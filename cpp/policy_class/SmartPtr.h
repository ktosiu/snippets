#include <exception>

template <typename T> struct NoChecking
{
    static void Check(T*) {}
};

template <typename T> struct EnforceNotNull
{
    static void Check(T* ptr)
    {
        if(!ptr) throw std::exception();
    }
};

template < typename T,
         template <typename> class CheckingPolicy>
class SmartPtr : public CheckingPolicy<T>
{
public:
    explicit SmartPtr(T* p = 0) : pointee_(p) {}

    T* operator->()
    {
        CheckingPolicy<T>::Check(pointee_);
        return pointee_;
    }
private:
    T* pointee_;
};

struct Dummy
{
    void func()
    {
        return;
    }
};

typedef SmartPtr<Dummy, NoChecking> NonCheckingPtr;
typedef SmartPtr<Dummy, EnforceNotNull> CheckingPtr;
