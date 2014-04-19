#include <iostream>
#include <vector>
#include <functional>

class CaffeineBeverage
{
public:
    CaffeineBeverage(std::function<int()> amountWater, std::function<void()> brew)
        : amountWater(amountWater)
        , brew(brew)
    {}

    void prepare()
    {
        boilWater(amountWater());
        brew();
        pourInCup();
    }
private:
    void boilWater(int water)
    {
        std::cout << "boil water: " << water << std::endl;
    }

    void pourInCup()
    {
        std::cout << "Pour in cup \n";
    }
    std::function<int()> amountWater;
    std::function<void()> brew;
};

class Recipe
{
public:
    int amountWater(int amount)
    {
        return amount;
    }

    void brewCoffee()
    {
        std::cout << "Brew coffee.\n";
    }

    void brewTea()
    {
        std::cout << "Brew tea.\n";
    }
};

int main()
{
    Recipe recipe;
    CaffeineBeverage coffee(std::bind(&Recipe::amountWater, &recipe, 150), std::bind(&Recipe::brewCoffee, &recipe));
    CaffeineBeverage tea(std::bind(&Recipe::amountWater, &recipe, 100), std::bind(&Recipe::brewTea, &recipe));

    std::vector<CaffeineBeverage*> beverages;

    beverages.push_back(&coffee);
    beverages.push_back(&tea);

    for(auto it = beverages.begin(); it != beverages.end(); it++)
    {
        (*it)->prepare();
    }

    return 0;
}
