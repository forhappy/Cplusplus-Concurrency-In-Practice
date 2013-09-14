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

### 1. [核心语言的运行时性能强化](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/appendix%20C%2B%2B11%20standards/C%2B%2B11%20Core%20language%20runtime%20performance%20enhancements.md) ###

本小节主要包括：

1. 右值引用和 move 语义
2. 泛化的常量表达式 constexpr
3. 对 POD 类型定义的修正。

### 2. 核心语言的构建时性能强化 ###

本小节主要包括：

1. 外部模板。

### 3. 核心语言的可用性强化 ###

本小节主要包括：

1. 初始化列表(`std::initializer_list`)
2. 统一的初始化方式
3. 类型推导(auto 和 decltype 关键字)
4. 基于范围的 for 循环
5. lambda 表达式
6. 另一种可选的函数语法
7. 对象创建优化
8. 显式虚函数重载
9. 空指针常量(nullptr)
10. 强类型枚举
11. 右尖括号(>)
12. 显式类型转换操作符
13. 模板别名
14. 无限制 union。

### 4. 核心语言的功能提升 ###

本小节主要包括：

1. 变长参数模板
2. 新的字符串字面值
3. 用户自定义的字面值
4. 多线程内存模型
5. 线程本地存储
6. 显式地使用或禁用某些特殊成员函数（构造函数，拷贝构造，赋值操作符，析构等）
7. long long int类型
8. 静态断言 assertions
9. 允许 sizeof 运算符作用在类型的数据成员上，无须明确的对象
10. 垃圾回收机制
11. 属性

### 5. C++ 标准库的变更 ###

本小节主要包括：

1. 标准库组件上的升级
2. 多线程支持
3. 元组(tuple)类型
4. 散列表(hash table)
5. 正则表达式
6. 通用智能指针
7. 可扩展的随机数功能
8. 包装引用
9. 多态函数对象包装器
10. 用于元编程的类型属性
11. 用于计算函数对象返回类型的统一方法