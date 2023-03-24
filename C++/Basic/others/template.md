# Template
内容来自：https://github.com/wuye9036/CppTemplateTutorial

## 类模版
```cpp
template <typename T> class ClassA; // 申明
template <typename T> class ClassA  // 定义
{
    T member;
};

```
## 函数模版
以关键字template和模板参数列表作为声明与定义的开始。模板参数列表中的类型，可以出现在**参数、返回值以及函数体**中
```cpp
template <typename T> void foo(T const& v);

template <typename T> T foo();

template <typename T, typename U> U foo(T const&);

template <typename T> void foo()
{
    T var;
    // ...
}
```
## 模版特化与偏特化
特化（specialization）是根据一个或多个特殊的整数或类型，给出模板实例化时的一个指定内容。（部分特化/偏特化 和 特化 相当于是模板实例化过程中的if-then-else。这使得我们根据不同类型，选择不同实现的需求得以实现；）
```cpp
// 首先，要写出模板的一般形式（原型）
template <typename T> class AddFloatOrMulInt
{
    static T Do(T a, T b)
    {
        // 在这个例子里面一般形式里面是什么内容不重要，因为用不上
        // 这里就随便给个0吧。
        return T(0);
    }
};

// 其次，我们要指定T是int时候的代码，这就是特化：
template <> class AddFloatOrMulInt<int>
{
public:
    static int Do(int a, int b)
    {
        return a * b;
    }
};

// 再次，我们要指定T是float时候的代码：
template <> class AddFloatOrMulInt<float>
{
public:
    static float Do(float a, float b)
    {
        return a + b;
    }
};

void foo()
{
    // 这里面就不写了
}
```

## 不定长的模版参数
这里的typename... Ts相当于一个声明，是说Ts不是一个类型，而是一个不定常的类型列表。同C语言的不定长参数一样，它通常只能放在参数列表的最后。
```cpp
template <typename... Ts> class tuple;

template <typename... Ts, typename U> class X {};              // (1) error!
template <typename... Ts>             class Y {};              // (2)
template <typename... Ts, typename U> class Y<U, Ts...> {};    // (3)
template <typename... Ts, typename U> class Y<Ts..., U> {};    // (4) error!
```
