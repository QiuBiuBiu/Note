#include <iostream>
#include <memory>

class B;
class A
{
public:
    ~A()
    {
        std::cout << "~A" << std::endl;
    }
public:
    std::shared_ptr<B> b;
};

class B
{
public:
    ~B()
    {
        std::cout << "~B" << std::endl;
    }
public:
    std::shared_ptr<A> a;
    // std::weak_ptr<A> a; // 解决办法
};


int main() {
    {
        auto aa = std::make_shared<A>();
        auto bb = std::make_shared<B>();
        
        aa->b = bb;
        bb->a = aa;
        
        std::cout << aa->b.use_count() << std::endl; // 2
        std::cout << bb->a.use_count() << std::endl; // 2
    }
    
    return 0;
}
/*
运行结果是 A, B 都不会被销毁(析构)。
这是因为 aa, bb 内部的 pointer 同时又引用了 aa, bb。这使得 aa, bb 的引用计数均变为了 2。
而离开作用域时，aa, bb 智能指针被析构，却只能造成这块区域的引用计数减一，这样就导致了 aa, bb 对象指向的内存区域引用计数不为零。
而外部已经没有办法找到这块区域了，也就造成了内存泄露。
*/