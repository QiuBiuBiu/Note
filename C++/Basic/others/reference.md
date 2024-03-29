# 引用

## 左值和右值
通常情况下，判断某个表达式是左值还是右值，最常用的有以下 2 种方法：
1. 可位于赋值号（=）左侧的表达式就是左值；反之，只能位于赋值号右侧的表达式就是右值。
2. 有名称的、可以获取到存储地址的表达式即为左值；反之则是右值。

## 左值引用
C++98/03 标准中就有引用，使用 "&" 表示。但此种引用方式有一个缺陷，即正常情况下只能操作 C++ 中的左值，无法对右值添加引用。因此，C++98/03 标准中的引用又称为左值引用。
```c++
    int num = 10;
    int &b = num;       // 正确
    //int &c = 10;      // 错误
    const int &d = num; // 正确
    const int &e = 10;  // 正确，虽然 C++98/03 标准不支持为右值建立非常量左值引用，但允许使用常量左值引用操作右值
```

## 右值引用
C++11 标准新引入了另一种引用方式，称为右值引用，用 "&&" 表示。右值引用可以从字面意思上理解，指的是以引用传递（而非值传递）的方式使用 C++ 右值。
```c++
    int num = 10;
    //int && a = num;   // 错误，右值引用不能初始化为左值
    int && a = 10;      // 正确，用右值来初始化右值引用

    a = 100;            // 和常量左值引用不同的是，右值引用还可以对右值进行修改
    cout << a << endl;  // 100
```

1. 右值引用就是必须绑定到右值（一个临时对象、将要销毁的对象）的引用，一般表示对象的值。
2. 右值引用可实现转移语义（Move Sementics）和完美转发（Perfect Forwarding），它的主要目的有两个方面：
    - 消除两个对象交互时不必要的对象拷贝，节省运算存储资源，提高效率。
    - 能够更简洁明确地定义泛型函数。

### 移动构造和复制构造
```c++
class demo
{
public:
    demo() {}
    demo(const demo& d) : num(new int(*d.num)) {}       // 复制构造，接受一个const的左值引用，做深拷贝
    demo(demo&& d) : num(d.num) { d.num = nullptr; }    // 移动构造，接受一个右值引用，做浅拷贝

private:
    int* num;
};
```

### std::move()和std::forward()
std::move是一个非常有迷惑性的函数，不理解左右值概念的人们往往以为它能把一个变量里的内容移动到另一个变量，但事实上std::move移动不了什么，**唯一的功能是把左值强制转化为右值，让右值引用可以指向左值**。其实现等同于一个类型转换：static_cast<T&&>(lvalue)。 所以，单纯的std::move(xxx)不会有性能提升。


### 转移语义
```c++
    {
        std::list<std::string> tokens;
        // 省略初始化...
        std::list<std::string> t = tokens;         // 这里存在拷贝 
    }
    std::list<std::string> tokens;
    std::list<std::string> t = std::move(tokens);  // 这里没有拷贝，tokens变为一个空list
```
1. 如果不用std::move，拷贝的代价很大，性能较低。使用move几乎没有任何代价，只是转换了资源的所有权。他实际上将左值变成右值引用，然后应用移动语义，调用移动构造函数，就避免了拷贝，提高了程序性能。如果一个对象内部有较大的对内存或者动态数组时，很有必要写move语义的拷贝构造函数和赋值函数，避免无谓的深拷贝，以提高性能。事实上，C++11中所有的容器都实现了移动语义，方便我们做性能优化。
2. 这里也要注意对move语义的误解，**move实际上它并不能移动任何东西，它唯一的功能是将一个左值强制转换为一个右值引用**。如果是一些基本类型比如int和char[10]定长数组等类型，使用move的话仍然会发生拷贝（因为没有对应的移动构造函数）。所以，move对于含资源（堆内存或句柄）的对象来说更有意义。

### 完美转发（Perfect Forwarding）
```c++
    void processValue(int& a){ cout << "lvalue" << endl; }
    void processValue(int&& a){ cout << "rvalue" << endl; }
    template <typename T>
    void forwardValue(T&& val)
    {
        processValue(std::forward<T>(val)); // 照参数本来的类型进行转发。
    }
    void Testdelcl()
    {
        int i = 0;
        forwardValue(i);    // 传入左值 
        forwardValue(0);    // 传入右值 
    }
    // 输出：
    // lvaue 
    // rvalue
```
右值引用T&&是一个universal references，可以接受左值或者右值，正是这个特性让他适合作为一个参数的路由，然后再通过std::forward按照参数的实际类型去匹配对应的重载函数，最终实现完美转发。

