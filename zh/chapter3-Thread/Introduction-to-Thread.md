本文将稍微详细地介绍 `std::thread` 的用法。

`std::thread` 在 `<thread>` 头文件中声明，因此使用 `std::thread` 时需要包含 `<thread>` 头文件。

# `std::thread` 构造 #

1. `thread() noexcept;` 默认构造函数，创建一个空的 thread 执行对象。
2. `template <class Fn, class... Args> explicit thread (Fn&& fn, Args&&... args);` 初始化构造函数，创建一个 thread对象，该 thread对象可被 joinable，新产生的线程会调用 fn 函数，该函数的参数由 args 给出。
3. `thread (const thread&) = delete;` 拷贝构造函数(被禁用)，意味着 thread 不可被拷贝构造。
4. `thread (thread&& x) noexcept;` move 构造函数，move 构造函数，调用成功之后 x 不代表任何 thread 执行对象。
注意：可被 joinable 的 thread 对象必须在他们销毁之前被主线程 join 或者将其设置为 detached.

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

# move 赋值操作 #

1. `thread& operator= (thread&& rhs) noexcept;` move 赋值操作，如果当前对象不可 joinable，需要传递一个右值引用(rhs)给 move 赋值操作；如果当前对象可被 joinable，则 terminate() 报错。
2. `thread& operator= (const thread&) = delete;` 拷贝赋值操作被禁用，thread 对象不可被拷贝。

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

    /*
     * ===  FUNCTION  =========================================================
     *         Name:  main
     *  Description:  program entry routine.
     * ========================================================================
     */
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
    }  /* ----------  end of function main  ---------- */

# 其他成员函数 #


- `get_id`: 获取线程 ID。
- `joinable`: 检查线程是否可被 join。
- `join`: Join 线程。
- `detach`: Detach 线程
- `swap`: Swap 线程 。
- `native_handle`: 返回 native handle。
- `hardware_concurrency` [static]: 检测硬件并发特性。