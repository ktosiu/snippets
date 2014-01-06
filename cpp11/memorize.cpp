#include <map>
#include <iostream>

template <int (*f)(int)>
int memorize(int x)
{
    static std::map<int, int> cache;
    auto it = cache.find(x);
    if(it != cache.end())
    {
        return it->second;
    }
    return cache[x] = f(x);
}

int fib(int n)
{
    if(n<2) return n;
    return memorize<fib>(n-1) + memorize<fib>(n-2);
}

int fact(int n)
{
    if(n == 1) return 1;
    return n * memorize<fact>(n-1);
}

int main()
{
    std::cout << fib(150) << std::endl;
    std::cout << fact(10) <<std::endl;
    return 0;
}
