#include <iostream>

template <typename T, size_t N>
struct block
{
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef const value_type* const_pointer;
    typedef const value_type& const_reference;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    typedef pointer iterator;
    typedef const_pointer const_iterator;

    iterator begin() {return data;}
    iterator end() {return data + N;}
    const_iterator begin() const {return data;}
    const_iterator end() const {return data+N;}

    reference operator[](size_type i) { return data[i]; }
    const_reference operator[](size_type i) const { return data[i]; }
    size_type size() {return N;}

    T data[N];
};

int main()
{
    block<int, 10> b;
    std::cout << b.size() << std::endl;
    for(block<int, 10>::iterator i = b.begin(); i != b.end(); i++)
    {
        std::cout << *i << std::endl;
    }
}
