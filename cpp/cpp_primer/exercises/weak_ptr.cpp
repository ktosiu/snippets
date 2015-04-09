#include <memory>
#include <iostream>

using namespace std;

int main() {
    shared_ptr<int> sp = make_shared<int>(0);
    weak_ptr<int> wp;
    cout << "wp use_count: " << wp.use_count() << endl;
    wp = sp;
    cout << "wp use_count: " << wp.use_count() << endl;
    auto sp1 = wp.lock();
    cout << "wp use_count: " << wp.use_count() << endl;
}
