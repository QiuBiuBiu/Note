#include <iostream>
#include <memory>
#include <mutex>

/*
namespace HungryMode
{
    class Singleton
    {
    public:
        using SingletonPtr = std::shared_ptr<Singleton>;
    private:
        Singleton() { std::cout << "constructor for HungryMode" << std::endl; };
        static SingletonPtr instance;

    public:
        static SingletonPtr getInstance()
        {
            return instance;
        };
        Singleton(Singleton& ) = delete;
        Singleton& operator= (const Singleton& ) = delete;
        ~Singleton() { std::cout << "destructor for HungryMode" << std::endl; }
    };
    std::shared_ptr<Singleton> Singleton::instance = std::shared_ptr<Singleton>(new Singleton()); // 饿汉式会在一开始就创建对象

}
*/

namespace LazyMode
{
    class Singleton
    {
    public:
        using SingletonPtr = std::shared_ptr<Singleton>;
    private:
        Singleton(){ std::cout << "constructor for LazyMode" << std::endl; }
        static SingletonPtr instance;
        static std::mutex mMutex;

    public:
        static SingletonPtr getInstance()
        {
            std::lock_guard<std::mutex> lk(mMutex); // std::scoped_lock<std::mutex> lk(mMutex)
            if (instance == nullptr)
            {
                instance = std::shared_ptr<Singleton>(new Singleton());
            }
            return instance;
        };
        ~Singleton() { std::cout << "destructor for LazyMode" << std::endl; }
        Singleton(Singleton& ) = delete;
        Singleton& operator= (const Singleton& ) = delete;
    };
    std::shared_ptr<Singleton> Singleton::instance = nullptr;
    std::mutex Singleton::mMutex;
}

namespace DoubleCheck
{
    class Singleton
    {
    private:
        Singleton() { std::cout << "constructor for DoubleCheck" << std::endl; };
        static std::shared_ptr<Singleton> instance;
        static std::mutex mMutex;

    public:
        static std::shared_ptr<Singleton>& getInstance()
        {
            if (instance == nullptr)
            {
                std::lock_guard<std::mutex> lk(mMutex);
                if (instance == nullptr)
                {
                    instance = std::shared_ptr<Singleton>(new Singleton());
                }
            }
            return instance;
        }
        ~Singleton() { std::cout << "destructor for DoubleCheck" << std::endl; }
        Singleton(Singleton& ) = delete;
        Singleton& operator= (const Singleton& ) = delete;
    };
    std::shared_ptr<Singleton> Singleton::instance = nullptr;
    std::mutex Singleton::mMutex;
}


int main()
{
    // auto hunger_ins = HungryMode::Singleton::getInstance();
    // auto lazy_ins = LazyMode::Singleton::getInstance();
    auto ins1 = DoubleCheck::Singleton::getInstance();
    auto ins2 = DoubleCheck::Singleton::getInstance();
    
    return 0;
}

/*
概括起来，要实现一个单例，我们需要关注的点无外乎下面几个：
    1. 构造函数需要是 private 访问权限的，这样才能避免外部通过 new 创建实例；
    2. 考虑对象创建时的线程安全问题；
    3. 考虑是否支持延迟加载；
    4. 考虑 getInstance() 性能是否高（是否加锁）。

单例存在的问题：
    单例对 OOP 特性的支持不友好
    单例会隐藏类之间的依赖关系
    单例对代码的扩展性不友好
    单例对代码的可测试性不友好
    单例不支持有参数的构造函数
*/
