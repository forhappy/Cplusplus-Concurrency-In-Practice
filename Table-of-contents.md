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


## 第三章 线程详解 ##


### 3.1 [`<thread>` 头文件摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#thread-%E5%A4%B4%E6%96%87%E4%BB%B6%E6%91%98%E8%A6%81) ###
#### 3.1.1 [`std::thread` 类摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#stdthread-%E7%B1%BB%E6%91%98%E8%A6%81) ####

### 3.2 [`std::thread` 详解](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#stdthread-%E8%AF%A6%E8%A7%A3) ###
#### 3.2.1 [`std::thread` 构造和赋值](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#stdthread-%E6%9E%84%E9%80%A0%E5%92%8C%E8%B5%8B%E5%80%BC) ####
##### 3.2.1.1 [`std::thread` 构造函数](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#stdthread-%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0) #####
##### 3.2.2.2 [`std::thread` 赋值操作](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#stdthread-%E8%B5%8B%E5%80%BC%E6%93%8D%E4%BD%9C) #####
#### 3.2.2 [其他成员函数](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#%E5%85%B6%E4%BB%96%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0) ####

### 3.3 [`std::this_thread` 命名空间中相关辅助函数介绍](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#stdthis_thread-%E5%91%BD%E5%90%8D%E7%A9%BA%E9%97%B4%E4%B8%AD%E7%9B%B8%E5%85%B3%E8%BE%85%E5%8A%A9%E5%87%BD%E6%95%B0%E4%BB%8B%E7%BB%8D) ###

### 3.4 `std::thread` 与 Pthread 线程对比 ###

### 3.5 [资料汇](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/web-resources.md "资料汇") ###


##第四章 互斥量与锁 ##

### 4.1 [`<mutex>` 头文件摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter4-Mutex/4.1%20Mutex-header-synopsis.md) ###
#### 4.1.1 [`std::mutex` 类摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter4-Mutex/4.1%20Mutex-header-synopsis.md#411-stdmutex-%E7%B1%BB%E6%91%98%E8%A6%81) ####
#### 4.1.2 [`std::recursive_mutex` 类摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter4-Mutex/4.1%20Mutex-header-synopsis.md#412-stdrecursive_mutex-%E7%B1%BB%E6%91%98%E8%A6%81) ####
#### 4.1.3 [`std::timed_mutex` 类摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter4-Mutex/4.1%20Mutex-header-synopsis.md#413-stdtimed_mutex-%E7%B1%BB%E6%91%98%E8%A6%81) ####
#### 4.1.4 [`std::recursive_timed_mutex` 类摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter4-Mutex/4.1%20Mutex-header-synopsis.md#414-stdrecursive_timed_mutex-%E7%B1%BB%E6%91%98%E8%A6%81) ####
#### 4.1.5 [`std::lock_guard` 类摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter4-Mutex/4.1%20Mutex-header-synopsis.md#415-stdlock_guard-%E7%B1%BB%E6%91%98%E8%A6%81) ####
#### 4.1.6 [`std::unique_lock` 类摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter4-Mutex/4.1%20Mutex-header-synopsis.md#416-stdunique_lock-%E7%B1%BB%E6%91%98%E8%A6%81) ####

### 4.2 [互斥量详解](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter4-Mutex/4.2%20Mutex-tutorial.md) ###
#### 4.2.1 `std::mutex` 类型介绍 ####
##### 4.2.1.1 `std::mutex` 构造函数 #####
##### 4.2.1.2 `std::mutex` 赋值操作 #####
##### 4.2.1.3 其他成员函数 #####
#### 4.2.2 `std::recursive_mutex` 类型介绍 ####
#### 4.2.3 `std::timed_mutex` 类型介绍 ####
#### 4.2.4 `std::recursive_timed_mutex` 类型介绍 ####

### 4.3 [锁类型详解](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter4-Mutex/4.3%20Lock-tutorial.md) ###
#### 4.3.1 `std::lock_guard` 类型介绍 ####
#### 4.3.2 `std::unique_lock` 类型介绍 ####

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

### 6.4 [Future 类型详解](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter6-Future/6.4%20Future-tutorial.md) ###

### 6.5 [与异步任务相关的类型介绍](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter6-Future/6.5%20Auxiliary-types.md) ###

### 6.6 [异步任务辅助函数 `std::async` 介绍](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter6-Future/6.6%20Auxiliary-function.md) ###

### 6.7 异步任务与多线程实例 ###

### 6.8 [资料汇](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter6-Future/web-resources.md) ###


##第七章 原子类型详解  ##


### [`std::atomic_flag` 入门介绍](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter7-Atomic/Introduction-to-Atomic-atomic_flag.md "std::atomic_flag 入门介绍") ###

### [ `std::atomic` 入门介绍](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter7-Atomic/Introduction-to-Atomic-atomic.md "std::atomic 入门介绍") ###

### [ `std::atomic` 入门介绍（续）](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter7-Atomic/Introduction-to-Atomic-atomic2.md "std::atomic 入门介绍（续）") ###

### [C++11 中 C 风格原子操作介绍](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter7-Atomic/Introduction-to-Atomic-c-style-atomic.md "C 风格原子操作介绍") ###


##第八章 C++11 内存模型 ##

### [资料汇](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter9-Memory-Order/web-resources.md "C++11 内存模型资料汇") ###

##第九章 高级线程管理 ##


##第十章 如何编写正确的并发数据结构 ##


##第十一章 并发编程应用实例 ##

### [如何利用 C++11 并发设施解决生产者消费者问题](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter10-application/Producer-Consum.md "如何利用 C++11 并发设施解决生产者消费者问题") ###


##附录 C++11 新标准概览 ##