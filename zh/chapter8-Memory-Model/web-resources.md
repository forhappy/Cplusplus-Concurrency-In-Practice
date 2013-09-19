# C++ 多线程与内存模型资料汇 #

## [Bartosz Milewski's Programming Cafe](http://bartoszmilewski.com/ "Bartosz Milewski's Programming Cafe") ##

- The Language of Concurrency Video: [http://bartoszmilewski.com/2011/06/27/the-language-of-concurrency-video/](http://bartoszmilewski.com/2011/06/27/the-language-of-concurrency-video/)

- C++ atomics and memory ordering: [http://bartoszmilewski.com/2008/12/01/c-atomics-and-memory-ordering/](http://bartoszmilewski.com/2008/12/01/c-atomics-and-memory-ordering/)

- Who ordered memory fences on an x86?: [http://bartoszmilewski.com/2008/11/05/who-ordered-memory-fences-on-an-x86/](http://bartoszmilewski.com/2008/11/05/who-ordered-memory-fences-on-an-x86/)

- Who ordered sequential consistency?: [http://bartoszmilewski.com/2008/11/11/who-ordered-sequential-consistency/](http://bartoszmilewski.com/2008/11/11/who-ordered-sequential-consistency/)

- The Future of C++ Concurrency and Parallelism: [http://bartoszmilewski.com/2012/05/11/the-future-of-c-concurrency-and-parallelism/](http://bartoszmilewski.com/2012/05/11/the-future-of-c-concurrency-and-parallelism/)

- Beyond Locks: Software Transactional Memory: [http://bartoszmilewski.com/2010/09/11/beyond-locks-software-transactional-memory/](http://bartoszmilewski.com/2010/09/11/beyond-locks-software-transactional-memory/)

- Data Races at the Processor Level: [http://bartoszmilewski.com/2011/08/15/data-races-at-the-processor-level/](http://bartoszmilewski.com/2011/08/15/data-races-at-the-processor-level/)

- Async Tasks in C++11: Not Quite There Yet: [http://bartoszmilewski.com/2011/10/10/async-tasks-in-c11-not-quite-there-yet/](http://bartoszmilewski.com/2011/10/10/async-tasks-in-c11-not-quite-there-yet/)

- Race-free Multithreading : Owner polymorphism： [http://bartoszmilewski.com/2009/06/15/race-free-multithreading-owner-polymorphism/](http://bartoszmilewski.com/2009/06/15/race-free-multithreading-owner-polymorphism/)

- Race-free Multithreading: Ownership: [http://bartoszmilewski.com/2009/06/02/race-free-multithreading-ownership/](http://bartoszmilewski.com/2009/06/02/race-free-multithreading-ownership/)

- Thin Lock vs. Futex: [http://bartoszmilewski.com/2008/09/01/thin-lock-vs-futex/](http://bartoszmilewski.com/2008/09/01/thin-lock-vs-futex/)

- Thin Lock Implementation: [http://bartoszmilewski.com/2008/08/16/thin-lock-implementation/](http://bartoszmilewski.com/2008/08/16/thin-lock-implementation/)


## [Preshing on programming](http://preshing.com/) ##

- Memory Reordering Caught in the Act: [http://preshing.com/20120515/memory-reordering-caught-in-the-act](http://preshing.com/20120515/memory-reordering-caught-in-the-act)

- An Introduction to Lock-Free Programming: [http://preshing.com/20120612/an-introduction-to-lock-free-programming](http://preshing.com/20120612/an-introduction-to-lock-free-programming)

- Memory Ordering at Compile Time: [http://preshing.com/20120625/memory-ordering-at-compile-time](http://preshing.com/20120625/memory-ordering-at-compile-time)

- Memory Barriers Are Like Source Control Operations: [http://preshing.com/20120710/memory-barriers-are-like-source-control-operations](http://preshing.com/20120710/memory-barriers-are-like-source-control-operations)

- Acquire and Release Semantics: [http://preshing.com/20120913/acquire-and-release-semantics](http://preshing.com/20120913/acquire-and-release-semantics)

- Weak vs. Strong Memory Models: [http://preshing.com/20120930/weak-vs-strong-memory-models](http://preshing.com/20120930/weak-vs-strong-memory-models)

- This Is Why They Call It a Weakly-Ordered CPU: [http://preshing.com/20121019/this-is-why-they-call-it-a-weakly-ordered-cpu](http://preshing.com/20121019/this-is-why-they-call-it-a-weakly-ordered-cpu)

- Atomic vs. Non-Atomic Operations: [http://preshing.com/20130618/atomic-vs-non-atomic-operations](http://preshing.com/20130618/atomic-vs-non-atomic-operations)

- The Happens-Before Relation: [http://preshing.com/20130702/the-happens-before-relation](http://preshing.com/20130702/the-happens-before-relation)

- The Synchronizes-With Relation: [http://preshing.com/20130823/the-synchronizes-with-relation](http://preshing.com/20130823/the-synchronizes-with-relation)

## [parallellabs.com](http://www.parallellabs.com) ##

- 浅析C++多线程内存模型: [http://www.parallellabs.com/2011/08/27/c-plus-plus-memory-model/](http://www.parallellabs.com/2011/08/27/c-plus-plus-memory-model/)
- 为什么程序员需要关心顺序一致性（Sequential Consistency）而不是Cache一致性（Cache Coherence？）:[http://www.parallellabs.com/2010/03/06/why-should-programmer-care-about-sequential-consistency-rather-than-cache-coherence/](http://www.parallellabs.com/2010/03/06/why-should-programmer-care-about-sequential-consistency-rather-than-cache-coherence/)
- 多线程程序中操作的原子性: [http://www.parallellabs.com/2010/04/15/atomic-operation-in-multithreaded-application/](http://www.parallellabs.com/2010/04/15/atomic-operation-in-multithreaded-application/)
- 并行编程中的“锁”难题: [http://www.parallellabs.com/2011/10/02/lock-in-parallel-programming/](http://www.parallellabs.com/2011/10/02/lock-in-parallel-programming/)
- Pthreads并行编程之spin lock与mutex性能对比分析: [http://www.parallellabs.com/2010/01/31/pthreads-programming-spin-lock-vs-mutex-performance-analysis/](http://www.parallellabs.com/2010/01/31/pthreads-programming-spin-lock-vs-mutex-performance-analysis/)
- 多核与异步并行: [http://www.parallellabs.com/2013/01/21/multicore-and-asynchronous-communication/](http://www.parallellabs.com/2013/01/21/multicore-and-asynchronous-communication/)
- 多线程队列的算法优化: [http://www.parallellabs.com/2010/10/25/practical-concurrent-queue-algorithm/](http://www.parallellabs.com/2010/10/25/practical-concurrent-queue-algorithm/)
- 剖析为什么在多核多线程程序中要慎用volatile关键字？: [http://www.parallellabs.com/2010/12/04/why-should-we-be-care-of-volatile-keyword-in-multithreaded-applications/](http://www.parallellabs.com/2010/12/04/why-should-we-be-care-of-volatile-keyword-in-multithreaded-applications/)
- 多线程程序常见Bug剖析（上）: [http://www.parallellabs.com/2010/11/13/concurrency-bugs-1/](http://www.parallellabs.com/2010/11/13/concurrency-bugs-1/)
- 多线程程序常见Bug剖析（下）: [http://www.parallellabs.com/2010/11/23/concurrency-bugs-2/](http://www.parallellabs.com/2010/11/23/concurrency-bugs-2/)

## 其他资源 ##

- Threads and memory model for C++: [http://www.hpl.hp.com/personal/Hans_Boehm/c++mm/](http://www.hpl.hp.com/personal/Hans_Boehm/c++mm/)

- 内存屏障什么的: [http://www.spongeliu.com/233.html](http://www.spongeliu.com/233.html)

- 《C++0x漫谈》系列之：多线程内存模型：[http://blog.csdn.net/pongba/article/details/1659952](http://blog.csdn.net/pongba/article/details/1659952)

- Lock-Free Algorithms: An Introduction: [http://concurrencykit.org/presentations/lockfree_introduction/index.html](http://concurrencykit.org/presentations/lockfree_introduction/index.html)

- Introduction to Lock-Free Algorithms: Through a case study: [http://concurrencykit.org/presentations/lf1/lf1.pdf
](http://concurrencykit.org/presentations/lf1/lf1.pdf)
