#include <memory>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Object
{
    virtual ~Object(){}
};

template<typename T>
struct Box : Object
{
    T value;
    Box(const T& _value):value(_value){}
};

struct Any
{
    shared_ptr<Object> box;

    template<typename T>
    Any(const T& value):box(make_shared<Box<T>>(value)) {}

    template<typename T>
    const T& Unbox()
    {
        return dynamic_pointer_cast<Box<T>>(box)->value;
    }
};

int main()
{
    vector<Any> fuck;
    fuck.push_back(string("fuck"));
    fuck.push_back(1);

    cout << fuck[0].Unbox<string>() << fuck[1].Unbox<int>() << endl;
    fuck[0].Unbox<float>(); // crash
}
