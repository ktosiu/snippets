#include <iostream>
#include <string>
#include <map>

class CaffeineBeverage
{
public:
    virtual ~CaffeineBeverage() {}
    virtual std::string description() = 0;
};

class Coffee : public CaffeineBeverage
{
public:
    virtual std::string description()
    {
        std::cout << "Coffee.\n";
    }
};

class Tea : public CaffeineBeverage
{
public:
    virtual std::string description()
    {
        std::cout << "Tea.\n";
    }
};

class CaffeineBeverageFactory
{
public:
    virtual CaffeineBeverage* create() = 0;
};

class CoffeeFactory : public CaffeineBeverageFactory
{
public:
    virtual CaffeineBeverage* create()
    {
        return new Coffee;
    }
};

class TeaFactory : public CaffeineBeverageFactory
{
public:
    virtual CaffeineBeverage* create()
    {
        return new Tea;
    }
};

class BeverageFactory
{
public:
    BeverageFactory()
    {
        factory["coffee"] = new CoffeeFactory;
        factory["tea"] = new TeaFactory;
    }

    ~BeverageFactory()
    {
        for(auto it = factory.begin(); it != factory.end(); it++)
            delete it->second;
    }

    CaffeineBeverage* create(const std::string& beverage)
    {
        return factory[beverage]->create();
    }
private:
    std::map<std::string, CaffeineBeverageFactory*> factory;
};

int main()
{
    BeverageFactory factory;
    CaffeineBeverage* b1 = factory.create("coffee");
    CaffeineBeverage* b2 = factory.create("tea");

    b1->description();
    b2->description();

    delete b1;
    delete b2;
}
