本文将介绍 std::muetx 的用法。

Mutex 又称互斥量，C++ 11 中与 Mutex 相关的类（包括锁类型）和函数都声明在 `<mutex>` 头文件中，所以如果你需要使用 `std::mutex`，就必须包含 `<mutex>` 头文件。

# `<mutex>` 头文件概述 #

- Mutex 系列类(四种)

    1. `std::mutex`，最基本的 Mutex 类。
    2. `std::recursive_mutex`，递归 Mutex 类。
    3. `std::time_mutex`，定时 Mutex 类。
    4. `std::recursive_timed_mutex`，定时递归 Mutex 类。

- Lock 类（两种）

    1. `std::lock_guard`，与 Mutex RAII 相关，方便线程对互斥量上锁。
    2. `std::unique_lock`，与 Mutex RAII 相关，方便线程对互斥量上锁，但提供了更好的上锁和解锁控制。

- 其他类型

    1. `std::once_flag`
    2. `std::adopt_lock_t`
    3. `std::defer_lock_t`
    4. `std::try_to_lock_t`

- 辅助函数

    1. `std::try_lock`，尝试同时对多个互斥量上锁。
    2. `std::lock`，可以同时对多个互斥量上锁。
    3.  `std::call_once`，如果多个线程需要同时调用某个函数，`call_once` 可以保证多个线程对该函数只调用一次。

# `std::mutex` 介绍 #
下面以 `std::mutex` 为例介绍 C++11 中的互斥量用法。

`std::mutex` 是C++11 中最基本的互斥量，`std::mutex` 对象提供了独占所有权的特性——即不支持递归地对 `std::mutex` 对象上锁，而 `std::recursive_lock` 则可以递归地对互斥量对象上锁。

## `std::mutex` 的成员函数 ##

- 构造函数，std::mutex不允许拷贝构造，也不允许 move 拷贝，最初产生的 mutex 对象是处于 unlocked 状态的。
- lock()，调用线程将锁住该互斥量。线程调用该函数会发生下面 3 种情况：(1). 如果该互斥量当前没有被锁住，则调用线程将该互斥量锁住，直到调用 unlock之前，该线程一直拥有该锁。(2). 如果当前互斥量被其他线程锁住，则当前的调用线程被阻塞住。(3). 如果当前互斥量被当前调用线程锁住，则会产生死锁(deadlock)。
- unlock()， 解锁，释放对互斥量的所有权。
- try_lock()，尝试锁住互斥量，如果互斥量被其他线程占有，则当前线程也不会被阻塞。线程调用该函数也会出现下面 3 种情况，

    1. 如果当前互斥量没有被其他线程占有，则该线程锁住互斥量，直到该线程调用 unlock 释放互斥量。
    2. 如果当前互斥量被其他线程锁住，则当前调用线程返回 false，而并不会被阻塞掉。
    3. 如果当前互斥量被当前调用线程锁住，则会产生死锁(deadlock)。

下面给出一个与 std::mutex 的小例子（[参考](http://www.cplusplus.com/reference/mutex/mutex/try_lock/)）

    #include <iostream>       // std::cout
    #include <thread>         // std::thread
    #include <mutex>          // std::mutex

    volatile int counter(0); // non-atomic counter
    std::mutex mtx;           // locks access to counter

    void attempt_10k_increases() {
        for (int i=0; i<10000; ++i) {
            if (mtx.try_lock()) {   // only increase if currently not locked:
                ++counter;
                mtx.unlock();
            }
        }
    }

    int main (int argc, const char* argv[]) {
        std::thread threads[10];
        for (int i=0; i<10; ++i)
            threads[i] = std::thread(attempt_10k_increases);

        for (auto& th : threads) th.join();
        std::cout << counter << " successful increases of the counter.\n";

        return 0;
    }

## `std::recursive_mutex` 介绍 ##

`std::recursive_mutex` 与 `std::mutex `一样，也是一种可以被上锁的对象，但是和 `std::mutex` 不同的是，`std::recursive_mutex` 允许同一个线程对互斥量多次上锁（即递归上锁），来获得对互斥量对象的多层所有权，`std::recursive_mutex` 释放互斥量时需要调用与该锁层次深度相同次数的 `unlock()`，可理解为 `lock()` 次数和 `unlock()` 次数相同，除此之外，`std::recursive_mutex` 的特性和 `std::mutex` 大致相同。

## std::time_mutex 介绍 ##

`std::time_mutex` 比 `std::mutex` 多了两个成员函数，`try_lock_for()`，`try_lock_until()`。

`try_lock_for` 函数接受一个时间范围，表示在这一段时间范围之内线程如果没有获得锁则被阻塞住（与 `std::mutex` 的 `try_lock()` 不同，try_lock 如果被调用时没有获得锁则直接返回 `false`），如果在此期间其他线程释放了锁，则该线程可以获得对互斥量的锁，如果超时（即在指定时间内还是没有获得锁），则返回 `false`。

`try_lock_until` 函数则接受一个时间点作为参数，在指定时间点未到来之前线程如果没有获得锁则被阻塞住，如果在此期间其他线程释放了锁，则该线程可以获得对互斥量的锁，如果超时（即在指定时间内还是没有获得锁），则返回 `false`。

下面的小例子说明了 `std::time_mutex` 的用法（[参考](http://www.cplusplus.com/reference/mutex/timed_mutex/try_lock_for/)）。

    #include <iostream>       // std::cout
    #include <chrono>         // std::chrono::milliseconds
    #include <thread>         // std::thread
    #include <mutex>          // std::timed_mutex

    std::timed_mutex mtx;

    void fireworks() {
        // waiting to get a lock: each thread prints "-" every 200ms:
        while (!mtx.try_lock_for(std::chrono::milliseconds(200))) {
            std::cout << "-";
        }

        // got a lock! - wait for 1s, then this thread prints "*"
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "*\n";
        mtx.unlock();
    }

    int main ()
    {
        std::thread threads[10];
        // spawn 10 threads:
        for (int i=0; i<10; ++i)
            threads[i] = std::thread(fireworks);

        for (auto& th : threads) th.join();

        return 0;
    }

## std::recursive_timed_mutex 介绍 ##

和 `std:recursive_mutex` 与 `std::mutex` 的关系一样，`std::recursive_timed_mutex` 的特性也可以从 `std::timed_mutex` 推导出来，感兴趣的同鞋可以自行查阅。 ;-)

## std::lock_guard 介绍 ##

与 Mutex RAII 相关，方便线程对互斥量上锁。例子（[参考](http://www.cplusplus.com/reference/mutex/lock_guard/)）:

    #include <iostream>       // std::cout
    #include <thread>         // std::thread
    #include <mutex>          // std::mutex, std::lock_guard
    #include <stdexcept>      // std::logic_error

    std::mutex mtx;

    void print_even (int x) {
        if (x%2==0) std::cout << x << " is even\n";
        else throw (std::logic_error("not even"));
    }

    void print_thread_id (int id) {
        try {
            // using a local lock_guard to lock mtx guarantees unlocking on destruction / exception:
            std::lock_guard<std::mutex> lck (mtx);
            print_even(id);
        }
        catch (std::logic_error&) {
            std::cout << "[exception caught]\n";
        }
    }

    int main ()
    {
        std::thread threads[10];
        // spawn 10 threads:
        for (int i=0; i<10; ++i)
            threads[i] = std::thread(print_thread_id,i+1);

        for (auto& th : threads) th.join();

        return 0;
    }

## `std::unique_lock` 介绍 ##

与 Mutex RAII 相关，方便线程对互斥量上锁，但提供了更好的上锁和解锁控制。例子（[参考](http://www.cplusplus.com/reference/mutex/unique_lock/)）：

    #include <iostream>       // std::cout
    #include <thread>         // std::thread
    #include <mutex>          // std::mutex, std::unique_lock

    std::mutex mtx;           // mutex for critical section

    void print_block (int n, char c) {
        // critical section (exclusive access to std::cout signaled by lifetime of lck):
        std::unique_lock<std::mutex> lck (mtx);
        for (int i=0; i<n; ++i) {
            std::cout << c;
        }
        std::cout << '\n';
    }

    int main ()
    {
        std::thread th1 (print_block,50,'*');
        std::thread th2 (print_block,50,'$');

        th1.join();
        th2.join();

        return 0;
    }

好了，本文暂时讲到这里，还剩下 `std::try_lock`，`std::lock`，`std::call_once` 三个函数没有讲到，留在下一篇博客中讲吧 ;-)