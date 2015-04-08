#include <iostream>
#include <memory>
using namespace std;

void int_deleter(const int* pInt) {
    delete pInt;
    cout << "delete int" << endl;
}

using MyUniquePtr = unique_ptr<int, decltype(int_deleter)*>;

MyUniquePtr return_up() {
    return MyUniquePtr(new int(10), int_deleter);
}

void func(MyUniquePtr up) {
    cout << "*up is " << *up << endl;
}

int main() {
    auto upInt = MyUniquePtr(new int(), int_deleter);
    auto up = return_up();
    func(std::move(up));
}
