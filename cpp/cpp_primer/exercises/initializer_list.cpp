#include <iostream>
#include <initializer_list>

int main() {
    std::initializer_list<int> lst = {1, 2, 3, 4};
    for(const auto& e : lst) {
        std::cout << e << std::endl;
    }
    return 0;
}
