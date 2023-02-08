#include <iostream>
#include <memory>
#include <map>


namespace SimpleFactory
{
    class IConfigParser {};
    class JsonConfigParser : public IConfigParser {};
    class XmlConfigParser : public IConfigParser {};
    class YamlConfigParser : public IConfigParser {};
    class TxtConfigParser : public IConfigParser {};

    class ConfigFactory
    {
    public:
        static std::shared_ptr<IConfigParser> createConfigParser(std::string& fileExtension)
        {
            if (fileExtension == "Json") return std::make_shared<JsonConfigParser>();
            else if (fileExtension == "Xml") return std::make_shared<XmlConfigParser>();
            else if (fileExtension == "Yaml") return std::make_shared<YamlConfigParser>();
            else if (fileExtension == "Txt") return std::make_shared<TxtConfigParser>();

            return nullptr;
        } 
    };
}

namespace FactoryMethod
{
    class IConfigFactory
    {
    public:
        virtual std::shared_ptr<IConfigFactory> createConfigParser() = 0;
        virtual ~IConfigFactory() = default;
    };

    class JsonConfigFactory : public IConfigFactory
    {
    public:
        std::shared_ptr<IConfigFactory> createConfigParser() override
        {
            std::cout << "Json config Factory" << std::endl;
            return std::make_shared<JsonConfigFactory>();
        }
    };

    class XmlConfigFactory : public IConfigFactory
    {
    public:
        std::shared_ptr<IConfigFactory> createConfigParser() override
        {
            std::cout << "Xml config Factory" << std::endl;
            return std::make_shared<XmlConfigFactory>();
        }
    };

    class FactoryContext // 工厂的工厂
    {
    public:
        static std::shared_ptr<IConfigFactory> getFactory(std::string& fileExtension)
        {
            return mFactories.at(fileExtension);
        }

    private:
        static std::map<std::string, std::shared_ptr<IConfigFactory>> mFactories;
    };
    std::map<std::string, std::shared_ptr<IConfigFactory>> FactoryContext::mFactories = {
        {"Json", std::make_shared<JsonConfigFactory>()},
        {"Xml", std::make_shared<XmlConfigFactory>()}
    };
}
/*
1）针对当前应用场景case，简单工厂模式简单好用，比工厂方法模式更加合适：
    实际上，对于规则配置文件解析这个应用场景来说，工厂模式需要额外创建诸多 Factory 类，也会增加代码的复杂性，
    而且，每个 Factory 类只是做简单的 new 操作，功能非常单薄（只有一行代码），也没必要设计成独立的类

2）什么时候用工厂模式而不是简单工厂？
    1）之所以将某个代码块剥离出来，独立为函数或者类，原因是这个代码块的逻辑过于复杂，剥离之后能让代码更加清晰，更加可读、可维护。
    但是，如果代码块本身并不复杂，就几行代码而已，我们完全没必要将它拆分成单独的函数或者类。
    2）当对象的创建逻辑比较复杂，不只是简单的 new 一下就可以，而是要组合其他类对象，做各种初始化操作的时候，我们推荐使用工厂方法模式，
    将复杂的创建逻辑拆分到多个工厂类中，让每个工厂类都不至于过于复杂。
    3）在某些场景下，如果对象不可复用，那工厂类每次都要返回不同的对象。如果我们使用简单工厂模式来实现，就只能选择第一种包含 if 分支逻辑的实现方式。
    如果我们还想避免烦人的 if-else 分支逻辑，这个时候，我们就推荐使用工厂方法模式。
*/



namespace AbstractFactory
{
    class IRuleConfigParser {};
    class JsonRuleConfigParser : public IRuleConfigParser {};
    // class XmlRuleConfigParser : ...

    class ISystemConfigParser {};
    class JsonSystemConfigParser : public ISystemConfigParser {};
    // class XmlSystemConfigParser : ...

    class IConfigParserFactory
    {
    public:
        virtual std::shared_ptr<IRuleConfigParser> createRuleConfigParser() = 0;
        virtual std::shared_ptr<ISystemConfigParser> createSystemConfigParser() = 0;
        //此处可以扩展新的parser类型，比如IBizConfigParser

        virtual ~IConfigParserFactory() = default;
    };

    class JsonConfigParserFactory : IConfigParserFactory
    {
    public:
        std::shared_ptr<IRuleConfigParser> createRuleConfigParser() override
        {
            return std::make_shared<JsonRuleConfigParser>();
        };

        std::shared_ptr<ISystemConfigParser> createSystemConfigParser() override
        {
            return std::make_shared<JsonSystemConfigParser>();
        }
    };

    // class XmlConfigParserFactory : IConfigParserFactory
    // ...
}


/*
    如果类有两种分类方式，比如，我们既可以按照配置文件格式来分类，也可以按照解析的对象（Rule 规则配置还是 System 系统配置）来分类，
    那就会对应下面这 8 个 parser 类：

    针对规则配置的解析器：基于接口IRuleConfigParser
    JsonRuleConfigParser
    XmlRuleConfigParser
    YamlRuleConfigParser
    PropertiesRuleConfigParser

    针对系统配置的解析器：基于接口ISystemConfigParser
    JsonSystemConfigParser
    XmlSystemConfigParser
    YamlSystemConfigParser
    PropertiesSystemConfigParser
    
    针对这种特殊的场景，如果还是继续用工厂方法来实现的话。
    我们要针对每个 parser 都编写一个工厂类，也就是要编写 8 个工厂类。
    如果我们未来还需要增加针对业务配置的解析器（比如 IBizConfigParser），那就要再对应地增加 4 个工厂类。
    
    抽象工厂就是针对这种非常特殊的场景而诞生的。
    我们可以让一个工厂负责创建多个不同类型的对象（IRuleConfigParser、ISystemConfigParser 等），而不是只创建一种 parser 对象。
    这样就可以有效地减少工厂类的个数。
*/


int main()
{
    // std::string fileExtension = "Json";
    std::string fileExtension = "Xml";
    FactoryMethod::FactoryContext::getFactory(fileExtension)->createConfigParser();
    return 0;
}