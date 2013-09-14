## 1. 核心语言的运行时性能强化 ##

### 1.1 右值引用和 move 语义 ###

> 本小节主要参考了 IBM developerWorkds 上的一篇博文: 《C++11 标准新特性: 右值引用与转移语义》: [http://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/](http://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/)，在此特向原作者表示感谢。

右值引用 (Rvalue Referene) 是 C++11 标准中引入的新特性 , 它实现了转移语义(Move Sementics)和完美转发(Perfect Forwarding)。它的主要目的有两个方面：

- 消除两个对象交互时不必要的对象拷贝，节省运算存储资源，提高效率
- 能够更简洁明确地定义泛型函数。

C++( 包括 C) 中所有的表达式和变量要么是左值，要么是右值。通俗的左值的定义就是非临时对象，那些可以在多条语句中使用的对象。所有的变量都满足这个定义，在多条代码中都可以使用，都是左值。右值是指临时的对象，它们只在当前的语句中有效。

在 C++11 之前，右值是不能被引用的，最大限度就是利用常量引用来绑定一个右值，如:

    const int &a = 1; 

在这种情况下，右值不能被修改的。但是实际上右值是可以被修改的，如:

    T().set().get(); 

T 是一个类，set 是一个函数为 T 中的一个变量赋值，get 用来取出这个变量的值。在这句中，T() 生成一个临时对象，就是右值，set() 修改了变量的值，也就修改了这个右值。

既然右值可以被修改，那么就可以实现右值引用。右值引用能够方便地解决实际工程中的问题，实现非常有吸引力的解决方案。

左值的声明符号为 ”&”， 为了和左值区分，右值的声明符号为 ”&&”。

如果临时对象通过一个接受右值的函数传递给另一个函数时，就会变成左值，因为这个临时对象在传递过程中，变成了命名对象。如下示例程序：

    void process_value(int& i) { 
        std::cout << "LValue processed: " << i << std::endl; 
    } 
    
    void process_value(int&& i) { 
        std::cout << "RValue processed: " << i << std::endl; 
    } 
    
    void forward_value(int&& i) { 
        process_value(i); 
    } 
    
    int main() { 
        int a = 0; 
        process_value(a); 
        process_value(1); 
        forward_value(2); 
    }

虽然 2 这个立即数在函数 forward_value 接收时是右值，但到了 process_value 接收时，变成了左值。

C++03 性能上被长期被诟病的其中之一，就是其耗时且不必要的深度拷贝。深度拷贝会发生在当对象是以传值的方式传递。举例而言，`std::vector<T>` 是内部保存了 C-style 数组的一个包装，如果一个`std::vector<T>` 的临时对象被建构或是从函数返回，要将其存储只能通过生成新的 `std::vector<T>` 并且把该临时对象所有的数据复制进去。该临时对象和其拥有的内存会被摧毁。(为了讨论上的方便，这里忽略返回值优化)

在 C++11，一个 `std::vector` 的 "move 构造函数" 对某个 `vector` 的右值引用可以单纯地从右值复制其内部 C-style 数组的指针到新的 `std::vector`，然后留下空的右值。这个操作不需要数组的复制，而且空的临时对象的析构也不会摧毁内存。传回 `std::vector` 临时对象的函数不需要显式地传回`std::vector<T>&&`。如果 `std::vector` 没有 move 构造函数，那么复制构造函数将被调用，以 `const std::vector<T> &` 的正常形式。 如果它确实有 move 构造函数，那么就会调用 move 构造函数，能够提高程序效率。

右值引用是用来支持转移语义的。转移语义可以将资源(堆，系统对象等)从一个对象转移到另一个对象，这样能够减少不必要的临时对象的创建、拷贝以及销毁，能够大幅度提高 C++ 程序的性能。临时对象的维护(创建和销毁)对性能有严重影响。

转移语义是和拷贝语义相对的，可以类比文件的剪切与拷贝，当我们将文件从一个目录拷贝到另一个目录时，速度比剪切慢很多。

通过转移语义，临时对象中的资源能够转移其它的对象里。

在现有的 C++ 机制中，我们可以定义拷贝构造函数和赋值函数。要实现转移语义，需要定义转移构造函数，还可以定义转移赋值操作符。对于右值的拷贝和赋值会调用转移构造函数和转移赋值操作符。如果转移构造函数和转移拷贝操作符没有定义，那么就遵循现有的机制，拷贝构造函数和赋值操作符会被调用。

普通的函数和操作符也可以利用右值引用操作符实现转移语义。

以一个简单的 string 类为示例，实现拷贝构造函数和拷贝赋值操作符。

    class MyString { 
    private: 
        char* _data; 
        size_t   _len; 
        void _init_data(const char *s) { 
           _data = new char[_len+1]; 
           memcpy(_data, s, _len); 
           _data[_len] = '\0'; 
        }

    public: 
        MyString() { 
            _data = NULL; 
            _len = 0; 
        } 
   
        MyString(const char* p) { 
            _len = strlen (p); 
            _init_data(p); 
        } 
   
        MyString(const MyString& str) { 
            _len = str._len; 
            _init_data(str._data); 
            std::cout << "Copy Constructor is called! source: " << str._data << std::endl; 
        } 
   
        MyString& operator=(const MyString& str) { 
            if (this != &str) { 
                _len = str._len; 
                _init_data(str._data); 
            } 
            std::cout << "Copy Assignment is called! source: " << str._data << std::endl; 
            return *this; 
        } 
   
        virtual ~MyString() { 
            if (_data) free(_data); 
       } 
    }; 
   
    int main() { 
        MyString a; 
        a = MyString("Hello"); 
        std::vector<MyString> vec; 
        vec.push_back(MyString("World")); 
    }

运行结果 :

    Copy Assignment is called! source: Hello 
    Copy Constructor is called! source: World 

这个 string 类已经基本满足我们演示的需要。在 main 函数中，实现了调用拷贝构造函数的操作和拷贝赋值操作符的操作。MyString(“Hello”) 和 MyString(“World”) 都是临时对象，也就是右值。虽然它们是临时的，但程序仍然调用了拷贝构造和拷贝赋值，造成了没有意义的资源申请和释放的操作。如果能够直接使用临时对象已经申请的资源，既能节省资源，有能节省资源申请和释放的时间。这正是定义转移语义的目的。

我们先定义转移构造函数。

    MyString(MyString&& str) { 
        std::cout << "Move Constructor is called! source: " << str._data << std::endl; 
        _len = str._len; 
        _data = str._data; 
        str._len = 0; 
        str._data = NULL; 
    } 

和拷贝构造函数类似，需要注意几点：

1. 参数（右值）的符号必须是右值引用符号，即“&&”。
2. 参数（右值）不可以是常量，因为我们需要修改右值。
3. 参数（右值）的资源链接和标记必须修改。否则，右值的析构函数就会释放资源。转移到新对象的资源也就无效了。

现在我们定义转移赋值操作符。

    MyString& operator=(MyString&& str) { 
        std::cout << "Move Assignment is called! source: " << str._data << std::endl; 
        if (this != &str) { 
            _len = str._len; 
            _data = str._data; 
            str._len = 0; 
          str._data = NULL; 
        } 
        return *this; 
     } 

由此看出，编译器区分了左值和右值，对右值调用了转移构造函数和转移赋值操作符。节省了资源，提高了程序运行的效率。

有了右值引用和转移语义，我们在设计和实现类时，对于需要动态申请大量资源的类，应该设计转移构造函数和转移赋值函数，以提高应用程序的效率。

既然编译器只对右值引用才能调用转移构造函数和转移赋值函数，而所有命名对象都只能是左值引用，如果已知一个命名对象不再被使用而想对它调用转移构造函数和转移赋值函数，也就是把一个左值引用当做右值引用来使用，怎么做呢？标准库提供了函数 std::move，这个函数以非常简单的方式将左值引用转换为右值引用。

基于安全的理由，具名的参数将永远不被认定为右值，即使它是被如此声明的；为了获得右值必须使用 `std::move<T>()`。

完美转发适用于这样的场景：需要将一组参数原封不动的传递给另一个函数。

“原封不动”不仅仅是参数的值不变，在 C++ 中，除了参数值之外，还有一下两组属性：

左值／右值和 const/non-const。完美转发就是在参数传递过程中，所有这些属性和参数值都不能改变。在泛型函数中这样的需求非常普遍。

### 1.2 泛化的常量表达式 constexpr ###

C++ 本来就已具备常量表示式(constant expression)的概念。C++11引进关键字 constexpr 允许用户保证函数或是对象建构式是编译期常量。

constexpr 可以修饰变量，函数，和类的构造函数。

当 constexpr 修饰变量时，应满足：

- 如果该变量是某个类的对象，则它应该立即被构造，如果是基本类型，则它应该被立即赋值。
- 构造函数的参数或者赋给该变量的值必须是字面常量，constexpr 变量或 constexpr 函数。
- 如果是使用构造函数创建该变量（无论显式构造或者隐式构造），构造函数必须满足 constexpr 特性。

当 constexpr 修饰函数时，应满足：

- 该函数不能是虚函数。
- return 返回值应该是字面类型的常量。
- 该函数每个参数必须是字面类型常量。
- 函数体只能包含：
    1. null 语句。
    2. [[../static_assert|static_assert]] 声明
    3. typedef 声明或 不定义类或枚举类型的 alias(模板别名) 声明
    4. using 声明
    5. using 语句。
    6. 只能存在唯一的 return 语句，并且 return 语句只能包含字面常量，constexpr 变量或 constexpr 函数。

当 constexpr 修饰类构造函数时，应满足：

- 构造函数的每个参数必须是字面类型常量。
- 该类不能有虚基类。
- 构造函数体必须满足以下条件：

    1. null 语句。
    2. [[../static_assert|static_assert]] 声明
    3. typedef 声明或 不定义类或枚举类型的 alias(模板别名) 声明
    4. using 声明
    5. using 语句。

- 构造函数中不能有 try-语句块。
- 该类的每个基类和非静态成员变量必须是初始化。
- 每一个隐式转换必须是常量表达式。

请看下例([参考](http://en.cppreference.com/w/cpp/language/constexpr))：

    #include <iostream>
    #include <stdexcept>
     
    // constexpr functions use recursion rather than iteration
    constexpr int factorial(int n)
    {
        return n <= 1 ? 1 : (n * factorial(n-1));
    }
     
    // literal class
    class conststr {
        const char * p;
        std::size_t sz;
     public:
        template<std::size_t N>
        constexpr conststr(const char(&a)[N]) : p(a), sz(N-1) {}
        // constexpr functions signal errors by throwing exceptions from operator ?:
        constexpr char operator[](std::size_t n) const {
            return n < sz ? p[n] : throw std::out_of_range("");
        }
        constexpr std::size_t size() const { return sz; }
    };
     
    constexpr std::size_t countlower(conststr s, std::size_t n = 0,
                                                 std::size_t c = 0) {
        return n == s.size() ? c :
               s[n] >= 'a' && s[n] <= 'z' ? countlower(s, n+1, c+1) :
               countlower(s, n+1, c);
    }
     
    // output function that requires a compile-time constant, for testing
    template<int n> struct constN {
        constN() { std::cout << n << '\n'; }
    };
     
    int main()
    {
        std::cout << "4! = " ;
        constN<factorial(4)> out1; // computed at compile time
     
        volatile int k = 8; // disallow optimization using volatile
        std::cout << k << "! = " << factorial(k) << '\n'; // computed at run time
     
        std::cout << "Number of lowercase letters in \"Hello, world!\" is ";
        constN<countlower("Hello, world!")> out2; // implicitly converted to conststr
    }


### 1.3 对 POD 类型定义的修正 ###

> 本小节主要来源于[维基百科C++11](http://zh.wikipedia.org/zh-cn/C%2B%2B11)词条中的《[对POD定义的修正](http://zh.wikipedia.org/zh-cn/C%2B%2B11#.E5.B0.8DPOD.E5.AE.9A.E7.BE.A9.E7.9A.84.E4.BF.AE.E6.AD.A3)》：

在标准C++，一个结构(struct)为了能够被当成 POD，必须遵守几条规则。有很好的理由使我们想让大量的类型符合这种定义，符合这种定义的类型能够允许产生与C兼容的对象布局(object layout)。然而，C++03 的规则太严苛了。

C++11 将会放宽关于 POD 的定义。

当 class/struct 是极简的(`trivial`)、属于标准布局(standard-layout)，以及他的所有非静态(non-static)成员都是 POD 时，会被视为 POD。

一个极简的类型或结构符合以下定义：

- 极简的默认建构式。这可以使用默认建构式语法，例如 `SomeConstructor() = default;`
- 极简的复制建构式，可使用默认语法(default syntax)
- 极简的赋值运算符，可使用默认语法(default syntax)
- 极简的析构式，不可以是虚拟的(virtual)

一个标准布局(standard-layout)的类型或结构符合以下定义：

- 只有非静态的(non-static)数据成员，且这些成员也是符合标准布局的类型
- 对所有non-static成员有相同的访问控制(public, private, protected)
- 没有虚函数
- 没有虚拟基类
- 只有符合标准布局的基类
- 没有和第一个定义的non-static成员相同类型的基类
- 若非没有带有non-static成员的基类，就是最底层(继承最末位)的类型没有non-static数据成员而且至多一个带有non-static成员的基类。基本上，在该类型的继承体系中只会有一个类型带有non-static成员。
