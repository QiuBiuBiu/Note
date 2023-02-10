#include <iostream>
#include <memory>


class Adaptee
{
public:
    void fun1() { std::cout << " Adaptee fun1 called " << std::endl; };
    void fun2() {};
    void fun3() {};
};

class ITarget
{
public:
    virtual void f1() = 0;
    virtual void f2() = 0;
    virtual void f3() = 0;
    virtual ~ITarget() = default;
};

class Adaptor : public ITarget
{
public:
    Adaptor()
    {
        adaptee = std::make_shared<Adaptee>();
    };
    void f1() override
    {
        std::cout << " Adaptor f1 called " << std::endl;
        adaptee->fun1();
    };
    void f2() override
    {
        // 重新实现
    };
    void f3() override
    {
        // 数据处理
        adaptee->fun3();
    };
private:
    std::shared_ptr<Adaptee> adaptee;
};

/*
适配器模式的应用场景是“接口不兼容”:
    1. 封装有缺陷的接口设计(修改接口名字、修改接口实现（仅限于调用原接口的前后修改实现、类似AOP思想：原接口为切面，而修改实现为增强）、二次封装接口的参数类型（方法参数或返回值）)
    2. 统一多个类的接口设计(某个功能的实现依赖多个外部系统（或者说类）。通过适配器模式，将它们的接口适配为统一的接口定义，然后我们就可以使用多态的特性来复用代码逻辑。)
    3. 替换依赖的外部系统(当我们把项目中依赖的一个外部系统替换为另一个外部系统的时候，利用适配器模式，可以减少对代码的改动。)
    4. 兼容老版本接口(在做版本升级的时候，对于一些要废弃的接口，我们不直接将其删除，而是暂时保留，并且标注为 deprecated，并将内部实现逻辑委托为新的接口实现。)

代理、桥接、装饰器、适配器 4 种设计模式的区别:
    代理、桥接、装饰器、适配器，这 4 种模式是比较常用的结构型设计模式。它们的代码结构非常相似。笼统来说，它们都可以称为 Wrapper 模式，也就是通过 Wrapper 类二次封装原始类。
    尽管代码结构相似，但这 4 种设计模式的用意完全不同，也就是说要解决的问题、应用场景不同，这也是它们的主要区别。这里我就简单说一下它们之间的区别。

    代理模式：代理模式在不改变原始类接口的条件下，为原始类定义一个代理类，主要目的是控制访问，而非加强功能，这是它跟装饰器模式最大的不同。
    桥接模式：桥接模式的目的是将接口部分和实现部分分离，从而让它们可以较为容易、也相对独立地加以改变。
    装饰器模式：装饰者模式在不改变原始类接口的情况下，对原始类功能进行增强，并且支持多个装饰器的嵌套使用。
    适配器模式：适配器模式是一种事后的补救策略。适配器提供跟原始类不同的接口，而代理模式、装饰器模式提供的都是跟原始类相同的接口。
*/

int main()
{
    auto adaptor = std::make_shared<Adaptor>();
    adaptor->f1();
    return 0;
}
