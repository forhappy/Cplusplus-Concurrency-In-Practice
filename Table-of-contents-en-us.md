
Concurrent C ++ Programming Guide
The book is divided into 11 chapters plan, arrangements are as follows:

The first chapter concurrent programming foundation

1.1 What is a concurrent programming

1.2 differences and connections of concurrency and parallelism

1.3 Why concurrent programming

1.4 concurrent programming scenarios and classic example

1.5 Discussion C ++ concurrent programming

1.6 Information exchange

The second chapter several common multithreading library introduction

2.1 Pthread Multithreaded Programming Guide

2.2 Windows Multithreaded Programming Guide

2.3 Several common multithreading library interface contrast

2.4 Information exchange

Chapter III threads explained

3.1 <thread>header file summary

3.2 std::threadDetailed

3.3 std::this_threadnamespace related auxiliary function introduction

3.4 std::threadComparison with Pthread thread

3.5 Information exchange

Chapter ## with a mutex lock ##

4.1 <mutex>header file summary

4.2 mutex Comments

4.3 Lock Type In Depth

4.4 Introduction Helper

4.5 std::mutexComparison with Pthread mutex

4.6 Information exchange

## Chapter ## thread synchronization and condition variable

5.1 <condition_variable>header file summary

5.2 condition variable Explanation

5.3 Helper introduction

5.4 use condition variables (std :: condition_variable) thread synchronization

5.5 std::condition_variableComparison with the condition variable Pthread

5.6 Information exchange

## Chapter VI Detailed asynchronous tasks ##

6.1 <future>header file summary

6.2 asynchronous task provider (Provider) Introduction

6.3 asynchronous task provider (Provider) Introduction (Continued)

6.4 asynchronous tasks Future Type In Depth

6.5 associated with the introduction of asynchronous task type

6.6 asynchronous tasks Helper std::asyncintroduction

6.7 asynchronous and multi-threaded task instances

6.8 Information exchange

## ## Chapter VII atomic Type In Depth

7.1 <atomic>header file summary

7.2 std::atomic_flagDetailed

7.3 Basic std::atomicType In Depth

7.4 specialized std::atomictype Comments

7.5 C atomic style

On the memory model 7.6 C ++ 11

7.7 How to use the atom type design concurrent data structure

7.8 Information exchange

## Chapter VIII C ++ 11 memory model ##

8.1 C ++ memory model overview

8.2 X86 CPU processor architecture and a common memory consistency model profile

8.3 Sequence Memory (Memory Order) and synchronous operation

Examples of the type of programming 8.4 atomic

Lock-free programming 8.5 Discussion

Information exchange

## Chapter IX advanced thread management ##

## Chapter X how to write correct concurrent data structures ##

## Chapter XI concurrent programming application examples ##

11.1 using the C ++ 11 concurrency facilities to solve the producer-consumer problem

## Appendix C ++ 11 standard new overview ##

1. the runtime performance of the core language of strengthening

This section includes:

Rvalue references and move semantics
Generalized constant expressions constexpr
Amendments to the POD type definition.
2. When building the core performance enhanced language

This section includes:

External template.
3. Availability strengthen the core language

This section includes:

Initialization list ( std::initializer_list)
Unified initialized
Type inference (auto and decltype keywords)
Based on the range for loop
lambda expressions
An alternative function syntax
Optimization of object creation
Explicit virtual function overloading
Null pointer constant (nullptr a)
A strongly typed enumeration
Right angle bracket (>)
Explicit conversion operator
Template Alias
Unlimited union.
4. enhance the core language features

This section includes:

Vararg template
The new string literals
User-defined literals
Multithreading memory model
Thread Local Storage
Explicitly or disable some particular member function (constructor, a copy constructor, assignment operator, destructor, etc.)
long long int类型
Static assertions assertions
Allow sizeof operator acting on the data member type, without explicit object
Garbage collection
Attributes
5. C ++ Standard Library changes

This section includes:

Upgrading the standard library components
Multi-threading support
Tuple (tuple) Type
Hash table (hash table)
Regular Expressions
General smart pointer
Scalable random number function
Packing quote
Polymorphic function object wrappers
Type attribute for meta-programming
A method for calculating a unified type of function object returns
