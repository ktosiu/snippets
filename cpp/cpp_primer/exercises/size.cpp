#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    using std::cout;
    using std::endl;
    using std::string;
    using std::vector;
    using std::map;

    cout << "size of string is: " << sizeof(string) << endl;
    cout << "size of vector<int> is: " << sizeof(vector<int>) << endl;
    cout << "size of map<int, int> is: " << sizeof(map<int, int>) << endl;
}
