# new

## new、delete
1. new / new[]：完成两件事，先底层调用 malloc 分配了内存，然后调用构造函数（创建对象）。
2. delete/delete[]：也完成两件事，先调用析构函数（清理资源），然后底层调用 free 释放空间。
3. new 在申请内存时会自动计算所需字节数，而 malloc 则需我们自己输入申请内存空间的字节数。

new、delete 使用

申请内存，确认是否申请成功

```cpp
int main()
{
    T* t = new T();     // 先内存分配 ，再构造函数
    delete t;           // 先析构函数，再内存释放
    return 0;
}
```

## 说说new和malloc的区别，各自底层实现原理?
- new是C++中的一个运算符，而malloc是函数。
- new在调用的时候先分配内存，在调用构造函数，释放的时候调用析构函数；而malloc没有构造函数和析构函数。
- malloc需要给定申请内存的大小，返回的指针需要强转；new会调用构造函数，不用指定内存的大小，返回指针不用强转。
- new可以被重载；malloc不行
- new分配内存更直接和安全。
- new发生错误抛出异常，malloc返回null