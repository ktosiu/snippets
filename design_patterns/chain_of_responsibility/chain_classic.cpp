#include <iostream>
#include <string>
#include <memory>
class Condiment
{
public:
    Condiment(Condiment* next)
        : next(next)
    {}

    Condiment()
        : next(nullptr)
    {}

    std::string description()
    {
        if(next)
        {
            return this->onDescription() + next->description();
        }
        return onDescription();
    }

    float price()
    {
        if(next)
            return onPrice() + next->price();
        return onPrice();
    }

    virtual std::string onDescription() = 0;
    virtual float onPrice() = 0;
private:
   Condiment* next; 
};

class Sugar : public Condiment
{
public:
    Sugar(Condiment* next)
        : Condiment(next)
    {}
    Sugar() {}
    virtual std::string onDescription() { return "-Sugar-"; }
    virtual float onPrice() { return 0.07f; }
};

class Milk : public Condiment
{
public:
    Milk(Condiment* next)
        : Condiment(next)
    {}
    Milk() {}

    virtual std::string onDescription() { return "-Milk-"; }
    virtual float onPrice() { return 0.13f; }
};

int main()
{
    std::unique_ptr<Milk> milk(new Milk());
    std::unique_ptr<Sugar> sugar_milk(new Sugar(milk.get()));
    std::unique_ptr<Sugar> sugar_sugar_milk(new Sugar(sugar_milk.get()));

    std::cout << "Condiment: " << sugar_sugar_milk->description() << std::endl;
    std::cout << "Price: " << sugar_sugar_milk->price() << std::endl;
}
