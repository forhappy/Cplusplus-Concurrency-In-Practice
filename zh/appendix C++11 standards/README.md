# 本章导读 #

本章主要介绍 C++11 标准的一些新特性，本文的素材主要来源于：

Bjarne Stroustrup 个人主页：

- C++11 - the new ISO C++ standard: [http://www.stroustrup.com/C++11FAQ.html](http://www.stroustrup.com/C++11FAQ.html)
- The C++ Programming Language: [http://www.stroustrup.com/C++.html](http://www.stroustrup.com/C++.html)


C++ 标准委员会：

- The C++ Standards Committee: [http://www.open-std.org/jtc1/sc22/wg21/](http://www.open-std.org/jtc1/sc22/wg21/)

维基百科：

- 英文 C++11: [http://en.wikipedia.org/wiki/C%2B%2B11](http://en.wikipedia.org/wiki/C%2B%2B11)
- 中文 C++11: [http://zh.wikipedia.org/zh-cn/C%2B%2B11](http://zh.wikipedia.org/zh-cn/C%2B%2B11)

Isocpp.org:

- [http://isocpp.org](http://isocpp.org)

Boostcon:

- [https://github.com/boostcon](https://github.com/boostcon)

按照维基百科中的分类方法，本文将对 C++11 标准的新特性按照以下四个方面来解释，分别是：

1. 核心语言的运行时性能强化
2. 核心语言的构建时性能强化
3. 核心语言的可用性强化
4. 核心语言的功能提升
5. C++ 标准库的变更

# 附录 C++11 新标准概览 #

## 1. [核心语言的运行时性能强化](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/appendix%20C%2B%2B11%20standards/C%2B%2B11%20Core%20language%20runtime%20performance%20enhancements.md) ##

本小节主要包括：

1. 右值引用和 move 语义
2. 泛化的常量表达式 constexpr
3. 对 POD 类型定义的修正。

## 2. 核心语言的构建时性能强化 ##

本小节主要包括：

1. 外部模板。

## 3. 核心语言的可用性强化 ##

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
14. 无限制 unoin。

## 4. 核心语言的功能提升 ##

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

## 5. C++ 标准库的变更 ##

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
