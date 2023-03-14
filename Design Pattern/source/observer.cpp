#include <iostream>
#include <list>
#include <memory>


class observer
{
public:
    virtual void onUpdate() = 0;
    virtual ~observer() = default;  // 虚析构函数

};
using ObserverPtr = std::shared_ptr<observer>;


class subject 
{
public:
    using ObserverPtr = std::shared_ptr<observer>;
    using ObserverWPtr = std::weak_ptr<observer>;
    bool registerObserver(ObserverPtr ob)
    {
        if (std::find_if(observerLists.begin(), observerLists.end(), [ob](ObserverWPtr& wob){
            if (auto observerPtr = wob.lock())
            {
                return ob == observerPtr;
            }
            else
            {
                return false;
            }
        }) == observerLists.end())
        {
            observerLists.push_back(ob); // 隐式地将shared_ptr转化为weak_ptr
            return true;
        }
        return false;
    };

    bool removeObserver(ObserverPtr ob)
    {
        auto iter = std::find_if(observerLists.begin(), observerLists.end(), [ob](ObserverWPtr& wob){
            if (auto observerPtr = wob.lock())
            {
                return ob == observerPtr;
            }
            else
            {
                return false;
            }
        });
        if (iter != observerLists.end())
        {
            observerLists.erase(iter);
            return true;            
        }
        return false;
    };

    void notify()
    {
        for (auto observer : observerLists)
        {
            if (auto observerPtr = observer.lock())
            {
                observerPtr->onUpdate();
            }
        }
    }

private:
    std::list<ObserverWPtr> observerLists;  // 被观察者以weak_pointer的方式管理一组观察者

};

class concretObserver1 : public observer
{
public:
    void onUpdate() override
    {
        std::cout << "concretObserver1 receive notification, do something" << std::endl;
    };
};

class concreteObserver2 : public observer
{
public:
    void onUpdate() override
    {
        std::cout << "concretObserver2 receive notification, do something" << std::endl;
    };
};

int main()
{
    std::cout << "hello world" << std::endl;
    
    auto sub = std::make_shared<subject>();
    auto ob1 = std::make_shared<concretObserver1>();
    auto ob2 = std::make_shared<concreteObserver2>();
    std::cout << "register observer 1" << std::endl;
    sub->registerObserver(ob1);
    sub->notify();

    std::cout << "register observer 2" << std::endl;
    sub->registerObserver(ob2);
    sub->notify();

    std::cout << "remove observer 2" << std::endl;
    sub->removeObserver(ob2);
    sub->notify();
    
    return 0;
}