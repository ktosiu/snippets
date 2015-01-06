#include <cstdlib>
#include <iterator>

namespace ds
{
    template<typename T, size_t N> struct array {
        typedef T value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef pointer iterator;
        typedef const_pointer const_iterator;

        iterator begin() { return data; }
        iterator end() { return data + N; }
        const_iterator begin() const { return data; }
        const_iterator end() const { return data + N; }

        reference operator[](size_type n) { return data[n]; }
        const_reference operator[](size_type n) const { return data[n]; }
        size_type size() const { return N; }

        T data[N];
    };
}
