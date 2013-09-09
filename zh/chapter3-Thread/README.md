# 本章导读 #

本章主要内容如下：

- `<thread>` 头文件中的类及相关函数的介绍，包括创建新的线程对象、线程对象的控制和管理、与线程相关的异常处理等。
- `std::thread` 与 Pthread 等线程库的对比，包括两者编程接口的差异及其他细节。
- `std::thread` 应用实例。

# 第三章 线程详解 #


## [3.1 `<thread>` 头文件摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#thread-%E5%A4%B4%E6%96%87%E4%BB%B6%E6%91%98%E8%A6%81) ##
### [`std::thread` 类摘要](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#stdthread-%E7%B1%BB%E6%91%98%E8%A6%81) ###

## [3.2 `std::thread` 详解](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#stdthread-%E8%AF%A6%E8%A7%A3) ##
### [3.2.1 `std::thread` 构造和赋值](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#stdthread-%E6%9E%84%E9%80%A0%E5%92%8C%E8%B5%8B%E5%80%BC) ###
#### [3.2.1.1 `std::thread` 构造函数](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#stdthread-%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0) ####
#### [3.2.2.2 `std::thread` 赋值操作](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#stdthread-%E8%B5%8B%E5%80%BC%E6%93%8D%E4%BD%9C) ####
### [3.2.2 其他成员函数](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#%E5%85%B6%E4%BB%96%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0) ###

## [3.3 `std::this_thread` 命名空间中相关辅助函数介绍](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter3-Thread/Introduction-to-Thread.md#stdthis_thread-%E5%91%BD%E5%90%8D%E7%A9%BA%E9%97%B4%E4%B8%AD%E7%9B%B8%E5%85%B3%E8%BE%85%E5%8A%A9%E5%87%BD%E6%95%B0%E4%BB%8B%E7%BB%8D) ##