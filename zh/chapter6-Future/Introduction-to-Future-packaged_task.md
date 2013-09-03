本文主要介绍 `std::packaged_task`。

`std::packaged_task` 包装一个可调用的对象，并且允许异步获取该可调用对象产生的结果，从包装可调用对象意义上来讲，`std::packaged_task` 与 `std::function` 类似，只不过 `std::packaged_task` 将其包装的可调用对象的执行结果传递给一个 `std::future` 对象（该对象通常在另外一个线程中获取 `std::packaged_task` 任务的执行结果）。

`std::packaged_task` 对象内部包含了两个最基本元素，一、被包装的任务(stored task)，任务(task)是一个可调用的对象，如函数指针、成员函数指针或者函数对象，二、共享状态(shared state)，用于保存任务的返回值，可以通过 `std::future` 对象来达到异步访问共享状态的效果。

可以通过 `std::packged_task::get_future` 来获取与共享状态相关联的 `std::future` 对象。在调用该函数之后，两个对象共享相同的共享状态，具体解释如下：

1. `std::packaged_task` 对象是异步 Provider，它在某一时刻通过调用被包装的任务来设置共享状态的值。
2. `std::future` 对象是一个异步返回对象，通过它可以获得共享状态的值，当然在必要的时候需要等待共享状态标志变为 `ready`.

`std::packaged_task` 的共享状态的生命周期一直持续到最后一个与之相关联的对象被释放或者销毁为止。下面一个小例子大致讲了 `std::packaged_task` 的用法：

    #include <iostream>     // std::cout
    #include <future>       // std::packaged_task, std::future
    #include <chrono>       // std::chrono::seconds
    #include <thread>       // std::thread, std::this_thread::sleep_for

    // count down taking a second for each value:
    int countdown (int from, int to) {
        for (int i=from; i!=to; --i) {
            std::cout << i << '\n';
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "Finished!\n";
        return from - to;
    }

    int main ()
    {
        std::packaged_task<int(int,int)> task(countdown); // 设置 packaged_task
        std::future<int> ret = task.get_future(); // 获得与 packaged_task 共享状态相关联的 future 对象.
    
        std::thread th(std::move(task), 10, 0);   //创建一个新线程完成计数任务.
    
        int value = ret.get();                    // 等待任务完成并获取结果.
    
        std::cout << "The countdown lasted for " << value << " seconds.\n";
    
        th.join();
        return 0;
    }

执行结果为：

    concurrency ) ./Packaged_Task1 
    9
    7
    5
    3
    1
    Finished!
    The countdown lasted for 10 seconds.

# `std::packaged_task` 构造函数 #

<table>
<tr class="odd"><th>default (1)</th>
<td>packaged_task() noexcept;
</td>
</tr>
<tr class="even"><th>initialization (2)</th>
<td>
<pre>template &lt;class Fn&gt;
explicit packaged_task (Fn&amp;&amp; fn);
</pre>
</td>
</tr>
<tr class="odd"><th>with allocator (3)</th>
<td>
<pre>template &lt;class Fn, class Alloc&gt;
explicit packaged_task (allocator_arg_t aa, const Alloc&amp; alloc, Fn&amp;&amp; fn);
</pre>
</td>
</tr>
<tr class="even"><th>copy [deleted] (4)</th>
<td>packaged_task (const packaged_task&amp;) = delete;
</td>
</tr>
<tr class="odd"><th>move (5)</th>
<td>packaged_task (packaged_task&amp;&amp; x) noexcept;
</td>
</tr>
</table>

`std::packaged_task` 构造函数共有 5 中形式，不过拷贝构造已经被禁用了。下面简单地介绍一下上述几种构造函数的语义：

1. 默认构造函数，初始化一个空的共享状态，并且该 `packaged_task` 对象无包装任务。
2. 初始化一个共享状态，并且被包装任务由参数 fn 指定。
3. 带自定义内存分配器的构造函数，与默认构造函数类似，但是使用自定义分配器来分配共享状态。
4. 拷贝构造函数，被禁用。
5. 移动构造函数。

下面例子介绍了各类构造函数的用法：

    #include <iostream>     // std::cout
    #include <utility>      // std::move
    #include <future>       // std::packaged_task, std::future
    #include <thread>       // std::thread

    int main ()
    {
        std::packaged_task<int(int)> foo; // 默认构造函数.
    
        // 使用 lambda 表达式初始化一个 packaged_task 对象.
        std::packaged_task<int(int)> bar([](int x){return x*2;});
    
        foo = std::move(bar); // move-赋值操作，也是 C++11 中的新特性.
    
        // 获取与 packaged_task 共享状态相关联的 future 对象.
        std::future<int> ret = foo.get_future();

        std::thread(std::move(foo), 10).detach(); // 产生线程，调用被包装的任务.

        int value = ret.get(); // 等待任务完成并获取结果.
        std::cout << "The double of 10 is " << value << ".\n";

        return 0;
    }

与 `std::promise` 类似， `std::packaged_task` 也禁用了普通的赋值操作运算，只允许 `move` 赋值运算。


# `std::packaged_task::valid` 介绍 #

检查当前 `packaged_task` 是否和一个有效的共享状态相关联，对于由默认构造函数生成的 `packaged_task` 对象，该函数返回 `false`，除非中间进行了 `move` 赋值操作或者 `swap` 操作。

请看下例：

        #include <iostream>     // std::cout
        #include <utility>      // std::move
        #include <future>       // std::packaged_task, std::future
        #include <thread>       // std::thread

        // 在新线程中启动一个 int(int) packaged_task.
        std::future<int> launcher(std::packaged_task<int(int)>& tsk, int arg)
        {
            if (tsk.valid()) {
                std::future<int> ret = tsk.get_future();
                std::thread (std::move(tsk),arg).detach();
                return ret;
            }
            else return std::future<int>();
        }

        int main ()
        {
            std::packaged_task<int(int)> tsk([](int x){return x*2;});

            std::future<int> fut = launcher(tsk,25);

            std::cout << "The double of 25 is " << fut.get() << ".\n";

            return 0;
        }


# `std::packaged_task::get_future` 介绍 #

返回一个与 `packaged_task` 对象共享状态相关的 `future` 对象。返回的 `future` 对象可以获得由另外一个线程在该 `packaged_task` 对象的共享状态上设置的某个值或者异常。

请看例子(其实前面已经讲了 `get_future` 的例子)：

    #include <iostream>     // std::cout
    #include <utility>      // std::move
    #include <future>       // std::packaged_task, std::future
    #include <thread>       // std::thread

    int main ()
    {
        std::packaged_task<int(int)> tsk([](int x) { return x * 3; })); // package task
    
        std::future<int> fut = tsk.get_future();   // 获取 future 对象.

        std::thread(std::move(tsk), 100).detach();   // 生成新线程并调用packaged_task.

        int value = fut.get();                     // 等待任务完成, 并获取结果.

        std::cout << "The triple of 100 is " << value << ".\n";

        return 0;
    }

# `std::packaged_task::operator()(Args... args)` 介绍 #

调用该 packaged_task 对象所包装的对象(通常为函数指针，函数对象，lambda 表达式等)，传入的参数为 args. 调用该函数一般会发生两种情况：

1. 如果成功调用 `packaged_task` 所包装的对象，则返回值（如果被包装的对象有返回值的话）被保存在 `packaged_task` 的共享状态中。
2. 如果调用 `packaged_task` 所包装的对象失败，并且抛出了异常，则异常也会被保存在 `packaged_task` 的共享状态中。

以上两种情况都使共享状态的标志变为 `ready`，因此其他等待该共享状态的线程可以获取共享状态的值或者异常并继续执行下去。

共享状态的值可以通过在 future 对象(由 `get_future` 获得)上调用 `get` 来获得。

由于被包装的任务在 `packaged_task` 构造时指定，因此调用 `operator()` 的效果由 packaged_task 对象构造时所指定的可调用对象来决定：

1. 如果被包装的任务是函数指针或者函数对象，调用 `std::packaged_task::operator()` 只是将参数传递给被包装的对象。
2. 如果被包装的任务是指向类的非静态成员函数的指针，那么 `std::packaged_task::operator()` 的第一个参数应该指定为成员函数被调用的那个对象，剩余的参数作为该成员函数的参数。
3. 如果被包装的任务是指向类的非静态成员变量，那么 `std::packaged_task::operator()` 只允许单个参数。

# `std::packaged_task::make_ready_at_thread_exit` 介绍 #

该函数会调用被包装的任务，并向任务传递参数，类似 `std::packaged_task` 的 `operator()` 成员函数。但是与 `operator()` 函数不同的是，`make_ready_at_thread_exit` 并不会立即设置共享状态的标志为 `ready`，而是在线程退出时设置共享状态的标志。

如果与该 packaged_task 共享状态相关联的 future 对象在 `future::get` 处等待，则当前的 `future::get` 调用会被阻塞，直到线程退出。而一旦线程退出，`future::get` 调用继续执行，或者抛出异常。

注意，该函数已经设置了 promise 共享状态的值，如果在线程结束之前有其他设置或者修改共享状态的值的操作，则会抛出 `future_error`( `promise_already_satisfied` )。

# `std::packaged_task::reset()` 介绍 #

重置 packaged_task 的共享状态，但是保留之前的被包装的任务。请看例子，该例子中，packaged_task 被重用了多次：

    #include <iostream>     // std::cout
    #include <utility>      // std::move
    #include <future>       // std::packaged_task, std::future
    #include <thread>       // std::thread

    // a simple task:
    int triple (int x) { return x*3; }

    int main ()
    {
        std::packaged_task<int(int)> tsk (triple); // package task
        std::future<int> fut = tsk.get_future();
        std::thread (std::move(tsk), 100).detach();
        std::cout << "The triple of 100 is " << fut.get() << ".\n";

    
        // re-use same task object:
        tsk.reset();
        fut = tsk.get_future();
        std::thread(std::move(tsk), 200).detach();
        std::cout << "Thre triple of 200 is " << fut.get() << ".\n";

        return 0;
    }

# `std::packaged_task::swap()` 介绍 #

交换 `packaged_task` 的共享状态。

好了，`std::packaged_task` 介绍到这里，本文参考了 [http://www.cplusplus.com/reference/future/packaged_task/](http://www.cplusplus.com/reference/future/packaged_task/) 相关的内容。后一篇文章我将向大家介绍 `std::future`，`std::shared_future` 以及 std::future_error，另外还会介绍 `<future>` 头文件中的 `std::async`，`std::future_category` 函数以及相关枚举类型。

