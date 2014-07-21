#include <cstdlib>
#include <new>

template <typename T>
struct OpNewCreator
{
    static T* Create()
    {
        return new T();
    }
};

template <typename T>
struct MallocCreator
{
    static T* Create()
    {
        void* buf = std::malloc(sizeof(T));
        return new(buf) T;
    }
};

template <typename T>
struct PrototypeCreator
{
    PrototypeCreator(T* pObj = 0)
        : pPrototype_(pObj)
    {
    }

    T* Create()
    {
        return pPrototype_ ? pPrototype_->Clone() : 0;
    }

    T* GetPrototype() { return pPrototype_; }
    void SetPrototype(T* pObj) { pPrototype_ = pObj; }
    T* pPrototype_;
};

template<class CreationPolicy>
class ItemManager : public CreationPolicy
{

};

typedef ItemManager<OpNewCreator<int> > IntManager;
typedef ItemManager<MallocCreator<long> > LongManager;
