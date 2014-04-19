#include <iostream>
#include <functional>
#include <string>

template <typename R>
static R chain_of_resp(std::function<R()> call, std::function<R()> next)
{
    if(next) return call() + next();
    return call();
}

struct Condiment
{
    std::function<std::string()> description;
    std::function<float()> price;
};

struct Milk
{
    static std::string description() { return "-Milk-"; }
    static float price() {return 0.07f;}
};

struct Sugar
{
    static std::string description() {return "-Sugar-";}
    static float price() {return 0.13f;}
};

int main()
{
    Condiment condiment;
    condiment.description = std::bind(&chain_of_resp<std::string>, &Milk::description, condiment.description);
    condiment.description = std::bind(&chain_of_resp<std::string>, &Sugar::description, condiment.description);
    condiment.description = std::bind(&chain_of_resp<std::string>, &Sugar::description, condiment.description);

    condiment.price = std::bind(&chain_of_resp<float>, &Milk::price, condiment.price);
    condiment.price = std::bind(&chain_of_resp<float>, &Sugar::price, condiment.price);
    condiment.price = std::bind(&chain_of_resp<float>, &Sugar::price, condiment.price);

    std::cout << "Condiments: " << condiment.description() << std::endl;
    std::cout << "Price: " << condiment.price() << std::endl;
}

