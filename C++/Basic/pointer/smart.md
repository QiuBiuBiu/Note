# 智能指针 
RAII: 资源获取即初始化。对于一个对象而言，我们在初始化的时候调用**构造函数**申请空间，而在离开作用域时调用**析构函数**释放空间。

## shared_ptr
std::shared_ptr 是一种智能指针，它**引用计数**来记录有多少个 shared_ptr 共同指向一个对象，从而消除显式的调用 delete，当**引用计数变为零的时候就会将对象自动删除**。
1. std::make_shared 就能够用来消除显式的使用 new（消除代码的不对称），所以std::make_shared 会分配创建传入参数中的对象， 并返回这个对象类型的std::shared_ptr指针。
2. std::shared_ptr 可以通过 get() 方法来获取原始指针，通过 reset() 来减少一个引用计数， 并通过use_count()来查看一个对象的引用计数。

## weak_ptr
std::shared_ptr 就会发现依然存在着资源无法释放的问题，比如循环引用的问题：[循环引用](../../Implement/code/cpp/sharedPointer.cpp)
1. std::weak_ptr是一种弱引用，弱引用不会引起引用计数增加。
2. std::weak_ptr 没有 * 运算符和 -> 运算符，所以不能够对资源进行操作。
    - **它可以用于检查 std::shared_ptr 是否存在**：expired() 方法能在资源未被释放时，会返回 false，否则返回 true。
    - **它也可以用于获取指向原始对象的 std::shared_ptr 指针**：lock() 方法在原始对象未被释放时，返回一个指向原始对象的 std::shared_ptr 指针，进而访问原始对象的资源，否则返回nullptr。

## unique_ptr
1. std::unique_ptr 是一种独占的智能指针，它禁止其他智能指针与其共享同一个对象。make_unique 方法从 C++14 才引入。
2. 既然是独占，换句话说就是不可复制。但是，**我们可以利用 std::move 将其转移给其他的 unique_ptr**。



