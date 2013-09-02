本文将介绍 C++11 标准中 `<condition_variable>` 头文件里面的类和相关函数。

`<condition_variable >` 头文件主要包含了与条件变量相关的类和函数。相关的类包括 `std::condition_variable` 和 `std::condition_variable_any`，还有枚举类型`std::cv_status`。另外还包括函数 `std::notify_all_at_thread_exit()`，下面分别介绍一下以上几种类型。

# `std::condition_variable` 类介绍 #

`std::condition_variable` 是条件变量，更多有关条件变量的定义参考维基百科。`Linux` 下使用 `Pthread` 库中的 `pthread_cond_*()` 函数提供了与条件变量相关的功能， `Windows` 则参考 MSDN。

当 `std::condition_variable` 对象的某个 `wait` 函数被调用的时候，它使用 `std::unique_lock`(封装 `std::mutex`) 来锁住当前线程。当前线程会一直被阻塞，直到另外一个线程在相同的 `std::condition_variable` 对象上调用了 `notification` 函数来唤醒当前线程。

`std::condition_variable` 对象通常使用 `std::unique_lock<std::mutex>` 来等待，如果需要使用另外的 `lockable` 类型，可以使用 `std::condition_variable_any` 类，本文后面会讲到 `std::condition_variable_any` 的用法。

首先我们来看一个简单的[例子](http://www.cplusplus.com/reference/condition_variable/condition_variable/)：

    #include <iostream>                // std::cout
    #include <thread>                // std::thread
    #include <mutex>                // std::mutex, std::unique_lock
    #include <condition_variable>    // std::condition_variable

    std::mutex mtx; // 全局互斥锁.
    std::condition_variable cv; // 全局条件变量.
    bool ready = false; // 全局标志位.

    void do_print_id(int id)
    {
        std::unique_lock <std::mutex> lck(mtx);
        while (!ready) // 如果标志位不为 true, 则等待...
            cv.wait(lck); // 当前线程被阻塞, 当全局标志位变为 true 之后,
        // 线程被唤醒, 继续往下执行打印线程编号id.
        std::cout << "thread " << id << '\n';
    }

    void go()
    {
        std::unique_lock <std::mutex> lck(mtx);
        ready = true; // 设置全局标志位为 true.
        cv.notify_all(); // 唤醒所有线程.
    }

    int main()
    {
        std::thread threads[10];
        // spawn 10 threads:
        for (int i = 0; i < 10; ++i)
            threads[i] = std::thread(do_print_id, i);

        std::cout << "10 threads ready to race...\n";
        go(); // go!

        for (auto & th:threads)
            th.join();

        return 0;
    }

执行结果如下：

    concurrency ) ./ConditionVariable-basic1 
    10 threads ready to race...
    thread 1
    thread 0
    thread 2
    thread 3
    thread 4
    thread 5
    thread 6
    thread 7
    thread 8
    thread 9

好了，对条件变量有了一个基本的了解之后，我们来看看 std::condition_variable 的各个成员函数。

## `std::condition_variable` 构造函数 ##
<table>
<tr class="odd"><th> default (1) </th><td> condition_variable(); </td></tr>
<tr class="even"><th> copy [deleted] (2) </th>
<td> condition_variable (const condition_variable&amp;) = delete; </td></tr>
</table>


`std::condition_variable` 的拷贝构造函数被禁用，只提供了默认构造函数。

## `std::condition_variable::wait()` 介绍 ##

<table>
<tr class="odd"><th> unconditional (1) </th>
<td> void wait (unique_lock&lt;mutex&gt;&amp; lck); </td></tr>
<tr class="even"><th>predicate (2)</th>
<td><pre>template &lt;class Predicate&gt;
void wait (unique_lock&lt;mutex&gt;&amp; lck, Predicate pred); </pre></td></tr>
</table>

`std::condition_variable` 提供了两种 `wait()` 函数。当前线程调用 `wait()` 后将被阻塞(此时当前线程应该获得了锁（`mutex`），不妨设获得锁 `lck`)，直到另外某个线程调用 `notify_*` 唤醒了当前线程。

在线程被阻塞时，该函数会自动调用 `lck.unlock()` 释放锁，使得其他被阻塞在锁竞争上的线程得以继续执行。另外，一旦当前线程获得通知(`notified`，通常是另外某个线程调用 `notify_*` 唤醒了当前线程)，`wait()` 函数也是自动调用 `lck.lock()`，使得 `lck` 的状态和 `wait` 函数被调用时相同。

在第二种情况下（即设置了 `Predicate`），只有当 `pred` 条件为 `false` 时调用 `wait()` 才会阻塞当前线程，并且在收到其他线程的通知后只有当 `pred` 为 `true` 时才会被解除阻塞。因此第二种情况类似以下代码：

    while (!pred()) wait(lck);

请看下面例子（[参考](http://www.cplusplus.com/reference/condition_variable/condition_variable/wait/)）：

    #include <iostream>                // std::cout
    #include <thread>                // std::thread, std::this_thread::yield
    #include <mutex>                // std::mutex, std::unique_lock
    #include <condition_variable>    // std::condition_variable

    std::mutex mtx;
    std::condition_variable cv;

    int cargo = 0;
    bool shipment_available()
    {
        return cargo != 0;
    }

    // 消费者线程.
    void consume(int n)
    {
        for (int i = 0; i < n; ++i) {
            std::unique_lock <std::mutex> lck(mtx);
            cv.wait(lck, shipment_available);
            std::cout << cargo << '\n';
            cargo = 0;
        }
    }

    int main()
    {
        std::thread consumer_thread(consume, 10); // 消费者线程.
    
        // 主线程为生产者线程, 生产 10 个物品.
        for (int i = 0; i < 10; ++i) {
            while (shipment_available())
                std::this_thread::yield();
            std::unique_lock <std::mutex> lck(mtx);
            cargo = i + 1;
            cv.notify_one();
        }
    
        consumer_thread.join();

        return 0;
    }

程序执行结果如下：

    concurrency ) ./ConditionVariable-wait 
    1
    2
    3
    4
    5
    6
    7
    8
    9
    10

## `std::condition_variable::wait_for()` 介绍 ##

<table>
<tr class="odd"><th>unconditional (1)</th>
<td>
<pre>template &lt;class Rep, class Period&gt;
cv_status wait_for (unique_lock&lt;mutex&gt;&amp; lck,
                      const chrono::duration&lt;Rep,Period&gt;&amp; rel_time);
</pre>
</td>
</tr>
<tr class="even"><th>predicate (2)</th>
<td>
<pre>template &lt;class Rep, class Period, class Predicate&gt;
bool wait_for (unique_lock&lt;mutex&gt;&amp; lck,
               const chrono::duration&lt;Rep, Period&gt;&amp; rel_time, Predicate pred);</pre>
</td>
</tr>
</table>

与 `std::condition_variable::wait()` 类似，不过 `wait_for` 可以指定一个时间段，在当前线程收到通知或者指定的时间 `rel_time` 超时之前，该线程都会处于阻塞状态。而一旦超时或者收到了其他线程的通知，`wait_for` 返回，剩下的处理步骤和 `wait()` 类似。

另外，`wait_for` 的重载版本（`predicte(2)`）的最后一个参数 pred 表示 `wait_for` 的预测条件，只有当 `pred` 条件为 `false` 时调用 `wait()` 才会阻塞当前线程，并且在收到其他线程的通知后只有当 `pred` 为 `true` 时才会被解除阻塞，因此相当于如下代码：

    return wait_until (lck, chrono::steady_clock::now() + rel_time, std::move(pred));

请看下面的例子（[参考](http://www.cplusplus.com/reference/condition_variable/condition_variable/wait_for/)），下面的例子中，主线程等待 `th` 线程输入一个值，然后将 `th` 线程从终端接收的值打印出来，在 `th` 线程接受到值之前，主线程一直等待，每个一秒超时一次，并打印一个 "`.`"：

    #include <iostream>           // std::cout
    #include <thread>             // std::thread
    #include <chrono>             // std::chrono::seconds
    #include <mutex>              // std::mutex, std::unique_lock
    #include <condition_variable> // std::condition_variable, std::cv_status

    std::condition_variable cv;

    int value;

    void do_read_value()
    {
        std::cin >> value;
        cv.notify_one();
    }

    int main ()
    {
        std::cout << "Please, enter an integer (I'll be printing dots): \n";
        std::thread th(do_read_value);
    
        std::mutex mtx;
        std::unique_lock<std::mutex> lck(mtx);
        while (cv.wait_for(lck,std::chrono::seconds(1)) == std::cv_status::timeout) {
            std::cout << '.';
            std::cout.flush();
        }
    
        std::cout << "You entered: " << value << '\n';
    
        th.join();
        return 0;
    }

## `std::condition_variable::wait_until` 介绍 ##

<table>
<tr class="odd"><th>unconditional (1)</th>
<td>
<pre>template &lt;class Clock, class Duration&gt;
cv_status wait_until (unique_lock&lt;mutex&gt;&amp; lck,
                        const chrono::time_point&lt;Clock,Duration&gt;&amp; abs_time);
</pre>
</td>
</tr>
<tr class="even"><th>predicate (2)</th>
<td>
<pre>template &lt;class Clock, class Duration, class Predicate&gt;
bool wait_until (unique_lock&lt;mutex&gt;&amp; lck,
                 const chrono::time_point&lt;Clock,Duration&gt;&amp; abs_time,
                 Predicate pred);</pre>
</td>
</tr>
</table>

与 `std::condition_variable::wait_for` 类似，但是 `wait_until` 可以指定一个时间点，在当前线程收到通知或者指定的时间点 `abs_time` 超时之前，该线程都会处于阻塞状态。而一旦超时或者收到了其他线程的通知，`wait_until` 返回，剩下的处理步骤和 `wait_until()` 类似。

另外，`wait_until` 的重载版本（`predicte`(2)）的最后一个参数 `pred` 表示 `wait_until` 的预测条件，只有当 `pred` 条件为 `false` 时调用 `wait()` 才会阻塞当前线程，并且在收到其他线程的通知后只有当 `pred` 为 `true` 时才会被解除阻塞，因此相当于如下代码：

    while (!pred())
        if ( wait_until(lck,abs_time) == cv_status::timeout)
        return pred();
    return true;

## `std::condition_variable::notify_one(`) 介绍 ##

唤醒某个等待(`wait`)线程。如果当前没有等待线程，则该函数什么也不做，如果同时存在多个等待线程，则唤醒某个线程是不确定的(`unspecified`)。

请看下例（[参考](http://www.cplusplus.com/reference/condition_variable/condition_variable/notify_one/)）：

    #include <iostream>                // std::cout
    #include <thread>                // std::thread
    #include <mutex>                // std::mutex, std::unique_lock
    #include <condition_variable>    // std::condition_variable

    std::mutex mtx;
    std::condition_variable cv;

    int cargo = 0; // shared value by producers and consumers

    void consumer()
    {
        std::unique_lock < std::mutex > lck(mtx);
        while (cargo == 0)
            cv.wait(lck);
        std::cout << cargo << '\n';
        cargo = 0;
    }
    
    void producer(int id)
    {
        std::unique_lock < std::mutex > lck(mtx);
        cargo = id;
        cv.notify_one();
    }

    int main()
    {
        std::thread consumers[10], producers[10];
    
        // spawn 10 consumers and 10 producers:
        for (int i = 0; i < 10; ++i) {
                consumers[i] = std::thread(consumer);
            producers[i] = std::thread(producer, i + 1);
        }

        // join them back:
        for (int i = 0; i < 10; ++i) {
            producers[i].join();
            consumers[i].join();
        }
    
        return 0;
    }

## `std::condition_variable::notify_all()` 介绍 ##

唤醒所有的等待(`wait`)线程。如果当前没有等待线程，则该函数什么也不做。请看下面的例子：

    #include <iostream>                // std::cout
    #include <thread>                // std::thread
    #include <mutex>                // std::mutex, std::unique_lock
    #include <condition_variable>    // std::condition_variable

    std::mutex mtx; // 全局互斥锁.
    std::condition_variable cv; // 全局条件变量.
    bool ready = false; // 全局标志位.

    void do_print_id(int id)
    {
        std::unique_lock <std::mutex> lck(mtx);
        while (!ready) // 如果标志位不为 true, 则等待...
            cv.wait(lck); // 当前线程被阻塞, 当全局标志位变为 true 之后,
        // 线程被唤醒, 继续往下执行打印线程编号id.
        std::cout << "thread " << id << '\n';
    }

    void go()
    {
        std::unique_lock <std::mutex> lck(mtx);
        ready = true; // 设置全局标志位为 true.
        cv.notify_all(); // 唤醒所有线程.
    }

    int main()
    {
        std::thread threads[10];
        // spawn 10 threads:
        for (int i = 0; i < 10; ++i)
            threads[i] = std::thread(do_print_id, i);
    
        std::cout << "10 threads ready to race...\n";
        go(); // go!
    
        for (auto & th:threads)
            th.join();

        return 0;
    }    

# `std::condition_variable_any` 介绍 #

与 `std::condition_variable` 类似，只不过 `std::condition_variable_any` 的 `wait` 函数可以接受任何 `lockable` 参数，而 `std::condition_variable` 只能接受 `std::unique_lock<std::mutex>` 类型的参数，除此以外，和 `std::condition_variable` 几乎完全一样。

# `std::cv_status` 枚举类型介绍 #


# `std::notify_all_at_thread_exit` #

函数原型为：

    void notify_all_at_thread_exit(condition_variable& cond, unique_lock<mutex> lck);

当调用该函数的线程退出时，所有在 cond 条件变量上等待的线程都会收到通知。请看下例（[参考](http://www.cplusplus.com/reference/condition_variable/notify_all_at_thread_exit/)）：

    #include <iostream>           // std::cout
    #include <thread>             // std::thread
    #include <mutex>              // std::mutex, std::unique_lock
    #include <condition_variable> // std::condition_variable

    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    void print_id (int id) {
      std::unique_lock<std::mutex> lck(mtx);
      while (!ready) cv.wait(lck);
      // ...
      std::cout << "thread " << id << '\n';
    }

    void go() {
      std::unique_lock<std::mutex> lck(mtx);
      std::notify_all_at_thread_exit(cv,std::move(lck));
      ready = true;
    }
    
    int main ()
    {
      std::thread threads[10];
      // spawn 10 threads:
      for (int i=0; i<10; ++i)
        threads[i] = std::thread(print_id,i);
      std::cout << "10 threads ready to race...\n";
    
      std::thread(go).detach();   // go!
    
      for (auto& th : threads) th.join();
    
      return 0;
    }

好了，到此为止，`<condition_variable>` 头文件中的两个条件变量类（`std::condition_variable` 和 `std::condition_variable_any`）、枚举类型（`std::cv_status`）、以及辅助函数（`std::notify_all_at_thread_exit()`）都已经介绍完了。从下一章开始我会逐步开始介绍 `<atomic>` 头文件中的内容，后续的文章还会介绍 C++11 的内存模型，涉及内容稍微底层一些，希望大家能够保持兴趣，学完 C++11 并发编程，如果你发现本文中的错误，也请给我反馈 ;-)。