## 3. 核心语言的可用性强化 ##

### 3.1 初始化列表(`std::initializer_list`) ###
### 3.2 统一的初始化方式 ###
### 3.3 类型推导(auto 和 decltype 关键字) ###
### 3.4 基于范围的 for 循环 ###

### 3.5 lambda 表达式 ###

C++11 新增了很多特性，lambda 表达式是其中之一。很多语言都提供了 lambda 表达式，如 Python，Java 8。lambda 表达式可以方便地构造匿名函数，如果你的代码里面存在大量的小函数，而这些函数一般只被调用一次，那么不妨将他们重构成 lambda 表达式。

<table>
<tbody>
<tr>
<td><code><strong>[</strong></code> <span>capture</span> <code><strong>]</strong></code> <code><strong>(</strong></code> <span>params</span> <code><strong>)</strong></code> <span>mutable</span> <span>exception</span> <span>attribute</span> <code><strong>-&gt;</strong></code> <span>ret</span> <code><strong>{</strong></code> <span>body</span> <code><strong>}</strong></code></td>
<td>(1)</td>
<td>&nbsp;</td>
</tr>
<tr>
<td><code><strong>[</strong></code> <span>capture</span> <code><strong>]</strong></code> <code><strong>(</strong></code> <span>params</span> <code><strong>)</strong></code> <code><strong>-&gt;</strong></code> <span>ret</span> <code><strong>{</strong></code> <span>body</span> <code><strong>}</strong></code></td>
<td>(2)</td>
<td>&nbsp;</td>
</tr>
<tr>
<td><code><strong>[</strong></code> <span>capture</span> <code><strong>]</strong></code> <code><strong>(</strong></code> <span>params</span> <code><strong>)</strong></code> <code><strong>{</strong></code> <span>body</span> <code><strong>}</strong></code></td>
<td>(3)</td>
<td>&nbsp;</td>
</tr>
<tr>
<td><code><strong>[</strong></code> <span>capture</span> <code><strong>]</strong></code> <code><strong>{</strong></code> <span>body</span> <code><strong>}</strong></code></td>
<td>(4)</td>
<td>&nbsp;</td>
</tr>
</tbody>
</table>

其中：

- (1) 是完整的 lambda 表达式形式，
- (2) const 类型的 lambda 表达式，该类型的表达式不能改捕获("capture")列表中的值。
- (3) 省略了返回值类型的 lambda 表达式，但是该 lambda 表达式的返回类型可以按照下列规则推演出来：

        (3.1) 如果 lambda 代码块中包含了 return 语句，则该 lambda 表达式的返回类型由 return 语句的返回类型确定。

        (3.2) 如果没有 return 语句，则类似 void f(...) 函数。

- (4) 省略了参数列表，类似于无参函数 f()。

`mutable` 修饰符说明 lambda 表达式体内的代码可以修改被捕获的变量，并且可以访问被捕获对象的 non-const 方法。

`exception` 说明 lambda 表达式是否抛出异常(`noexcept`)，以及抛出何种异常，类似于 `void f() throw(X, Y)`。

attribute 用来声明属性。

另外，`capture` 指定了在可见域范围内 lambda 表达式的代码内可见得外部变量的列表，具体解释如下：

- [a,&b]： a变量以值的方式呗捕获，b以引用的方式被捕获。
- [this]： 以值的方式捕获 this 指针。
- [&]： 以引用的方式捕获所有的外部自动变量。
- [=]： 以值的方式捕获所有的外部自动变量。
- []： 不捕获外部的任何变量。

此外，params 指定 lambda 表达式的参数。

请看下面 lambda 表达式的例子：

    #include <vector>
    #include <iostream>
    #include <algorithm>
    #include <functional>
     
    int main()
    {
        std::vector<int> c { 1,2,3,4,5,6,7 };
        int x = 5;
        c.erase(std::remove_if(c.begin(), c.end(), [x](int n) { return n < x; } ), c.end());
     
        std::cout << "c: ";
        for (auto i: c) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
     
        auto func1 = [](int i) { return i + 4; };
        std::cout << "func1: " << func1(6) << '\n'; 
     
        std::function<int(int)> func2 = [](int i) { return i + 4; };
        std::cout << "func2: " << func2(6) << '\n'; 
    }

### 3.6 另一种可选的函数语法 ###
### 3.7 对象创建优化 ###
### 3.8 显式虚函数重载 ###
### 3.9 空指针常量(nullptr) ###
### 3.10 强类型枚举 ###
### 3.11 右尖括号(>) ###
### 3.12 显式类型转换操作符 ###
### 3.13 模板别名 ###
### 3.14 无限制 union ###
