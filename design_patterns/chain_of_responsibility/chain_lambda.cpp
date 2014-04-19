#include <iostream>
#include <functional>
#include <string>

template <typename Call, typename NextCall>
static auto chain_of_resp(Call call, NextCall next) -> decltype(call() + next())
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
    condiment.description = [=](){return chain_of_resp(&Milk::description, condiment.description); };
    condiment.description = [=](){return chain_of_resp(&Sugar::description, condiment.description);};
    condiment.description = [=](){return chain_of_resp(&Sugar::description, condiment.description);};

    condiment.price = [=](){return chain_of_resp(&Milk::price, condiment.price);};
    condiment.price = [=](){return chain_of_resp(&Sugar::price, condiment.price);}; 
    condiment.price = [=](){return chain_of_resp(&Sugar::price, condiment.price);};

    std::cout << "Condiments: " << condiment.description() << std::endl;
    std::cout << "Price: " << condiment.price() << std::endl;
}

