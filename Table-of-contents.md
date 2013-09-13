# C++ 并发编程指南 #
本书计划分为 11 章, 分别如下安排:

## 第一章 并发编程基础 ##

### 1.1 什么是并发编程 ###
### 1.2 并发与并行的区别和联系 ###
### 1.3 为什么需要并发编程 ###
### 1.4 并发编程应用场景和经典示例 ###
### 1.5 [C++ 并发编程初探](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter1-Introduction/Cplusplus-Concurrency-Introduction.md) ###
### 1.6 [资料汇](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter1-Introduction/web-resources.md) ###


## 第二章 几种常见的多线程库介绍 ##

### 2.1 Pthread 多线程编程指南 ###

### 2.2 Windows 多线程编程指南 ###

### 2.3 几种常见的多线程库接口对比 ###

### 2.4 资料汇 ###


## 第三章 线程详解 ##

### 3.1 [`<thread>` 头文件摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#thread-%E5%A4%B4%E6%96%87%E4%BB%B6%E6%91%98%E8%A6%81) ###

### 3.2 [`std::thread` 详解](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#stdthread-%E8%AF%A6%E8%A7%A3) ###

### 3.3 [`std::this_thread` 命名空间中相关辅助函数介绍](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#stdthis_thread-%E5%91%BD%E5%90%8D%E7%A9%BA%E9%97%B4%E4%B8%AD%E7%9B%B8%E5%85%B3%E8%BE%85%E5%8A%A9%E5%87%BD%E6%95%B0%E4%BB%8B%E7%BB%8D) ###

### 3.4 `std::thread` 与 Pthread 线程对比 ###

### 3.5 [资料汇](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/web-resources.md "资料汇") ###


##第四章 互斥量与锁 ##

### 4.1 [`<mutex>` 头文件摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter4-Mutex/4.1%20Mutex-header-synopsis.md) ###

### 4.2 [互斥量详解](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter4-Mutex/4.2%20Mutex-tutorial.md) ###

### 4.3 [锁类型详解](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter4-Mutex/4.3%20Lock-tutorial.md) ###

### 4.4 辅助函数介绍 ###

### 4.5 `std::mutex` 与 Pthread 互斥量对比 ###

### 4.6 [资料汇](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter4-Mutex/web-resources.md) ###


##第五章 条件变量与线程同步 ##

### 5.1 [`<condition_variable>` 头文件摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter5-Condition-Variable/5.1%20Condition-variable%20header%20synopsis.md) ###

### 5.2 [条件变量详解](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter5-Condition-Variable/5.2%20Condition-variable-tutorial.md) ###

### 5.3 [辅助函数介绍](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter5-Condition-Variable/5.3%20Auxiliary-function.md) ###

### 5.4 利用条件变量（std::condition_variable）进行线程同步 ###

### 5.5 `std::condition_variable` 与 Pthread 条件变量对比 ###

### 5.6 [资料汇](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter5-Condition-Variable/web-resources.md) ###


##第六章 异步任务详解 ##

### 6.1 [`<future>` 头文件摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter6-Future/6.1%20Future-header-synopsis.md) ###

### 6.2 [异步任务提供者(Provider) 介绍](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter6-Future/6.2%20Providers-tutorial.md) ###

### 6.3 [异步任务提供者(Provider) 介绍（续）](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter6-Future/6.3%20Providers-tutorial-2.md) ###

### 6.4 [异步任务 Future 类型详解](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter6-Future/6.4%20Future-tutorial.md) ###

### 6.5 [与异步任务相关的类型介绍](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter6-Future/6.5%20Auxiliary-types.md) ###

### 6.6 [异步任务辅助函数 `std::async` 介绍](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter6-Future/6.6%20Auxiliary-function.md) ###

### 6.7 异步任务与多线程实例 ###

### 6.8 [资料汇](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter6-Future/web-resources.md) ###


##第七章 原子类型详解  ##

### 7.1 [`<atomic>` 头文件摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter7-Atomic/7.1%20Atomic-header-synopsis.md) ###

### 7.2 [`std::atomic_flag` 详解](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter7-Atomic/7.2%20Atomic-flag-tutorial.md) ###

### 7.3 [基本 `std::atomic` 类型详解](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter7-Atomic/7.3%20Atomic-tutorial.md) ###

### 7.4 [特化的 `std::atomic` 类型详解](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter7-Atomic/7.4%20Atomic-tutorial2.md) ###

### 7.5 [C 风格的原子操作](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter7-Atomic/7.5%20C-style-atomic.md) ###

### 7.6 C++11 内存模型初探 ###

### 7.7 如何利用原子类型设计并发数据结构 ###

### 7.8 [资料汇](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter7-Atomic/web-resources.md) ###


##第八章 C++11 内存模型 ##

### 8.1 [资料汇](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter8-Memory-Order/web-resources.md "C++11 内存模型资料汇") ###


##第九章 高级线程管理 ##


##第十章 如何编写正确的并发数据结构 ##


##第十一章 并发编程应用实例 ##

### 11.1 [利用 C++11 并发设施解决生产者消费者问题](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter11-Application/11.1%20Producer-Consumer-solution.md "如何利用 C++11 并发设施解决生产者消费者问题") ###


##附录 C++11 新标准概览 ##