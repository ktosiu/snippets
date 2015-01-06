#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    vector<char> str_table;
    char c;
    while(cin.get(c)) {
        str_table.push_back(c);
    }

    typedef vector<char>::iterator str_table_iterator;
    typedef pair<str_table_iterator, str_table_iterator> line_type;
    vector<line_type> lines;

    auto it = str_table.begin();
    while(it != str_table.end()) {
        auto next = find(it, str_table.end(), '\n');
        if(next != str_table.end())
            ++next;

        lines.push_back(make_pair(it, next));
        it = next;
    }

    sort(lines.begin(), lines.end(),
         [](const line_type& x, const line_type& y){
             return lexicographical_compare(x.first, x.second, y.first, y.second);
         });

    for_each(lines.begin(), lines.end(),
             [](const line_type& s){
                 copy(s.first, s.second, ostream_iterator<char>(cout));
             });
    return 0;
}
