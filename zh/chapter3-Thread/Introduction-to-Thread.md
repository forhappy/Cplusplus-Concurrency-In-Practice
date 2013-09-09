本节将详细介绍 `std::thread` 的用法。

`std::thread` 在 `<thread>` 头文件中声明，因此使用 `std::thread` 需包含 `<thread>` 头文件。

## `<thread>` 头文件摘要 ##

`<thread>` 头文件声明了 std::thread 线程类及 `std::swap` (交换两个线程对象)辅助函数。另外命名空间 `std::this_thread` 也声明在 `<thread>` 头文件中。下面是 C++11 标准所定义的 `<thread>` 头文件摘要：

>参见 N3242=11-0012 草案第 30.3 节 Threads(p1133)。

    namespace std {
        #define __STDCPP_THREADS__ __cplusplus
        class thread;
        void swap(thread& x, thread& y);
        namespace this_thread {
            thread::id get_id();
            void yield();

            template <class Clock, class Duration>
            void sleep_until(const chrono::time_point<Clock, Duration>& abs_time);

            template <class Rep, class Period>
            void sleep_for(const chrono::duration<Rep, Period>& rel_time);
        }        
    }

`<thread>` 头文件主要声明了 `std::thread` 类，另外在 `std::this_thread` 命名空间中声明了 `get_id`，`yield`，`sleep_until` 以及 `sleep_for` 等辅助函数，本章稍微会详细介绍 `std::thread` 类及相关函数。


### `std::thread` 类摘要 ###

`std::thread` 代表了一个线程对象，C++11 标准声明如下：

    namespace std {
        class thread {
            public:
                // 类型声明:
                class id;
                typedef implementation-defined native_handle_type;

                // 构造函数、拷贝构造函数和析构函数声明:
                thread() noexcept;
                template <class F, class ...Args> explicit thread(F&& f, Args&&... args);
                ~thread();
                thread(const thread&) = delete;
                thread(thread&&) noexcept;
                thread& operator=(const thread&) = delete;
                thread& operator=(thread&&) noexcept;

                // 成员函数声明:
                void swap(thread&) noexcept;
                bool joinable() const noexcept;
                void join();
                void detach();
                id get_id() const noexcept;
                native_handle_type native_handle();
                
                // 静态成员函数声明:
                static unsigned hardware_concurrency() noexcept;
        };
    }

`std::thread` 中主要声明三类函数：(1). 构造函数、拷贝构造函数及析构函数；(2). 成员函数；(3). 静态成员函数。另外， `std::thread::id` 表示线程 ID，同时 C++11 声明如下：

    namespace std {
        class thread::id {
            public:
                id() noexcept;
        };
    
        bool operator==(thread::id x, thread::id y) noexcept;
        bool operator!=(thread::id x, thread::id y) noexcept;
        bool operator<(thread::id x, thread::id y) noexcept;
        bool operator<=(thread::id x, thread::id y) noexcept;
        bool operator>(thread::id x, thread::id y) noexcept;
        bool operator>=(thread::id x, thread::id y) noexcept;
    
        template<class charT, class traits>
        basic_ostream<charT, traits>&
            operator<< (basic_ostream<charT, traits>& out, thread::id id);
    
    
        // Hash 支持
        template <class T> struct hash;
        template <> struct hash<thread::id>;
    }

### `std::thread` 详解 ###

### `std::thread` 构造和赋值 ###

#### `std::thread` 构造函数 ####

<table>
<tbody>
<tr class="odd"><th>默认构造函数 (1)</th>
<td>thread() noexcept;</td>
</tr>
<tr class="even"><th>初始化构造函数 (2)</th>
<td>
template &lt;class Fn, class... Args&gt;<br/>
explicit thread(Fn&amp;&amp; fn, Args&amp;&amp;... args);
</td>
</tr>
<tr class="odd"><th>拷贝构造函数 [deleted] (3)</th>
<td>
thread(const thread&amp;) = delete;
</td>
</tr>
<tr class="even"><th>Move 构造函数 (4)</th>
<td>
thread(thread&amp;&amp; x) noexcept;
</td>
</tr>
</tbody>
</table>

1. 默认构造函数(1)，创建一个空的 `std::thread` 执行对象。
2. 初始化构造函数(2)，创建一个 `std::thread` 对象，该 `std::thread` 对象可被 `joinable`，新产生的线程会调用 `fn` 函数，该函数的参数由 `args` 给出。
3. 拷贝构造函数(被禁用)(3)，意味着 `std::thread` 对象不可拷贝构造。
4. Move 构造函数(4)，move 构造函数(move 语义是 C++11 新出现的概念，详见附录)，调用成功之后 `x` 不代表任何 `std::thread` 执行对象。

>注意：可被 `joinable` 的 `std::thread` 对象必须在他们销毁之前被主线程 `join` 或者将其设置为 `detached`.

std::thread 各种构造函数例子如下（[参考](http://en.cppreference.com/w/cpp/thread/thread/thread)）：

    #include <iostream>
    #include <utility>
    #include <thread>
    #include <chrono>
    #include <functional>
    #include <atomic>
 
    void f1(int n)
    {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Thread " << n << " executing\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
 
    void f2(int& n)
    {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Thread 2 executing\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
 
    int main()
    {
        int n = 0;
        std::thread t1; // t1 is not a thread
        std::thread t2(f1, n + 1); // pass by value
        std::thread t3(f2, std::ref(n)); // pass by reference
        std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
        t2.join();
        t4.join();
        std::cout << "Final value of n is " << n << '\n';
    }

#### `std::thread` 赋值操作 ####

<table style="width: 475px; height: 87px;">
<tbody>
<tr class="odd"><th>Move 赋值操作 (1)</th>
<td>
thread&amp; operator=(thread&amp;&amp; rhs) noexcept;
</td>
</tr>
<tr class="even"><th>拷贝赋值操作 [deleted] (2)</th>
<td>
thread&amp; operator=(const thread&amp;) = delete;
</td>
</tr>
</tbody>
</table>

1. Move 赋值操作(1)，如果当前对象不可 `joinable`，需要传递一个右值引用(`rhs`)给 `move` 赋值操作；如果当前对象可被 `joinable`，则会调用 `terminate`() 报错。
2. 拷贝赋值操作(2)，被禁用，因此 `std::thread` 对象不可拷贝赋值。

请看下面的例子：

    #include <stdio.h>
    #include <stdlib.h>

    #include <chrono>    // std::chrono::seconds
    #include <iostream>  // std::cout
    #include <thread>    // std::thread, std::this_thread::sleep_for

    void thread_task(int n) {
        std::this_thread::sleep_for(std::chrono::seconds(n));
        std::cout << "hello thread "
            << std::this_thread::get_id()
            << " paused " << n << " seconds" << std::endl;
    }

    int main(int argc, const char *argv[])
    {
        std::thread threads[5];
        std::cout << "Spawning 5 threads...\n";
        for (int i = 0; i < 5; i++) {
            threads[i] = std::thread(thread_task, i + 1);
        }
        std::cout << "Done spawning threads! Now wait for them to join\n";
        for (auto& t: threads) {
            t.join();
        }
        std::cout << "All threads joined.\n";

        return EXIT_SUCCESS;
    }

### 其他成员函数 ###

- `get_id`: 获取线程 ID。
- `joinable`: 检查线程是否可被 join。
- `join`: Join 线程。
- `detach`: Detach 线程。
- `swap`: Swap 线程 。
- `native_handle`: 返回 native handle。
- `hardware_concurrency` [static]: 检测硬件并发特性。