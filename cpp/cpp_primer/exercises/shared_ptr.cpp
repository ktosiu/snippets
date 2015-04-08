#include <iostream>
#include <memory>
using namespace std;

void func(shared_ptr<int> spInt) {
    cout << "spInt ref count: " << spInt.use_count() << endl;
}

void int_deleter(const int* pInt) {
    delete pInt;
    cout << "delete int pointer" << endl;
}

int main() {
    //shared_ptr<int> sp = make_shared<int>(0);
    //auto sp = shared_ptr<int>(new int(), int_deleter);
    auto sp = shared_ptr<int>(new int(),
                              [](const int* pInt){
                                  delete pInt;
                                  cout << "delete int pointer" << endl;
                              });

    cout << "sp initial ref count is: " << sp.use_count() << endl;
    func(sp);
    cout << "sp initial ref count is: " << sp.use_count() << endl;
}
