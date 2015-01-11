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
            : start(0)
            , finish(0)
            , end_of_storage(0)
        {
        }

        ~vector() {
            if(start) {
                for(auto p = start; p != finish; ++p) {
                    p->~T();
                }
                free(start);
            }
        }

        iterator begin() {
            return start;
        }

        iterator end() {
            return finish;
        }

        const_iterator begin() const {
            return start;
        }

        const_iterator end() const {
            return finish;
        }

        reference front() { return *begin(); }
        reference back() { return *(end() - 1); }

        void push_back(const T& x) {
            if(finish != end_of_storage) {
                new(finish)T();
                ++finish;
            }
            else {
                size_type capacity = size_type(end_of_storage - start);
                capacity = capacity ? capacity * 2 : 1;
                pointer new_start = malloc(capacity * sizeof(T));
                pinter new_finish = new_start;

            }
        }

        void pop_back() {

        }

        // erase the value of position
        iterator erase(iterator position) {

        }

        void resize(size_type new_size, const T& x) {

        }

        void resize(size_type new_size) {

        }

        void clear() {

        }

        bool empty() const {
            return start == finish;
        }

        size_type size() const { return size_type(end() - begin()); }
        size_type capacity() const { return size_type(end_of_storage - begin());}
        reference operator[](size_type n) {
            return *(begin() + n);
        }
    private:
        iterator start, finish, end_of_storage;
    };
}
