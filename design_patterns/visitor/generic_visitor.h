
class BaseVisitor
{
public:
    virtual ~BaseVisitor() {}
};

template <typename T, typename R = void>
class Visitor
{
public:
    typedef R ReturnType;
    virtual ReturnType Visit(T&) = 0;
};

template <typename R = void>
class BaseVisitable
{
public:
    typedef R ReturnType;
    virtual ~BaseVisitable() {}
    virtual ReturnType Accept(BaseVisitor&) = 0;
protected:
    template<typename T>
    static ReturnType AcceptImpl(T& visited, BaseVisitor& guest)
    {
        if(Visitor<T>* p = dynamic_cast<Visitor<T>*>(&guest))
        {
            return p->Visit(visited);
        }
        return ReturnType();
    }
};

#define DEFINE_VISITABLE() \
    virtual ReturnType Accept(BaseVisitor& guest) \
    { return AcceptImpl (*this, guest); }

