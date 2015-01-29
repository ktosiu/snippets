#include <set>
#include <iostream>

using std::set;

typedef unsigned long long IDType;

class id_generator {
public:
    id_generator() : m_watermark(0) {}
    IDType request() {
        if(released.empty()) {
            requested.insert(m_watermark);
            IDType id = m_watermark;
            ++m_watermark;
            return id;
        }
        else {
            IDType id = *released.begin();
            released.erase(released.begin());
            requested.insert(id);
            return id;
        }
    }

    void release(IDType id) {
        if(requested.count(id) > 0) {
            requested.erase(id);
            released.insert(id);
        }
        {
            //Error
        }
    }

    set<IDType> released;
    set<IDType> requested;
    IDType m_watermark;
};

int main() {

    //Tests
    id_generator id_gen;
    std::cout << id_gen.request() << "\n";
    std::cout << id_gen.request() << "\n";
    std::cout << id_gen.request() << "\n";
    std::cout << id_gen.request() << "\n";
    id_gen.release(0);
    std::cout << id_gen.request() << "\n";
    return 0;
}
