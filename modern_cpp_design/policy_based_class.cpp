#include <iostream>
#include <cstdlib>

template <typename T> struct OpNewCreator {
    static T* Create() {
        return new T;
    }

    static void Destroy(T* pt) {
        delete pt;
    }
};

template <typename T> struct MallocCreator {
    static T* Create() {
        void* buf = std::malloc(sizeof(T));
        return new(buf) T;
    }

    static void Destroy(T* pt) {
        pt->~T();
        free(pt);
    }
};

template <typename CreationPolicy>
class WidgetManager : public CreationPolicy {
};

class T {
public:
    T() {
        std::cout << "T constructor.\n";
    }

    ~T() {
        std::cout << "T destructor.\n";
    }
};

int main() {
    T* p = WidgetManager<OpNewCreator<T> >::Create();
    WidgetManager<OpNewCreator<T> >::Destroy(p);

    T* p1 = WidgetManager<MallocCreator<T> >::Create();
    WidgetManager<MallocCreator<T> >::Destroy(p1);
    return 0;
}
