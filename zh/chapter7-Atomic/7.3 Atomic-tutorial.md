[C++11 并发指南七(atomic 类型详解一 atomic_flag 介绍)](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter7-Atomic/Introduction-to-Atomic-atomic_flag.md) 一文介绍了 C++11 中最简单的原子类型 `std::atomic_flag`，但是 `std::atomic_flag` 过于简单，只提供了 `test_and_set` 和 `clear` 两个 API，不能满足其他需求(如 `store`, `load`, `exchange`, `compare_exchange` 等)，因此本文将介绍功能更加完善的 `std::atomic` 类。

# std::atomic 基本介绍 #

`std::atomic` 是模板类，一个模板类型为 T 的原子对象中封装了一个类型为 T 的值。

    template <class T> struct atomic;

原子类型对象的主要特点就是从不同线程访问不会导致数据竞争(data race)。因此从不同线程访问某个原子对象是良性 (`well-defined`) 行为，而通常对于非原子类型而言，并发访问某个对象（如果不做任何同步操作）会导致未定义 (`undifined`) 行为发生。

C++11 标准中的基本 `std::atomic` 模板定义如下：

    template < class T > struct atomic {
        bool is_lock_free() const volatile;
        bool is_lock_free() const;
        void store(T, memory_order = memory_order_seq_cst) volatile;
        void store(T, memory_order = memory_order_seq_cst);
        T load(memory_order = memory_order_seq_cst) const volatile;
        T load(memory_order = memory_order_seq_cst) const;
        operator  T() const volatile;
        operator  T() const;
        T exchange(T, memory_order = memory_order_seq_cst) volatile;
        T exchange(T, memory_order = memory_order_seq_cst);
        bool compare_exchange_weak(T &, T, memory_order, memory_order) volatile;
        bool compare_exchange_weak(T &, T, memory_order, memory_order);
        bool compare_exchange_strong(T &, T, memory_order, memory_order) volatile;
        bool compare_exchange_strong(T &, T, memory_o    rder, memory_order);
        bool compare_exchange_weak(T &, T, memory_order = memory_order_seq_cst) volatile;
        bool compare_exchange_weak(T &, T, memory_order = memory_order_seq_cst);
        bool compare_exchange_strong(T &, T, memory_order = memory_order_seq_cst) volatile;
        bool compare_exchange_strong(T &, T, memory_order = memory_order_seq_cst);
        atomic() = default;
        constexpr atomic(T);
        atomic(const atomic &) = delete;
        atomic & operator=(const atomic &) = delete;
        atomic & operator=(const atomic &) volatile = delete;
        T operator=(T) volatile;
        T operator=(T);
    };

另外，C++11 标准库 `std::atomic` 提供了针对整形(`integral`)和指针类型的特化实现，分别定义如下：

针对整形(`integral`)的特化，其中 integal 代表了如下类型 `char`, `signed char`, `unsigned char`, `short`, `unsigned short`, `int`, `unsigned int`, `long`, `unsigned long`, `long long`, `unsigned long long`, `char16_t`, `char32_t`, `wchar_t`：

    template <> struct atomic<integral> {
        bool is_lock_free() const volatile;
        bool is_lock_free() const;
     
        void store(integral, memory_order = memory_order_seq_cst) volatile;
        void store(integral, memory_order = memory_order_seq_cst);
     
        integral load(memory_order = memory_order_seq_cst) const volatile;
        integral load(memory_order = memory_order_seq_cst) const;
     
        operator integral() const volatile;
        operator integral() const;
     
        integral exchange(integral, memory_order = memory_order_seq_cst) volatile;
        integral exchange(integral, memory_order = memory_order_seq_cst);
     
        bool compare_exchange_weak(integral&, integral, memory_order, memory_order) volatile;
        bool compare_exchange_weak(integral&, integral, memory_order, memory_order);
     
        bool compare_exchange_strong(integral&, integral, memory_order, memory_order) volatile;
        bool compare_exchange_strong(integral&, integral, memory_order, memory_order);
     
        bool compare_exchange_weak(integral&, integral, memory_order = memory_order_seq_cst) volatile;
        bool compare_exchange_weak(integral&, integral, memory_order = memory_order_seq_cst);
     
        bool compare_exchange_strong(integral&, integral, memory_order = memory_order_seq_cst) volatile;
        bool compare_exchange_strong(integral&, integral, memory_order = memory_order_seq_cst);
     
        integral fetch_add(integral, memory_order = memory_order_seq_cst) volatile;
        integral fetch_add(integral, memory_order = memory_order_seq_cst);
     
        integral fetch_sub(integral, memory_order = memory_order_seq_cst) volatile;
        integral fetch_sub(integral, memory_order = memory_order_seq_cst);
     
        integral fetch_and(integral, memory_order = memory_order_seq_cst) volatile;
        integral fetch_and(integral, memory_order = memory_order_seq_cst);
     
        integral fetch_or(integral, memory_order = memory_order_seq_cst) volatile;
        integral fetch_or(integral, memory_order = memory_order_seq_cst);
     
        integral fetch_xor(integral, memory_order = memory_order_seq_cst) volatile;
        integral fetch_xor(integral, memory_order = memory_order_seq_cst);
         
        atomic() = default;
        constexpr atomic(integral);
        atomic(const atomic&) = delete;
     
        atomic& operator=(const atomic&) = delete;
        atomic& operator=(const atomic&) volatile = delete;
         
        integral operator=(integral) volatile;
        integral operator=(integral);
         
        integral operator++(int) volatile;
        integral operator++(int);
        integral operator--(int) volatile;
        integral operator--(int);
        integral operator++() volatile;
        integral operator++();
        integral operator--() volatile;
        integral operator--();
        integral operator+=(integral) volatile;
        integral operator+=(integral);
        integral operator-=(integral) volatile;
        integral operator-=(integral);
        integral operator&=(integral) volatile;
        integral operator&=(integral);
        integral operator|=(integral) volatile;
        integral operator|=(integral);
        integral operator^=(integral) volatile;
        integral operator^=(integral);
    };

针对指针的特化：

    template <class T> struct atomic<T*> {
        bool is_lock_free() const volatile;
        bool is_lock_free() const;
     
        void store(T*, memory_order = memory_order_seq_cst) volatile;
        void store(T*, memory_order = memory_order_seq_cst);
     
        T* load(memory_order = memory_order_seq_cst) const volatile;
        T* load(memory_order = memory_order_seq_cst) const;
     
        operator T*() const volatile;
        operator T*() const;
     
        T* exchange(T*, memory_order = memory_order_seq_cst) volatile;
        T* exchange(T*, memory_order = memory_order_seq_cst);
     
        bool compare_exchange_weak(T*&, T*, memory_order, memory_order) volatile;
        bool compare_exchange_weak(T*&, T*, memory_order, memory_order);
     
        bool compare_exchange_strong(T*&, T*, memory_order, memory_order) volatile;
        bool compare_exchange_strong(T*&, T*, memory_order, memory_order);
     
        bool compare_exchange_weak(T*&, T*, memory_order = memory_order_seq_cst) volatile;
        bool compare_exchange_weak(T*&, T*, memory_order = memory_order_seq_cst);
     
        bool compare_exchange_strong(T*&, T*, memory_order = memory_order_seq_cst) volatile;
        bool compare_exchange_strong(T*&, T*, memory_order = memory_order_seq_cst);
     
        T* fetch_add(ptrdiff_t, memory_order = memory_order_seq_cst) volatile;
        T* fetch_add(ptrdiff_t, memory_order = memory_order_seq_cst);
     
        T* fetch_sub(ptrdiff_t, memory_order = memory_order_seq_cst) volatile;
        T* fetch_sub(ptrdiff_t, memory_order = memory_order_seq_cst);
     
        atomic() = default;
        constexpr atomic(T*);
        atomic(const atomic&) = delete;
     
        atomic& operator=(const atomic&) = delete;
        atomic& operator=(const atomic&) volatile = delete;
     
        T* operator=(T*) volatile;
        T* operator=(T*);
        T* operator++(int) volatile;
        T* operator++(int);
        T* operator--(int) volatile;
        T* operator--(int);
        T* operator++() volatile;
        T* operator++();
        T* operator--() volatile;
        T* operator--();
        T* operator+=(ptrdiff_t) volatile;
        T* operator+=(ptrdiff_t);
        T* operator-=(ptrdiff_t) volatile;
        T* operator-=(ptrdiff_t);
    };    

# `std::atomic` 成员函数 #

好了，对 `std::atomic` 有了一个最基本认识之后我们来看 `std::atomic` 的成员函数吧。

## `std::atomic` 构造函数 ##

`std::atomic` 的构造函数如下：

<table>
<tr class="odd"><th>default (1)</th>
<td>atomic() noexcept = default;</td>
</tr>
<tr class="even"><th>initialization (2)</th>
<td>constexpr atomic (T val) noexcept;</td>
</tr>
<tr class="odd"><th>copy [deleted] (3)</th>
<td>atomic (const atomic&amp;) = delete;</td>
</tr>
</table>

1. 默认构造函数，由默认构造函数创建的 `std::atomic` 对象处于未初始化(`uninitialized`)状态，对处于未初始化(`uninitialized`)状态 `std::atomic` 对象可以由 `atomic_init` 函数进行初始化。
2. 初始化构造函数，由类型 T初始化一个 `std::atomic` 对象。
3. 拷贝构造函数被禁用。

请看下例：

    #include <iostream>       // std::cout
    #include <atomic>         // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
    #include <thread>         // std::thread, std::this_thread::yield
    #include <vector>         // std::vector
     
    // 由 false 初始化一个 std::atomic<bool> 类型的原子变量
    std::atomic<bool> ready(false);
    std::atomic_flag winner = ATOMIC_FLAG_INIT;
     
    void do_count1m(int id)
    {
        while (!ready) { std::this_thread::yield(); } // 等待 ready 变为 true.
     
        for (volatile int i=0; i<1000000; ++i) {} // 计数
     
        if (!winner.test_and_set()) {
          std::cout << "thread #" << id << " won!\n";
        }
    }
     
    int main ()
    {
        std::vector<std::thread> threa    ds;
        std::cout << "spawning 10 threads that count to 1 million...\n";
        for (int i=1; i<=10; ++i) threads.push_back(std::thread(count1m,i));
        ready = true;
     
        for (auto& th : threads) th.join();
        return 0;
    }

## std::atomic::operator=() 函数 ##

`std::atomic` 的赋值操作函数定义如下：

<table>
<tr class="odd"><th>set value (1)</th>
<td>
<pre>T operator= (T val) noexcept;
T operator= (T val) volatile noexcept;
</pre>
</td>
</tr>
<tr class="even"><th>copy [deleted] (2)</th>
<td>
<pre>atomic&amp; operator= (const atomic&amp;) = delete;
atomic&amp; operator= (const atomic&amp;) volatile = delete;</pre>
</td>
</tr>
</table>

可以看出，普通的赋值拷贝操作已经被禁用。但是一个类型为 T 的变量可以赋值给相应的原子类型变量（相当与隐式转换），该操作是原子的，内存序(Memory Order) 默认为顺序一致性(`std::memory_order_seq_cst`)，如果需要指定其他的内存序，需使用 `std::atomic::store()`。

    #include <iostream>             // std::cout
    #include <atomic>               // std::atomic
    #include <thread>               // std::thread, std::this_thread::yield
     
    std::atomic <int> foo = 0;
     
    void set_foo(int x)
    {
        foo = x; // 调用 std::atomic::operator=().
    }
     
    void print_foo()
    {
        while (foo == 0) { // wait while foo == 0
            std::this_thread::yield();
        }
        std::cout << "foo: " << foo << '\n';
    }
     
    int main()
    {
        std::thread first(print_foo);
        std::thread second(set_foo, 10);
        first.join();
        second.join();
        return 0;
    }

## 基本 std::atomic 类型操作 ##

本节主要介绍基本 `std::atomic` 类型所具备的操作（即成员函数）。我们知道 `std::atomic` 是模板类，一个模板类型为 T 的原子对象中封装了一个类型为 T 的值。本文`<std::atomic 基本介绍>`一节中也提到了 `std::atomic` 类模板除了基本类型以外，还针对整形和指针类型做了特化。 特化的 `std::atomic` 类型支持更多的操作，如 `fetch_add`, `fetch_sub`, `fetch_and` 等。本小节介绍基本 `std::atomic` 类型所具备的操作：

### `is_lock_free` ###

    bool is_lock_free() const volatile noexcept;
    bool is_lock_free() const noexcept;

判断该 `std::atomic` 对象是否具备 lock-free 的特性。如果某个对象满足 lock-free 特性，在多个线程访问该对象时不会导致线程阻塞。(可能使用某种事务内存transactional memory 方法实现 lock-free 的特性)。

### `store` ###

    void store (T val, memory_order sync = memory_order_seq_cst) volatile noexcept;
    void store (T val, memory_order sync = memory_order_seq_cst) noexcept;

修改被封装的值，`std::atomic::store` 函数将类型为 T 的参数 `val` 复制给原子对象所封装的值。T 是 `std::atomic` 类模板参数。另外参数 `sync` 指定内存序(Memory Order)，可能的取值如下：


<table class="boxed">
<tr><th style="text-align: center;">Memory Order 值</th><th style="text-align: center;">Memory Order 类型</th></tr>
<tr>
<td style="text-align: center;"><samp>memory_order_relaxed</samp></td>
<td style="text-align: center;">Relaxed</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_release</samp></td>
<td style="text-align: center;">Release</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_seq_cst</samp></td>
<td style="text-align: center;">Sequentially consistent</td>
</tr>
</table>

请看下面例子：

    #include <iostream>       // std::cout
    #include <atomic>         // std::atomic, std::memory_order_relaxed
    #include <thread>         // std::thread
     
    std::atomic<int> foo(0); // 全局的原子对象 foo
     
    void set_foo(int x)
    {
        foo.store(x, std::memory_order_relaxed); // 设置(store) 原子对象 foo 的值
    }
     
    void print_foo()
    {
        int x;
        do {
            x = foo.load(std::memory_order_relaxed); // 读取(load) 原子对象 foo 的值
        } while (x == 0);
        std::cout << "foo: " << x << '\n';
    }
     
    int main ()
    {
        std::thread first(print_foo); // 线程 first 打印 foo 的值
        std::thread second(set_foo, 10); // 线程 second 设置 foo 的值
        first.join();
        second.join();
        return 0;
    }

### `load` ###

    T load (memory_order sync = memory_order_seq_cst) const volatile noexcept;
    T load (memory_order sync = memory_order_seq_cst) const noexcept;

读取被封装的值，参数 `sync` 设置内存序(Memory Order)，可能的取值如下：

<table class="boxed">
<tr><th style="text-align: center;">Memory Order 值</th><th style="text-align: center;">Memory Order 类型</th></tr>
<tr>
<td style="text-align: center;"><samp>memory_order_relaxed</samp></td>
<td style="text-align: center;">Relaxed</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_consume</samp></td>
<td style="text-align: center;">Consume</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_acquire</samp></td>
<td style="text-align: center;">Acquire</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_seq_cst</samp></td>
<td style="text-align: center;">Sequentially consistent</td>
</tr>
</table>

请看下面例子：

    #include <iostream>       // std::cout
    #include <atomic>         // std::atomic, std::memory_order_relaxed
    #include <thread>         // std::thread
     
    std::atomic<int> foo(0); // 全局的原子对象 foo
     
    void set_foo(int x)
    {
        foo.store(x, std::memory_order_relaxed); // 设置(store) 原子对象 foo 的值
    }
     
    void print_foo()
    {
        int x;
        do {
            x = foo.load(std::memory_order_relaxed); // 读取(load) 原子对象 foo 的值
        } while (x == 0);
        std::cout << "foo: " << x << '\n';
    }
     
    int main ()
    {
        std::thread first(print_foo); // 线程 first 打印 foo 的值
        std::thread second(set_foo, 10); // 线程 second 设置 foo 的值
        first.join();
        second.join();
        return 0;
    }

### `operator T` ###

    operator T() const volatile noexcept;
    operator T() const noexcept;

与 `load` 功能类似，也是读取被封装的值，`operator T()` 是类型转换(`type-cast`)操作，默认的内存序是 `std::memory_order_seq_cst`，如果需要指定其他的内存序，你应该使用 `load()` 函数。请看下面例子：

    #include <iostream>       // std::cout
    #include <atomic>         // std::atomic
    #include <thread>         // std::thread, std::this_thread::yield
     
    std::atomic<int> foo = 0;
    std::atomic<int> bar = 0;
     
    void set_foo(int x)
    {
        foo = x;
    }    
     
    void copy_foo_to_bar()
    {
     
        // 如果 foo == 0，则该线程 yield,
        // 在 foo == 0 时, 实际也是隐含了类型转换操作,
        // 因此也包含了 operator T() const 的调用.
        while (foo == 0) std::this_thread::yield();
     
        // 实际调用了 operator T() const, 将foo 强制转换成 int 类型,
        // 然后调用 operator=().
        bar = static_cast<int>(foo);
    }
     
    void print_bar()
    {
        // 如果 bar == 0，则该线程 yield,
        // 在 bar == 0 时, 实际也是隐含了类型转换操作,
        // 因此也包含了 operator T() const 的调用.
        while (bar == 0) std::this_thread::yield();
        std::cout << "bar: " << bar << '\n';
    }
     
    int main ()
    {
        std::thread first(print_bar);
        std::thread second(set_foo, 10);
        std::thread third(copy_foo_to_bar);
     
        first.join();
        second.join();
        third.join();
        return 0;
    }

### `exchange` ###

    T exchange (T val, memory_order sync = memory_order_seq_cst) volatile noexcept;
    T exchange (T val, memory_order sync = memory_order_seq_cst) noexcept;

读取并修改被封装的值，`exchange` 会将 `val` 指定的值替换掉之前该原子对象封装的值，并返回之前该原子对象封装的值，整个过程是原子的(因此 `exchange` 操作也称为 read-modify-write 操作)。`sync` 参数指定内存序(Memory Order)，可能的取值如下：

<table class="boxed">
<tr><th style="text-align: center;">Memory Order 值</th><th style="text-align: center;">Memory Order 类型</th></tr>
<tr>
<td style="text-align: center;"><samp>memory_order_relaxed</samp></td>
<td style="text-align: center;">Relaxed</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_consume</samp></td>
<td style="text-align: center;">Consume</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_acquire</samp></td>
<td style="text-align: center;">Acquire</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_release</samp></td>
<td style="text-align: center;">Release</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_acq_rel</samp></td>
<td style="text-align: center;">Acquire/Release</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_seq_cst</samp></td>
<td style="text-align: center;">Sequentially consistent</td>
</tr>
</table>

请看下面例子，各个线程计数至 1M，首先完成计数任务的线程打印自己的 ID，

    #include <iostream>       // std::cout
    #include <atomic>         // std::atomic
    #include <thread>         // std::thread
    #include <vector>         // std::vector
     
    std::atomic<bool> ready(false);
    std::atomic<bool> winner(false);
     
    void count1m (int id)
    {
        while (!ready) {}                  // wait for the ready signal
        for (int i = 0; i < 1000000; ++i) {}   // go!, count to 1 million
        if (!winner.exchange(true)) { std::cout << "thread #" << id << " won!\n"; }
    };
     
    int main ()
    {
        std::vector<std::thread> threads;
        std::cout << "spawning 10 threads that count to 1 million...\n";
        for (int i = 1; i <= 10; ++i) threads.push_back(std::thread(count1m,i));
        ready = true;
        for (auto& th : threads) th.join();
     
        return 0;
    }

### `compare_exchange_weak` ###

<table>
<tr class="odd"><th>(1)</th>
<td>
<pre>bool compare_exchange_weak (T&amp; expected, T val,
           memory_order sync = memory_order_seq_cst) volatile noexcept;
bool compare_exchange_weak (T&amp; expected, T val,
           memory_order sync = memory_order_seq_cst) noexcept;
</pre>
</td>
</tr>
<tr class="even"><th>(2)</th>
<td>
<pre>bool compare_exchange_weak (T&amp; expected, T val,
           memory_order success, memory_order failure) volatile noexcept;
bool compare_exchange_weak (T&amp; expected, T val,
           memory_order success, memory_order failure) noexcept;</pre>
</td>
</tr>
</table>

比较并交换被封装的值(`weak`)与参数 `expected` 所指定的值是否相等，如果：

1. 相等，则用 `val` 替换原子对象的旧值。
2. 不相等，则用原子对象的旧值替换 `expected` ，因此调用该函数之后，如果被该原子对象封装的值与参数 `expected` 所指定的值不相等，`expected` 中的内容就是原子对象的旧值。

该函数通常会读取原子对象封装的值，如果比较为 `true`(即原子对象的值等于 `expected`)，则替换原子对象的旧值，但整个操作是原子的，在某个线程读取和修改该原子对象时，另外的线程不能对读取和修改该原子对象。

在第(2)种情况下，内存序（Memory Order）的选择取决于比较操作结果，如果比较结果为 `true`(即原子对象的值等于 `expected`)，则选择参数 `success` 指定的内存序，否则选择参数 `failure` 所指定的内存序。

注意，该函数直接比较原子对象所封装的值与参数 `expected` 的物理内容，所以某些情况下，对象的比较操作在使用 `operator==()` 判断时相等，但 `compare_exchange_weak` 判断时却可能失败，因为对象底层的物理内容中可能存在位对齐或其他逻辑表示相同但是物理表示不同的值(比如 `true` 和 2 或 3，它们在逻辑上都表示"真"，但在物理上两者的表示并不相同)。

`与compare_exchange_strong` 不同, `weak` 版本的 `compare-and-exchange` 操作允许(*`spuriously`* 地)返回 `false` (即原子对象所封装的值与参数 `expected` 的物理内容相同，但却仍然返回 `false`)，不过在某些需要循环操作的算法下这是可以接受的，并且在一些平台下 `compare_exchange_weak` 的性能更好 。如果 `compare_exchange_weak` 的判断确实发生了伪失败(spurious failures)——即使原子对象所封装的值与参数 `expected` 的物理内容相同，但判断操作的结果却为 `false`，`compare_exchange_weak` 函数返回 `false`，并且参数 `expected` 的值不会改变。

对于某些不需要采用循环操作的算法而言, 通常采用 `compare_exchange_strong` 更好。另外，该函数的内存序由 `sync` 参数指定，可选条件如下：

<table class="boxed">
<tr><th style="text-align: center;">Memory Order 值</th><th style="text-align: center;">Memory Order 类型</th></tr>
<tr>
<td style="text-align: center;"><samp>memory_order_relaxed</samp></td>
<td style="text-align: center;">Relaxed</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_consume</samp></td>
<td style="text-align: center;">Consume</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_acquire</samp></td>
<td style="text-align: center;">Acquire</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_release</samp></td>
<td style="text-align: center;">Release</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_acq_rel</samp></td>
<td style="text-align: center;">Acquire/Release</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_seq_cst</samp></td>
<td style="text-align: center;">Sequentially consistent</td>
</tr>
</table>

请看下面的例子（参考）：

    #include <iostream>       // std::cout
    #include <atomic>         // std::atomic
    #include <thread>         // std::thread
    #include <vector>         // std::vector
 
    // a simple global linked list:
    struct Node { int value; Node* next; };
    std::atomic<Node*> list_head(nullptr);
     
    void append(int val)
    {
        // append an element to the list
        Node* newNode = new Node{val, list_head};
     
        // next is the same as: list_head = newNode, but in a thread-safe way:
        while (!list_head.compare_exchange_weak(newNode->next,newNode)) {}
        // (with newNode->next updated accordingly if some other thread just appended another node)
    }
     
    int main ()
    {
        // spawn 10 threads to fill the linked list:
        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i) threads.push_back(std::thread(append, i));
        for (auto& th : threads) th.join();
     
        // print contents:
        for (Node* it = list_head; it!=nullptr; it=it->next)
            std::cout << ' ' << it->value;
     
        std::cout << '\n';
     
        // cleanup:
        Node* it; while (it=list_head) {list_head=it->next; delete it;}
     
        return 0;
    }

可能的执行结果如下：

    9 8 7 6 5 4 3 2 1 0

### `compare_exchange_strong` ###

<table>
<tr class="odd"><th>(1)</th>
<td>
<pre>bool compare_exchange_strong (T&amp; expected, T val,
           memory_order sync = memory_order_seq_cst) volatile noexcept;
bool compare_exchange_strong (T&amp; expected, T val,
           memory_order sync = memory_order_seq_cst) noexcept;
</pre>
</td>
</tr>
<tr class="even"><th>(2)</th>
<td>
<pre>bool compare_exchange_strong (T&amp; expected, T val,
           memory_order success, memory_order failure) volatile noexcept;
bool compare_exchange_strong (T&amp; expected, T val,
           memory_order success, memory_order failure) noexcept;</pre>
</td>
</tr>
</table>

比较并交换被封装的值(`strong`)与参数 `expected` 所指定的值是否相等，如果：

1. 相等，则用 `val` 替换原子对象的旧值。
2. 不相等，则用原子对象的旧值替换 `expected` ，因此调用该函数之后，如果被该原子对象封装的值与参数 `expected` 所指定的值不相等，expected 中的内容就是原子对象的旧值。

该函数通常会读取原子对象封装的值，如果比较为 `true`(即原子对象的值等于 `expected`)，则替换原子对象的旧值，但整个操作是原子的，在某个线程读取和修改该原子对象时，另外的线程不能对读取和修改该原子对象。

在第(2)种情况下，内存序（Memory Order）的选择取决于比较操作结果，如果比较结果为 true(即原子对象的值等于 expected)，则选择参数 `success` 指定的内存序，否则选择参数 `failure` 所指定的内存序。

注意，该函数直接比较原子对象所封装的值与参数 `expected` 的物理内容，所以某些情况下，对象的比较操作在使用 `operator==()` 判断时相等，但 `compare_exchange_weak` 判断时却可能失败，因为对象底层的物理内容中可能存在位对齐或其他逻辑表示相同但是物理表示不同的值(比如 `true` 和 2 或 3，它们在逻辑上都表示"真"，但在物理上两者的表示并不相同)。

与 `compare_exchange_weak` 不同, `strong` 版本的 `compare-and-exchange` 操作不允许(*`spuriously`* 地)返回 `false`，即原子对象所封装的值与参数 `expected` 的物理内容相同，比较操作一定会为 `true`。不过在某些平台下，如果算法本身需要循环操作来做检查， `compare_exchange_weak` 的性能会更好。

因此对于某些不需要采用循环操作的算法而言, 通常采用 `compare_exchange_strong` 更好。另外，该函数的内存序由 `sync` 参数指定，可选条件如下：

<table class="boxed">
<tr><th style="text-align: center;">Memory Order 值</th><th style="text-align: center;">Memory Order 类型</th></tr>
<tr>
<td style="text-align: center;"><samp>memory_order_relaxed</samp></td>
<td style="text-align: center;">Relaxed</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_consume</samp></td>
<td style="text-align: center;">Consume</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_acquire</samp></td>
<td style="text-align: center;">Acquire</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_release</samp></td>
<td style="text-align: center;">Release</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_acq_rel</samp></td>
<td style="text-align: center;">Acquire/Release</td>
</tr>
<tr>
<td style="text-align: center;"><samp>memory_order_seq_cst</samp></td>
<td style="text-align: center;">Sequentially consistent</td>
</tr>
</table>

请看下面的例子：

    #include <iostream>       // std::cout
    #include <atomic>         // std::atomic
    #include <thread>         // std::thread
    #include <vector>         // std::vector
     
    // a simple global linked list:
    struct Node { int value; Node* next; };
    std::atomic<Node*> list_head(nullptr);
     
    void append(int val)
    {
        // append an element to the list
        Node* newNode = new Node{val, list_head};
     
        // next is the same as: list_head = newNode, but in a thread-safe way:
     
        while (!(list_head.compare_exchange_strong(newNode->next, newNode)));
        // (with newNode->next updated accordingly if some other thread just appended another node)
    }
     
    int main ()
    {
        // spawn 10 threads to fill the linked list:
        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i) threads.push_back(std::thread(append, i));
        for (auto& th : threads) th.join();
     
        // print contents:
        for (Node* it = list_head; it!=nullptr; it=it->next)
            std::cout << ' ' << it->value;
     
        std::cout << '\n';
     
        // cleanup:
        Node* it; while (it=list_head) {list_head=it->next; delete it;}
     
        return 0;
    }

好了，本文花了大量的篇幅介绍 `std::atomic` 基本类型，下一篇博客我会给大家介绍 C++11 的标准库中 `std::atomic` 针对整形(integral)和指针类型的特化版本做了哪些改进。





