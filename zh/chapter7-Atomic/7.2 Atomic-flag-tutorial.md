C++11 并发指南已经写了 6 章，前六章重点介绍了多线程编程方面的内容，但大部分内容只涉及多线程、互斥量、条件变量和异步编程相关的 API，C++11 程序员完全可以不必知道这些 API 在底层是如何实现的，只需要清楚 C++11 多线程和异步编程相关 API 的语义，然后熟加练习即可应付大部分多线程编码需求。但是在很多极端的场合下为了性能和效率，我们需要开发一些 lock-free 的算法和数据结构，前面几章的内容可能就派不上用场了，因此从本文开始介绍 C++11 标准中 `<atomic>` 头文件里面的类和相关函数。

本文介绍 `<atomic>` 头文件中最简单的原子类型: `atomic_flag`。`atomic_flag` 一种简单的原子布尔类型，只支持两种操作，`test_and_set` 和 `clear`。

# `std::atomic_flag` 构造函数 #

`std::atomic_flag` 构造函数如下：

    atomic_flag() noexcept = default;
    atomic_flag (const atomic_flag&T) = delete;

`std::atomic_flag` 只有默认构造函数，拷贝构造函数已被禁用，因此不能从其他的 `std::atomic_flag` 对象构造一个新的 `std::atomic_flag` 对象。

如果在初始化时没有明确使用 `ATOMIC_FLAG_INIT初始化`，那么新创建的 `std::atomic_flag` 对象的状态是未指定的（unspecified）（既没有被 set 也没有被 clear。）另外，`atomic_flag` 不能被拷贝，也不能 move 赋值。

`ATOMIC_FLAG_INIT`: 如果某个 `std::atomic_flag `对象使用该宏初始化，那么可以保证该 `std::atomic_flag` 对象在创建时处于 clear 状态。

下面先看一个简单的例子，`main()` 函数中创建了 10 个线程进行计数，率先完成计数任务的线程输出自己的 ID，后续完成计数任务的线程不会输出自身 ID：

    #include <iostream>              // std::cout
    #include <atomic>                // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
    #include <thread>                // std::thread, std::this_thread::yield
    #include <vector>                // std::vector
    
    std::atomic<bool> ready(false);    // can be checked without being set
    std::atomic_flag winner = ATOMIC_FLAG_INIT;    // always set when checked
    
    void count1m(int id)
    {
        while (!ready) {        
            std::this_thread::yield();
        } // 等待主线程中设置 ready 为 true.
    
        for (int i = 0; i < 1000000; ++i) {
        } // 计数.
    
        // 如果某个线程率先执行完上面的计数过程，则输出自己的 ID.
        // 此后其他线程执行 test_and_set 是 if 语句判断为 false，
        // 因此不会输出自身 ID.
        if (!winner.test_and_set()) {
            std::cout << "thread #" << id << " won!\n";
        }
    };
    
    int main()
    {
        std::vector<std::thread> threads;
        std::cout << "spawning 10 threads that count to 1 million...\n";
        for (int i = 1; i <= 10; ++i)
            threads.push_back(std::thread(count1m, i));
        ready = true;
    
        for (auto & th:threads)
            th.join();
    
        return 0;
    }

多次执行结果如下：

    atomic ) ./Atomic-Flag1 
    spawning 10 threads that count to 1 million...
    thread #6 won!
    atomic ) ./Atomic-Flag1     
    spawning 10 threads that count to 1 million...
    thread #1 won!
    atomic ) ./Atomic-Flag1 
    spawning 10 threads that count to 1 million...
    thread #5 won!
    atomic ) ./Atomic-Flag1 
    spawning 10 threads that count to 1 million...
    thread #1 won!
    atomic ) ./Atomic-Flag1 
    spawning 10 threads that count to 1 million...
    thread #1 won!
    atomic ) ./Atomic-Flag1 
    spawning 10 threads that count to 1 million...
    thread #10 won!

# `test_and_set` 介绍 #

`std::atomic_flag` 的 `test_and_set` 函数原型如下：

    bool test_and_set (memory_order sync = memory_order_seq_cst) volatile noexcept;
    bool test_and_set (memory_order sync = memory_order_seq_cst) noexcept;

`test_and_set()` 函数检查 `std::atomic_flag` 标志，如果 `std::atomic_flag` 之前没有被设置过，则设置 `std::atomic_flag` 的标志，并返回先前该 `std::atomic_flag` 对象是否被设置过，如果之前 `std::atomic_flag` 对象已被设置，则返回 `true`，否则返回 `false`。

test-and-set 操作是原子的（因此 test-and-set 是原子 read-modify-write （RMW）操作）。

`test_and_set` 可以指定 Memory Order(后续的文章会详细介绍 C++11 的 Memory Order，此处为了完整性列出 `test_and_set` 参数 `sync` 的取值)，取值如下：

<table class="boxed">
<tr><th>Memory Order 值</th><th>Memory Order 类型</th></tr>
<tr>
<td style="text-align: center;"><samp>memory_order_relaxed</samp></td>
<td style="text-align: center;">Relaxed</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_consume</samp></td>
<td style="text-align: center;">Consume</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_acquire</samp></td>
<td style="text-align: center;">Acquire</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_release</samp></td>
<td style="text-align: center;">Release</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_acq_rel</samp></td>
<td style="text-align: center;">Acquire/Release</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_seq_cst</samp></td>
<td style="text-align: center;">Sequentially consistent</td>
</tr>
</table>

一个简单的例子：

    #include <iostream>                // std::cout
    #include <atomic>                // std::atomic_flag
    #include <thread>                // std::thread
    #include <vector>                // std::vector
    #include <sstream>                // std::stringstream
    
    std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;
    std::stringstream stream;
    
    void append_number(int x)
    {
        while (lock_stream.test_and_set()) {
        }
        stream << "thread #" << x << '\n';
        lock_stream.clear();
    }
    
    int main()
    {
        std::vector < std::thread > threads;
        for (int i = 1; i <= 10; ++i)
            threads.push_back(std::thread(append_number, i));
        for (auto & th:threads)
            th.join();
    
        std::cout << stream.str() << std::endl;;
        return 0;
    }

执行结果如下：

    thread #1
    thread #2
    thread #3
    thread #4
    thread #5
    thread #6
    thread #7
    thread #8
    thread #9
    thread #10

`clear()` 介绍

清除 `std::atomic_flag` 对象的标志位，即设置 `atomic_flag` 的值为 `false`。`clear` 函数原型如下：

    void clear (memory_order sync = memory_order_seq_cst) volatile noexcept;
    void clear (memory_order sync = memory_order_seq_cst) noexcept;

清除 `std::atomic_flag` 标志使得下一次调用 `std::atomic_flag::test_and_set` 返回 false。

`std::atomic_flag::clear()` 可以指定 Memory Order(后续的文章会详细介绍 C++11 的 Memory Order，此处为了完整性列出 `clear` 参数 `sync` 的取值)，取值如下：

<table class="boxed">
<tr><th>Memory Order 值</th><th>Memory Order 类型</th></tr>
<tr>
<td style="text-align: center;"><samp>memory_order_relaxed</samp></td>
<td style="text-align: center;">Relaxed</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_consume</samp></td>
<td style="text-align: center;">Consume</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_acquire</samp></td>
<td style="text-align: center;">Acquire</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_release</samp></td>
<td style="text-align: center;">Release</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_acq_rel</samp></td>
<td style="text-align: center;">Acquire/Release</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_seq_cst</samp></td>
<td style="text-align: center;">Sequentially consistent</td>
</tr>
</table>

结合 `std::atomic_flag::test_and_set()` 和 `std::atomic_flag::clear()`，`std::atomic_flag` 对象可以当作一个简单的自旋锁使用，请看下例：

    #include <thread>
    #include <vector>
    #include <iostream>
    #include <atomic>
    
    std::atomic_flag lock = ATOMIC_FLAG_INIT;
    
    void f(int n)
    {
        for (int cnt = 0; cnt < 100; ++cnt) {
            while (lock.test_and_set(std::memory_order_acquire))  // acquire lock
                 ; // spin
            std::cout << "Output from thread " << n << '\n';
            lock.clear(std::memory_order_release);               // release lock
        }
    }
    
    int main()
    {
        std::vector<std::thread> v;
        for (int n = 0; n < 10; ++n) {
            v.emplace_back(f, n);
        }
        for (auto& t : v) {
            t.join();
        }
    }

在上面的程序中，`std::atomic_flag` 对象 `lock` 的上锁操作可以理解为 `lock.test_and_set(std::memory_order_acquire);` (此处指定了 Memory Order，更多有关 Memory Order 的概念，我会在后续的文章中介绍)，解锁操作相当与 `lock.clear(std::memory_order_release)`。

在上锁的时候，如果 `lock.test_and_set` 返回 `false`，则表示上锁成功（此时 `while` 不会进入自旋状态），因为此前 `lock` 的标志位为 `false`(即没有线程对 `lock` 进行上锁操作)，但调用 `test_and_set` 后 `lock` 的标志位为 `true`，说明某一线程已经成功获得了 `lock` 锁。

解锁操作非常简单，直接调用 `lock.clear()` 即可，此后其他线程可以继续对该 `std::atomic_flag` 对象(`lock`)进行上锁和解锁操作。

如果在该线程解锁（即调用 `lock.clear(std::memory_order_release)`） 之前，另外一个线程也调用 `lock.test_and_set(std::memory_order_acquire)` 试图获得锁，则 `test_and_set(std::memory_order_acquire)` 返回 `true`，则 `while` 进入自旋状态。如果获得锁的线程解锁（即调用了 `lock.clear(std::memory_order_release)`）之后，另外某个线程试图调用 `lock.test_and_set(std::memory_order_acquire)` 并且返回 `false`，则 `while` 不会进入自旋，此时该线程也成功地获得了锁。

按照上面的分析，我们知道在某种情况下 `std::atomic_flag` 对象可以当作一个简单的自旋锁使用。