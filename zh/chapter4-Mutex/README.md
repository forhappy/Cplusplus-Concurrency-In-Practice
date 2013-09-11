# 本章导读 #

本章主要内容如下：

- `<mutex>` 头文件中的类及相关函数的介绍，包括互斥量、各种锁类型的介绍，以及 lock， try_lock，call_once 等函数的用法。
- `std::mutex` 与 Pthread 等线程库中的 `pthread_mutex_t` 类型的对比，包括两者编程接口的差异及其他细节。
- `std::mutex` 和 `std::lock_guard`、`std::unique_lock` 应用实例。

# 第四章 互斥量与锁 #

## 4.1 `<mutex>` 头文件摘要 ##
### 4.1.1 `std::mutex` 类摘要 ###
### 4.1.2 `std::recursive_mutex` 类摘要 ###
### 4.1.3 `std::timed_mutex` 类摘要 ###
### 4.1.4 `std::recursive_timed_mutex` 类摘要 ###
### 4.1.4 `std::lock_guard` 类摘要 ###
### 4.1.4 `std::unique_lock` 类摘要 ###

## 4.2 互斥量详解 ##
### 4.2.1 `std::mutex` 类型介绍 ###
#### 4.2.1.1 `std::mutex` 构造函数 ####
#### 4.2.1.2 `std::mutex` 赋值操作 ####
#### 4.2.1.3 其他成员函数 ####
### 4.2.2 `std::recursive_mutex` 类型介绍 ###
### 4.2.3 `std::timed_mutex` 类型介绍 ###
### 4.2.4 `std::recursive_timed_mutex` 类型介绍 ###

## 4.3 锁类型详解 ##
### 4.3.1 `std::lock_guard` 类型介绍 ###
### 4.3.2 `std::unique_lock` 类型介绍 ###

## 4.4 辅助函数介绍 ##

## 4.5 `std::mutex` 与 Pthread 对比 ##

## [4.6 资料汇](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter4-Mutex/web-resources.md) ##