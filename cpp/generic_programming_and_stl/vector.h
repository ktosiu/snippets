#include <iterator>

namespace ds {
    template<typename T> class vector {
    public:
        typedef T value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        typedef pointer iterator;
        typedef const_pointer const_iterator;

        vector()
            : start_(0)
        {

        }

        ~vector() {

        }

        iterator begin() {
            return start_;
        }

        iterator end() {
            return finish_;
        }

        const_iterator begin() const {
            return start_;
        }

        const_iterator end() const {
            return finish_;
        }

    private:
        pointer start_, finish_, end_of_storage_;
    };
}
