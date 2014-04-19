#include <iostream>
#include <vector>

class Recipe
{
public:
    virtual int amountWater() = 0;
    virtual void brew() = 0;
};

class CoffeeRecipe : public Recipe
{
public:
    CoffeeRecipe(int amountWater)
        : Recipe()
        , amountWater_(amountWater)
    {
    }

    virtual int amountWater() override
    {
        return amountWater_;
    }
    
    virtual void brew() override
    {
        std::cout << "Dripping Coffee through filter.\n";
    }
private:
    int amountWater_;
};

class TeaRecipe : public Recipe
{
public:
    TeaRecipe(int amountWater)
        : Recipe()
        , amountWater_(amountWater)
    {}

    virtual int amountWater() override
    {
        return amountWater_;
    }

    virtual void brew() override
    {
        std::cout << "steeping Tea.\n";
    }
private:
    int amountWater_;
};

class CaffeineBeverage
{
public:
    CaffeineBeverage(Recipe &recipe)
        : recipe(recipe)
    {}

    void prepare()
    {
        boilWater(recipe.amountWater());
        recipe.brew();
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
    Recipe& recipe;
};

int main()
{
    CoffeeRecipe coffeRecipe(150);
    TeaRecipe teaRecipe(100);
    CaffeineBeverage coffee(coffeRecipe);
    CaffeineBeverage tea(teaRecipe);

    std::vector<CaffeineBeverage*> beverages;

    beverages.push_back(&coffee);
    beverages.push_back(&tea);

    for(auto it = beverages.begin(); it != beverages.end(); it++)
    {
        (*it)->prepare();
    }

    return 0;
}
