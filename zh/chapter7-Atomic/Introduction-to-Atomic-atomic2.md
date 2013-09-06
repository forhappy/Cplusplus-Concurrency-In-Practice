[C++11 并发指南七( `<atomic>` 类型详解二 std::atomic )](https://github.com/forhappy/A-Detailed-Cplusplus-Concurrency-Tutorial/blob/master/zh/chapter7-Atomic/Introduction-to-Atomic-atomic.md) 介绍了基本的原子类型 `std::atomic` 的用法，本节我会给大家介绍 C++11 标准库中的 `std::atomic` 针对整形(`integral`)和指针类型的特化版本做了哪些改进。

总地来说，C++11 标准库中的 `std::atomic` 针对整形(`integral`)和指针类型的特化版本新增了一些算术运算和逻辑运算操作。具体如下：

    integral fetch_add(integral, memory_order = memory_order_seq_cst) volatile;
    integral fetch_add(integral, memory_order = memory_order_seq_cst);
    integral fetch_sub(integral, memory_order = memory_order_seq_cst) volatile;
    integral fetch_sub(integral, memory_order = memory_order_seq_cst);
    integral fetch_and(integral, memory_order = memory_order_seq_cst) volatile;
    integra    l fetch_and(integral, memory_order = memory_order_seq_cst);
    integral fetch_or(integral, memory_order = memory_order_seq_cst) volatile;
    integral fetch_or(integral, memory_order = memory_order_seq_cst);
    integral fetch_xor(integral, memory_order = memory_order_seq_cst) volatile;
    integral fetch_xor(integral, memory_order = memory_order_seq_cst);
     
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

下面我们来简单介绍以上的 `std::atomic` 特化版本的成员函数。


### `fetch_add` ###

<table>
<tr class="odd"><th>if T is integral (1)</th>
<td>
<pre>T fetch_add (T val, memory_order sync = memory_order_seq_cst) volatile noexcept;
T fetch_add (T val, memory_order sync = memory_order_seq_cst) noexcept;
</pre>
</td>
</tr>
<tr class="even"><th>if T is pointer (2)</th>
<td>
<pre>T fetch_add (ptrdiff_t val, memory_order sync = memory_order_seq_cst) volatile noexcept;
T fetch_add (ptrdiff_t val, memory_order sync = memory_order_seq_cst) noexcept;
</pre>
</td>
</tr>
</table>

将原子对象的封装值加 `val`，并返回原子对象的旧值（适用于整形和指针类型的 `std::atomic` 特化版本），整个过程是原子的。`sync` 参数指定内存序：

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

另外，如果第二个参数不指定（取默认参数 `memory_order_seq_cst`），则 `fetch_add` 相当与 `std::atomic::operator+=`。

### `fetch_sub` ###

<table>
<tr class="odd"><th>if T is integral (1)</th>
<td>
<pre>T fetch_add (T val, memory_order sync = memory_order_seq_cst) volatile noexcept;
T fetch_add (T val, memory_order sync = memory_order_seq_cst) noexcept;
</pre>
</td>
</tr>
<tr class="even"><th>if T is pointer (2)</th>
<td>
<pre>T fetch_add (ptrdiff_t val, memory_order sync = memory_order_seq_cst) volatile noexcept;
T fetch_add (ptrdiff_t val, memory_order sync = memory_order_seq_cst) noexcept;
</pre>
</td>
</tr>
</table>

将原子对象的封装值减 `val`，并返回原子对象的旧值（适用于整形和指针类型的 `std::atomic` 特化版本），整个过程是原子的。`sync` 参数指定内存序：

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

另外，如果第二个参数不指定（取默认参数 `memory_order_seq_cst`），则 `fetch_sub` 相当与 `std::atomic::operator-=`。

### `fetch_and` ###

    T fetch_and (T val, memory_order sync = memory_order_seq_cst) volatile noexcept;
    T fetch_and (T val, memory_order sync = memory_order_seq_cst) noexcept;

将原子对象的封装值按位与 `val`，并返回原子对象的旧值（只适用于整型的 `std::atomic` 特化版本），整个过程是原子的。`sync` 参数指定内存序：

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

另外，如果第二个参数不指定（取默认参数 `memory_order_seq_cst`），则 `fetch_and` 相当与 `std::atomic::operator&=`。

### `fetch_or` ###

    T fetch_or (T val, memory_order sync = memory_order_seq_cst) volatile noexcept;
    T fetch_or (T val, memory_order sync = memory_order_seq_cst) noexcept;

将原子对象的封装值按位或 `val`，并返回原子对象的旧值（只适用于整型的 `std::atomic` 特化版本），整个过程是原子的。`sync` 参数指定内存序：

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

另外，如果第二个参数不指定（取默认参数 `memory_order_seq_cst`），则 `fetch_or` 相当与 `std::atomic::operator|=`。

### `fetch_xor` ###

    T fetch_xor (T val, memory_order sync = memory_order_seq_cst) volatile noexcept;
    T fetch_xor (T val, memory_order sync = memory_order_seq_cst) noexcept;

将原子对象的封装值按位异或 `val`，并返回原子对象的旧值（只适用于整型的 `std::atomic` 特化版本），整个过程是原子的。`sync` 参数指定内存序：

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
>
另外，如果第二个参数不指定（取默认参数 `memory_order_seq_cst`），则 `fetch_xor` 相当与 `std::atomic::operator^=`。

### `operator++` ###

<table>
<tr class="odd"><th>pre-increment (1)</th>
<td>
<pre>T operator++() volatile noexcept;
T operator++() noexcept;
</pre>
</td>
</tr>
<tr class="even"><th>post-increment (2)</th>
<td>
<pre>T operator++ (int) volatile noexcept;
T operator++ (int) noexcept;
</pre>
</td>
</tr>
</table>

自增运算符重载， 第一种形式 (1) 返回自增后的值（即前缀++），第二种形式(2) 返回自增前的值（即后缀++），适用于整形和指针类型的 `std::atomic` 特化版本。

### `operator--` ###

<table>
<tr class="odd"><th>pre-decrement (1)</th>
<td>
<pre>T operator--() volatile noexcept;
T operator--() noexcept;
</pre>
</td>
</tr>
<tr class="even"><th>post-decrement (2)</th>
<td>
<pre>T operator-- (int) volatile noexcept;
T operator-- (int) noexcept;
</pre>
</td>
</tr>
</table>

自减运算符重载， 第一种形式 (1) 返回自减后的值（即前缀--），第二种形式(2) 返回自减前的值（即后缀--），适用于整形和指针类型的 `std::atomic` 特化版本。

### `atomic::operator (comp. assign.)` ###

复合赋值运算符重载，主要包含以下形式：

<table>
<tr class="odd"><th>if T is integral (1)</th>
<td>
<pre>T operator+= (T val) volatile noexcept;
T operator+= (T val) noexcept;
T operator-= (T val) volatile noexcept;
T operator-= (T val) noexcept;
T operator&amp;= (T val) volatile noexcept;
T operator&amp;= (T val) noexcept;
T operator|= (T val) volatile noexcept;
T operator|= (T val) noexcept;
T operator^= (T val) volatile noexcept;
T operator^= (T val) noexcept;
</pre>
</td>
</tr>
<tr class="even"><th>if T is pointer (2)</th>
<td>
<pre>T operator+= (ptrdiff_t val) volatile noexcept;
T operator+= (ptrdiff_t val) noexcept;
T operator-= (ptrdiff_t val) volatile noexcept;
T operator-= (ptrdiff_t val) noexcept;
</pre>
</td>
</tr>
</table>

以上各个 operator 都会有对应的 `fetch_*` 操作，详细见下表：

<table class="boxed">
<tr><th style="text-align: center;" rowspan="2">操作符</th><th style="text-align: center;" colspan="2">成员函数</th><th style="text-align: center;" colspan="3">支持类型</th></tr>
<tr><th style="text-align: center;">复合赋值</th><th style="text-align: center;">等价于</th><th style="text-align: center;">整型</th><th style="text-align: center;">指针类型</th><th style="text-align: center;">其他类型</th></tr>
<tr>
<td style="text-align: center;"><code>+</code></td>
<td style="text-align: center;"><samp>atomic::operator+=</samp></td>
<td style="text-align: center;"><samp>atomic::fetch_add</samp></td>
<td style="text-align: center;">是</td>
<td style="text-align: center;">是</td>
<td style="text-align: center;">否</td>
</tr>
<tr>
<td style="text-align: center;"><code>-</code></td>
<td style="text-align: center;"><samp>atomic::operator-=</samp></td>
<td style="text-align: center;"><samp>atomic::fetch_sub</samp></td>
<td style="text-align: center;">是</td>
<td style="text-align: center;">是</td>
<td style="text-align: center;">否</td>
</tr>
<tr>
<td style="text-align: center;"><code>&amp;</code></td>
<td style="text-align: center;"><samp>atomic::operator&amp;=</samp></td>
<td style="text-align: center;"><samp>atomic::fetch_and</samp></td>
<td style="text-align: center;">是</td>
<td style="text-align: center;">否</td>
<td style="text-align: center;">否</td>
</tr>
<tr>
<td style="text-align: center;"><code>|</code></td>
<td style="text-align: center;"><samp>atomic::operator|=</samp></td>
<td style="text-align: center;"><samp>atomic::fetch_or</samp></td>
<td style="text-align: center;">是</td>
<td style="text-align: center;">否</td>
<td style="text-align: center;">否</td>
</tr>
<tr>
<td style="text-align: center;"><code>^</code></td>
<td style="text-align: center;"><samp>atomic::operator^=</samp></td>
<td style="text-align: center;"><samp>atomic::fetch_xor</samp></td>
<td style="text-align: center;">是</td>
<td style="text-align: center;">否</td>
<td style="text-align: center;">否</td>
</tr>
</table>

好了，本节先介绍这里，下一节我会介绍 C++11 中 C 风格的原子操作 API。