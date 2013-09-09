# 引言 #
C++11 是 2011 年 9 月 1 号发布的。C++11 在 C++03 的基础上做了大量的改进，引入了很多新的特性，比如 Lambda 表达式，右值引用，统一的列表初始化方式，正则表达式等等。当然，其中最令人激动的特性是新标准引入了原子操作类和线程支持库。C++ 一直在语言层面缺少对多线程的支持，因此 C++11 新标准基本上弥补了这一缺陷。可以毫不夸张地说，C++11 相当于一门新的编程语言。

相信 Linux 程序员都用过 Pthread, 但有了 C++11 的 std::thread 以后，你可以在语言层面编写多线程程序了，直接的好处就是多线程程序的可移植性得到了很大的提高，所以作为一名 C++ 程序员，熟悉 C++11 的多线程编程方式还是很有益处的。

如果你对 C++11 不太熟悉，建议先看看维基百科上关于 C++11 新特性的介绍，中文C++11介绍，英文C++11介绍 ，另外C++之父 Bjarne Stroustrup 的关于 C++11 的 FAQ 也是必看的，我也收集了一些关于C++11的资料，供大家查阅，详见本章的 [资料汇](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter1-Introduction/web-resources.md)

# 与 C++11 多线程相关的头文件 #

C++11 新标准中引入了五个头文件来支持多线程编程，它们分别是 `<atomic>, <thread>, <mutex>, <condition_variable>` 和 `<future>`。

- `<atomic>`：该头文主要声明了两个类, `std::atomic` 和 `std::atomic_flag`，另外还声明了一套 C 风格的原子类型和与 C 兼容的原子操作的函数。

- `<thread>`：该头文件主要声明了 `std::thread` 类，另外 `std::this_thread` 命名空间也在该头文件中。

- `<mutex>`：该头文件主要声明了与互斥量(Mutex)相关的类，包括 `std::mutex_*` 一系列类，`std::lock_guard`, `std::unique_lock`, 以及其他的类型和函数。

- `<condition_variable>`：该头文件主要声明了与条件变量相关的类，包括 `std::condition_variable` 和 `std::condition_variable_any`。

- `<future>`：该头文件主要声明了 `std::promise`, `std::package_task` 两个 Provider 类，以及 `std::future` 和 `std::shared_future` 两个 Future 类，另外还有一些与之相关的类型和函数，`std::async()` 函数就声明在此头文件中。

# `std::thread` "Hello world" #
下面是一个最简单的使用 std::thread 类的例子

    #include <stdio.h>
    #include <stdlib.h>

    #include <iostream> // std::cout
    #include <thread>   // std::thread

    void thread_task() {
        std::cout << "hello thread" << std::endl;
    }

    int main(int argc, const char *argv[])
    {
        std::thread t(thread_task);
        t.join();

        return EXIT_SUCCESS;
    }

Makefile 如下：

    all:Thread

    CC=g++
    CPPFLAGS=-Wall -std=c++11 -ggdb
    LDFLAGS=-pthread

    Thread:Thread.o
        $(CC) $(LDFLAGS) -o $@ $^

    Thread.o:Thread.cc
        $(CC) $(CPPFLAGS) -o $@ -c $^


    .PHONY:
        clean

    clean:
        rm Thread.o Thread

注意在 Linux GCC4.6 环境下，编译时需要加 -pthread，否则执行时会出现：

    $ ./Thread
    terminate called after throwing an instance of 'std::system_error'
      what():  Operation not permitted
    Aborted (core dumped)

原因是 GCC 默认没有加载 pthread 库，据说在后续的版本中可以不用在编译时添加 -pthread 选项。
如果 -std=c++11 不被支持，请尝试使用 -std=c++0x 代替并确保GCC已经升级。
更多的有关 C++11 Concurrency 的介绍将在后续的一系列博客中写出，希望自己勤快一点吧 ;-)
