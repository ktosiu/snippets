#include <utility>
#include <string>

using namespace std;

struct X {
    int i;
    string s;
};

struct HasX {
    X x;
};

int main() {
    X x1, x2 = std::move(x1);
    HasX hx1, hx2 = std::move(hx1);
}
