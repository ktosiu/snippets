#include "array.h"
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;
using namespace ds;

int main () {
    ds::array<int, 10> a = { 2, 1, 3, 6, 15, 30, 7, 11, 9, 35};
    copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    sort(a.begin(), a.end());
    copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}
