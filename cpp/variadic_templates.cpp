#include <iostream>
#include <string>

using namespace std;

//
// Simple template functions
//
template<typename T>
T adder(T v) {
    cout << __PRETTY_FUNCTION__ << "\n";
    return v;
}

template<typename T, typename... Args>
T adder(T first, Args... args) {
    cout << __PRETTY_FUNCTION__ << "\n";
    return first + adder(args...);
}

//
// pair comparer
//
template<typename T>
bool pair_comparer(T a) {
    return false;
}

template<typename T>
bool pair_comparer(T a, T b) {
    return a == b;
}

template<typename T, typename... Args>
bool pair_comparer(T a, T b, Args... args) {
    return a == b && pair_comparer(args...);
}

//
// Tuple
//
template<typename... Ts> struct my_tuple {};

template<typename T, typename... Ts>
struct my_tuple<T, Ts...> : my_tuple<Ts...> {
    //Constructor
    my_tuple(T t, Ts... ts) : my_tuple<Ts...>(ts...), tail(t) {
    }

    T tail;
};

template <typename T, typename... Ts>
struct elem_type_holder<0, my_tuple<T, Ts...>> {
    typedef T type;
};

template <size_t k, typename T, typename... Ts>
struct elem_type_holder<k, my_tuple<T, Ts...>> {
    typedef typename elem_type_holder<k - 1, my_tuple<Ts...>>::type type;
};

template <size_t k, class... Ts>
typename std::enable_if<
    k == 0,
    typename elem_type_holder<0, my_tuple<Ts...>>::type&>::type
                                   get(my_tuple<Ts...>& t) {
    return t.tail;
};

template <size_t k, class T, class... Ts>
typename std::enable_if<
    k != 0,
    typename elem_type_holder<k, my_tuple<T, Ts...>>::type&>::type
                                   get(my_tuple<T, Ts...>& t) {
    my_tuple<Ts...>& base = t;
    return get<k - 1>(base);
};


int main() {
    int sum = adder(1, 2, 3, 5, 6, 7);
    cout << sum << endl;

    string str = adder(string("11"), string("22"), string("33"));
    cout << str << endl;

    cout << pair_comparer(1, 1, 2, 2) << endl;
    cout << pair_comparer(1, 2) << endl;
    cout << pair_comparer(1, 1, 2) << endl;

    my_tuple<int, long, string> t(12, 1200, "string");
    cout << get<0>(t) << endl;
    cout << get<1>(t) << endl;
    cout << get<2>(t) << endl;
    return 0;
}
