#include <iostream>
#include <string>
#include <iterator>

using namespace std;

class line_iterator {
 private:
    istream* in;
    string line;
    bool is_valid;

    void read() {
        if(*in) {
            getline(*in, line);
        }
        is_valid = (*in)? true : false;
    }

 public:
    typedef input_iterator_tag iterator_category;
    typedef string value_type;
    typedef ptrdiff_t difference_type;
    typedef const string* pointer;
    typedef const string& reference;

    line_iterator(){
        in = &cin;
        is_valid = false;
    }

    line_iterator(istream& s) {
        in = &s;
        read();
    }

    reference operator*() const { return line; }
    pointer operator->() const { return &line; }

    line_iterator operator++() {
        read();
        return *this;
    }

    line_iterator operator++(int) {
        line_iterator tmp = *this;
        read();
        return tmp;
    }

    bool operator==(const line_iterator& i) const {
        return (in == i.in && is_valid == i.is_valid) ||
        (is_valid == false && i.is_valid == false);
    }

    bool operator!=(const line_iterator& i) const {
        return !(*this == i);
    }
};
