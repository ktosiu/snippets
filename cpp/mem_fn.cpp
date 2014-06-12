#include <functional>
#include <iostream>

using namespace std;

struct wrapper
{
    void member_func_0_arg()
    {
        cout<< "0 argument" << endl;
    }

    void member_func_1_arg(int arg)
    {
        cout<< "1 argument: " << arg << endl;
    }

    int data;
};

int main()
{
    wrapper w;

    auto fn_0_arg = std::mem_fn(&wrapper::member_func_0_arg);
    auto fn_1_arg = std::mem_fn(&wrapper::member_func_1_arg);
    auto mem_data = std::mem_fn(&wrapper::data);

    fn_0_arg(w);
    fn_1_arg(w, 20);

    mem_data(w) = 100;
    cout<< mem_data(w) << endl;
}
