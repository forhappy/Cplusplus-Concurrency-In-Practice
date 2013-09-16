## 3. 核心语言的可用性强化 ##

### 3.1 初始化列表(`std::initializer_list`) ###
### 3.2 统一的初始化方式 ###
### 3.3 类型推导(auto 和 decltype 关键字) ###
### 3.4 基于范围的 for 循环 ###

基于范围的for循环可以用非常简单的方式迭代集合中的每一项，C++11 标准中规定基于范围的 for 循环具有如下形式：

    for (for-range-declaration : expression) statement

基于范围的 for 语句可以构造出在某个范围内执行的循环语句，上述语句可以做如下解释：为 expression 的每个元素重复并按顺序执行 statement。例如：

    int array[5] = { 1, 2, 3, 4, 5 };
    for (int& x : array)
        x *= 2;

更完整的例子[如下](http://msdn.microsoft.com/zh-cn/library/jj203382.ASPX)：

    #include <iostream>
    #include <vector>
    using namespace std;
    
    int main() 
    {
        // Basic 10-element integer array.
        int x[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    
        // Range-based for loop to iterate through the array.
        for( int y : x ) { // Access by value using a copy declared as a specific type. 
                           // Not preferred.
            cout << y << " ";
        }
        cout << endl;
    
        // The auto keyword causes type inference to be used. Preferred.
    
        for( auto y : x ) { // Copy of 'x', almost always undesirable
            cout << y << " ";
        }
        cout << endl;
    
        for( auto &y : x ) { // Type inference by reference.
            // Observes and/or modifies in-place. Preferred when modify is needed.
            cout << y << " ";
        }
        cout << endl;
    
        for( const auto &y : x ) { // Type inference by reference.
            // Observes in-place. Preferred when no modify is needed.
            cout << y << " ";
        }
        cout << endl;
        cout << "end of integer array test" << endl;
        cout << endl;
    
        // Create a vector object that contains 10 elements.
        vector<double> v;
        for (int i = 0; i < 10; ++i) {
            v.push_back(i + 0.14159);
        }
    
        // Range-based for loop to iterate through the vector, observing in-place.
        for( const auto &j : v ) {
            cout << j << " ";
        }
        cout << endl;
        cout << "end of vector test" << endl;
    }

基于范围的 for 循环语句在如下条件下会退出执行，1、`break`，2、`return`，3、`goto` 至该 for 循环语句之外某一的标签语句处。

注意，基于范围的 for 语句会：

- 自动识别数组。
- 自动识别具有 .begin() 和 .end() 成员函数的容器。
- 对于其他类型，需使用依赖于参数的 `begin()` 和 `end()`。
- 如果要在循环中修改数组或容器的每个元素，可使用引用类型。

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

- [a,&b]： a变量以值的方式被捕获，b以引用的方式被捕获。
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

标准 C++03 的语法分析器一律将 ">>" 视为右移运算符。 但在模板定义式中，很多情况下 ">>" 其实代表了两个连续右角括号。C++11 新标准不在要求声明嵌套模板时使用空格将尖括号分开。

### 3.12 显式类型转换操作符 ###
### 3.13 模板别名 ###
### 3.14 无限制 union ###
