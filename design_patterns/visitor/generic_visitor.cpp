#include "generic_visitor.h"
#include <iostream>

class VisitableObject : public BaseVisitable<>
{
public:
    DEFINE_VISITABLE()
};

class DerivedVisitableObject : public VisitableObject
{
public:
    DEFINE_VISITABLE()
};

class VisitorObject :
    public BaseVisitor,
    public Visitor<VisitableObject>,
    public Visitor<DerivedVisitableObject>
{
public:
    void Visit(VisitableObject&)
    {
        std::cout << "Visit(VisitableObject)" << std::endl;
    }

    void Visit(DerivedVisitableObject&)
    {
        std::cout << "Visit(DerivedVisitableObject)" << std::endl;
    }
};

int main()
{
    VisitorObject visitor;
    VisitableObject* p1 = new DerivedVisitableObject;
    VisitableObject* p2 = new VisitableObject;

    p1->Accept(visitor);
    p2->Accept(visitor);

    delete p1;
    delete p2;
}
