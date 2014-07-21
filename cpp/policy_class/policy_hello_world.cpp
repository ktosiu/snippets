#include <iostream>
#include <string>

template <typename OutputPolicy,
          typename LanguagePolicy>
class HelloWorld : public OutputPolicy,
                   public LanguagePolicy
{
public:
    void run()
    {
        OutputPolicy::print(LanguagePolicy::message());
    }
};

template<typename T>
class OutputToCout
{
public:
    void print(const T& message)
    {
        std::cout << message << std::endl;
    }
};

template<typename T>
class LanguageEnglish
{
public:
    T message()
    {
        return "Hello, world";
    }
};

template<typename T>
class LanguageChinese
{
public:
   T message()
   {
       return "Hello, world (Chinese)";
   }
};

int main()
{
    using std::string;
    typedef HelloWorld<OutputToCout<string>, LanguageEnglish<string>> HelloWorldEnglish;
    HelloWorldEnglish hwe;
    hwe.run();

    typedef HelloWorld<OutputToCout<string>, LanguageChinese<string>> HelloWorldChinese;
    HelloWorldChinese hwc;
    hwc.run();
}

