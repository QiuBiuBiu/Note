#include <iostream>
#include <memory>
#include <mutex>


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
            std::lock_guard<std::mutex> lk(mMutex);
            if (instance == nullptr) // 对于多进程并发的情况，一个进程已经创建完instance并释放锁了了，而另外一个进程此时获取了锁，故此时要判断instance是否为空，避免重复创建。
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
        static std::shared_ptr<Singleton> getInstance()
        {
            if (instance == nullptr) // 增加了一次判断，保证只有instance为空时才上锁（避免每次调用getInstance时都上锁，资源浪费）
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


namespace MagicStatic
{
    class Singleton
    {
    private:
        Singleton() { std::cout << "constructor for MagicStatic" << std::endl; }
    
    public:
        static Singleton& getInstance()
        {
            static Singleton instance; // “当变量在初始化的时候，并发同时进入声明语句，并发线程将会阻塞等待初始化结束。” 这样保证了并发线程在获取静态局部变量的时候一定是初始化过的，所以具有线程安全性。
            return instance;
        }
        ~Singleton() { std::cout << "destructor for MagicStatic" << std::endl; }
        Singleton(Singleton& ) = delete;
        Singleton& operator= (const Singleton& ) = delete;
    };
}


int main()
{
    std::cout << " main " << std::endl;
    // auto hunger_ins = HungryMode::Singleton::getInstance();
    // auto lazy_ins = LazyMode::Singleton::getInstance();
    auto ins1 = DoubleCheck::Singleton::getInstance();
    auto ins2 = DoubleCheck::Singleton::getInstance();

    // auto& magic_static_ins1 = MagicStatic::Singleton::getInstance(); // 注意在magic static模式下使用的时候需要声明单例的引用 Single& 才能获取对象。
    // auto& magic_static_ins2 = MagicStatic::Singleton::getInstance();
    
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
