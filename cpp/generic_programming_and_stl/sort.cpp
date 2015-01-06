#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include "line_iterator.h"

using namespace std;

int main() {
    line_iterator iter(cin);
    line_iterator end_of_file;
    vector<string> v(iter, end_of_file);
    sort(v.begin(), v.end());
    copy(v.begin(), v.end(), ostream_iterator<string>(cout, "\n"));
    return 0;
}
