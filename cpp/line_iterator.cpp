#include <iterator>
#include <string>
#include <iostream>
#include <istream>
#include <vector>
#include <algorithm>
using namespace std;

class line_iterator : std::iterator<std::input_iterator_tag, string>
{
private:
    istream* in;
    string line;
    bool valid;

    void read()
    {
        if(*in)
        {
            getline(*in, line);
        }
        valid = (*in) ? true : false;
    }
public:
    line_iterator() : in(&cin), valid(false) {}
    line_iterator(istream& s) : in(&s) { read(); }
    const string& operator*() const { return line; }
    const string* operator->() const {return &line;}
    line_iterator operator++()
    {
        read();
        return *this;
    }
    line_iterator operator++(int)
    {
        line_iterator temp = *this;
        read();
        return temp;
    }

    bool operator==(const line_iterator& i) const
    {
        return (in == i.in && valid == i.valid) ||
            (valid == false && i.valid == false);
    }

    bool operator!=(const line_iterator& i) const
    {
        return !(*this == i);
    }
};

int main()
{
    line_iterator iter(cin);
    line_iterator eof;
    vector<string> v(iter, eof);
    sort(v.begin(), v.end());
    copy(v.begin(), v.end(), ostream_iterator<string>(cout, "\n"));
}
