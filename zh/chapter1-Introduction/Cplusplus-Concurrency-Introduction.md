# 引言 #
C++11 自2011年发布以来已经快两年了，之前一直没怎么关注，直到最近几个月才看了一些 C++11 的新特性，今后几篇博客我都会写一些关于 C++11 的特性，算是记录一下自己学到的东西吧，和大家共勉。

相信 Linux 程序员都用过 Pthread, 但有了 C++11 的 std::thread 以后，你可以在语言层面编写多线程程序了，直接的好处就是多线程程序的可移植性得到了很大的提高，所以作为一名 C++ 程序员，熟悉 C++11 的多线程编程方式还是很有益处的。

如果你对 C++11 不太熟悉，建议先看看维基百科上关于 C++11 新特性的介绍，中文C++11介绍，英文C++11介绍 ，另外C++之父 Bjarne Stroustrup 的关于 C++11 的 FAQ 也是必看的，我也收集了一些关于C++11的资料，供大家查阅：

# 资料汇 #
[http://www.open-std.org/jtc1/sc22/wg21/](http://www.open-std.org/jtc1/sc22/wg21/ "WG21")

C++0x/C++11 Support in GCC：[http://gcc.gnu.org/projects/cxx0x.html](http://gcc.gnu.org/projects/cxx0x.html "C++0x/C++11 Support in GCC")

What is C++0x：[https://www2.research.att.com/~bs/what-is-2009.pdf](https://www2.research.att.com/~bs/what-is-2009.pdf "What is C++0x")

Overview of the New C++：[http://www.artima.com/shop/overview_of_the_new_cpp](http://www.artima.com/shop/overview_of_the_new_cpp "Overview of the New C++")

Overview of the New C++ (C++0x).pdf：[http://ishare.iask.sina.com.cn/f/20120005.html?from=like](http://ishare.iask.sina.com.cn/f/20120005.html?from=like "Overview of the New C++ (C++0x).pdf")

A Brief Look at C++0x：[http://www.artima.com/cppsource/cpp0x.html](http://www.artima.com/cppsource/cpp0x.html "A Brief Look at C++0x")

Summary of C++11 Feature Availability in gcc and MSVC：[http://www.aristeia.com/C++11/C++11FeatureAvailability.htm](http://www.aristeia.com/C++11/C++11FeatureAvailability.htm "Summary of C++11 Feature Availability in gcc and MSVC")

C++ 11: Come Closer：[http://www.codeproject.com/Articles/344282/Cplusplus-11-Come-Closer](http://www.codeproject.com/Articles/344282/Cplusplus-11-Come-Closer "C++ 11: Come Closer")

C++11 threads, locks and condition variables： [http://www.codeproject.com/Articles/598695/Cplusplus11-threads-locks-and-condition-variables](http://www.codeproject.com/Articles/598695/Cplusplus11-threads-locks-and-condition-variables "C++11 threads, locks and condition variables")

Move Semantics and Perfect Forwarding in C++11：[http://www.codeproject.com/Articles/397492/Move-Semantics-and-Perfect-Forwarding-in-Cplusplus](http://www.codeproject.com/Articles/397492/Move-Semantics-and-Perfect-Forwarding-in-Cplusplus "Move Semantics and Perfect Forwarding in C++11")

[http://solarianprogrammer.com/categories/C++11/](http://solarianprogrammer.com/categories/C++11/)

C++11 Concurrency：[http://www.baptiste-wicht.com/2012/03/cpp11-concurrency-part1-start-threads/](http://www.baptiste-wicht.com/2012/03/cpp11-concurrency-part1-start-threads/ "C++11 Concurrency")

[http://www.hpl.hp.com/personal/Hans_Boehm/misc_slides/sfacm-cleaned.pdf](http://www.hpl.hp.com/personal/Hans_Boehm/misc_slides/sfacm-cleaned.pdf)

[http://en.cppreference.com/w/cpp/thread](http://en.cppreference.com/w/cpp/thread)

[http://isocpp.org/blog/2012/12/c11-a-cheat-sheet-alex-sinyakov](http://isocpp.org/blog/2012/12/c11-a-cheat-sheet-alex-sinyakov)

The Biggest Changes in C++11：[http://blog.smartbear.com/c-plus-plus/the-biggest-changes-in-c11-and-why-you-should-care/](http://blog.smartbear.com/c-plus-plus/the-biggest-changes-in-c11-and-why-you-should-care/ "The Biggest Changes in C++11")

Ten C++11 Features Every C++ Developer Should Use：[http://www.codeproject.com/Articles/570638/Ten-Cplusplus11-Features-Every-Cplusplus-Developer](http://www.codeproject.com/Articles/570638/Ten-Cplusplus11-Features-Every-Cplusplus-Developer "Ten C++11 Features Every C++ Developer Should Use")

C++11 – A Glance [part 1 of n]：[http://www.codeproject.com/Articles/312029/Cplusplus11-A-Glance-part-1-of-n](http://www.codeproject.com/Articles/312029/Cplusplus11-A-Glance-part-1-of-n " C++11 – A Glance [part 1 of n]")

C++11 – A Glance [part 2 of n]：[http://www.codeproject.com/Articles/314415/Cplusplus11-A-Glance-part-2-of-n](http://www.codeproject.com/Articles/314415/Cplusplus11-A-Glance-part-2-of-n "C++11 – A Glance [part 2 of n]")

C++11（及现代C++风格）和快速迭代式开发：[http://mindhacks.cn/2012/08/27/modern-cpp-practices/](http://mindhacks.cn/2012/08/27/modern-cpp-practices/ "C++11（及现代C++风格）和快速迭代式开发")

Lambda Functions in C++11 - the Definitive Guide：[http://www.cprogramming.com/c++11/c++11-lambda-closures.html](http://www.cprogramming.com/c++11/c++11-lambda-closures.html "Lambda Functions in C++11 - the Definitive Guide")

Better types in C++11 - nullptr, enum classes (strongly typed enumerations) and cstdint：[http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html](http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html "Better types in C++11 - nullptr, enum classes (strongly typed enumerations) and cstdint")

Rvalue-references-and-move-semantics-in-c++11：[http://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html](http://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html "Rvalue-references-and-move-semantics-in-c++11")

[http://www.gotw.ca/publications/index.htm](http://www.gotw.ca/publications/index.htm)

[http://www.devx.com/SpecialReports/Door/38865](http://www.devx.com/SpecialReports/Door/38865)

Multi-threading in C++0x：[http://accu.org/index.php/journals/1584](http://accu.org/index.php/journals/1584 "Multi-threading in C++0x")

C++ 0X feature summary cheat sheat：[http://www.iesensor.com/blog/2011/05/31/c-0x-feature-summary-cheat-sheat/](http://www.iesensor.com/blog/2011/05/31/c-0x-feature-summary-cheat-sheat/ "C++ 0X feature summary cheat sheat")

Multithreading in C++0x part 1: Starting Threads：[http://www.justsoftwaresolutions.co.uk/threading/multithreading-in-c++0x-part-1-starting-threads.html](http://www.justsoftwaresolutions.co.uk/threading/multithreading-in-c++0x-part-1-starting-threads.html "Multithreading in C++0x part 1")

[http://en.cppreference.com/w/cpp/thread](http://en.cppreference.com/w/cpp/thread)

[http://www.cplusplus.com/reference/multithreading/](http://www.cplusplus.com/reference/multithreading/)

好了，下面来说正题吧 ;-)

# 与 C++11 多线程相关的头文件 #

C++11 新标准中引入了四个头文件来支持多线程编程，他们分别是 `<atomic>, <thread>, <mutex>, <condition_variable>` 和 `<future>`。

- `<atomic>`：该头文主要声明了两个类, `std::atomic` 和 `std::atomic_flag`，另外还声明了一套 C 风格的原子类型和与 C 兼容的原子操作的函数。

- `<thread>`：该头文件主要声明了 `std::thread` 类，另外 `std::this_thread` 命名空间也在该头文件中。

- `<mutex>`：该头文件主要声明了与互斥量(mutex)相关的类，包括 `std::mutex` 系列类，`std::lock_guard`, `std::unique_lock`, 以及其他的类型和函数。

- `<condition_variable>`：该头文件主要声明了与条件变量相关的类，包括 `std::condition_variable` 和 `std::condition_variable_any`。

- <future>：该头文件主要声明了 `std::promise`, `std::package_task` 两个 Provider 类，以及 `std::future` 和 `std::shared_future` 两个 Future 类，另外还有一些与之相关的类型和函数，`std::async()` 函数就声明在此头文件中。

# std::thread "Hello world" #
下面是一个最简单的使用 std::thread 类的例子

    #include <stdio.h>
    #include <stdlib.h>

    #include <iostream> // std::cout
    #include <thread>   // std::thread

    void thread_task() {
        std::cout << "hello thread" << std::endl;
    }

    /*
     * ===  FUNCTION  =========================================================
     *         Name:  main
     *  Description:  program entry routine.
     * ========================================================================
     */
    int main(int argc, const char *argv[])
    {
        std::thread t(thread_task);
        t.join();

        return EXIT_SUCCESS;
    }  /* ----------  end of function main  ---------- */

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

更多的有关 C++11 Concurrency 的介绍将在后续的一系列博客中写出，希望自己勤快一点吧 ;-)