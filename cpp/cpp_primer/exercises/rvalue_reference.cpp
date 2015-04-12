#include <iostream>
#include <utility>

int main() {
    int lv = 40;
    int& lr = lv;
    //Error: int&& rr = lv;
    //Error: int& lr2 = 100;
    const int& clr2 = 100;
    int&& rr2 = 100;
    //Error: int&& rr3 = rr2;
    int&& rr3 = std::move(rr2);
}
