## 4.3 锁类型详解 ##

### std::lock_guard 介绍 ###

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

### `std::unique_lock` 介绍 ###

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
