#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    allocator<string> string_alloc;
    auto p = string_alloc.allocate(10);
    string* q = p;
    for(int i = 0; i < 10; i++)
        string_alloc.construct(q++, "aaa");

    copy(p, q, ostream_iterator<string>(cout, " "));

    cout << endl;

    for(int i = 0; i < 10; i++)
        string_alloc.destroy(p);

    string_alloc.deallocate(p, 10);

    vector<string> v = {"aaa", "bbb", "ccc", "ddd", "eee"};

    auto ps = string_alloc.allocate(v.size());
    auto qs = uninitialized_copy(v.begin(), v.end(), ps);
    copy(ps, qs, ostream_iterator<string>(cout, " "));
    cout << endl;

    for(auto p = ps; p != qs; ++p)
        string_alloc.destroy(p);

    string_alloc.deallocate(ps, v.size());
}
