#include <atomic>
using std::atomic;

template <typename T>
class LockFreeQueue
{
private:
    struct node
    {
        T value;
        node* next;

        node(T val)
            : value(val), next(0)
        {
        }
    };

    node* first; // Producer only
    atomic<node*> divider;
    atomic<node*> last; //Shared
public:
    LockFreeQueue()
    {
        first = divider = last = new node(T());
    }

    ~LockFreeQueue()
    {
        while(first != last)
        {
            node *p = first;
            first = first->next;
            delete p;
        }
    }

    void Produce(const T& val)
    {
        last.load()->next = new node(val);
        last.store(last.load()->next);
        while(first != divider)
        {
            node* p = first;
            first = first->next;
            delete p;
        }
    }

    bool Consume(T &val)
    {
        if(divider != last)
        {
            val = divider.load()->next->value; // Consume this value
            divider.store(divider.load()->next); // Flag that this value has been used and move the divider
            return true;
        }
        return false;
    }
};
