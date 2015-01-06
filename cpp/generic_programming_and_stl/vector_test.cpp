#include "vector.h"
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {
    ds::vector<int> dv;
    copy(dv.begin(), dv.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}
