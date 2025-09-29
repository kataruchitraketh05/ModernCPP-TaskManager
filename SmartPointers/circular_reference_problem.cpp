#include <iostream>
#include <memory>

class Child; //Fordward Declaration
class SafeChild;

class Parent 
{
public:
    std::shared_ptr<Child> child_ptr;
    ~Parent() { std::cout << "  -> Parent DESTROYED\n"; }
};

class Child
{
public:
    std::shared_ptr<Parent> parent_ptr;
    ~Child() { std::cout << "  -> Child DESTROYED\n"; }
};

class SafeParent
{
public:
    std::shared_ptr<SafeChild> child_ptr;
    ~SafeParent() { std::cout << "  -> SafeParent DESTROYED\n"; }
};

class SafeChild
{
public:
    std::weak_ptr<SafeParent> parent_ptr;
    ~SafeChild() { std::cout << "  -> SafeChild DESTROYED\n"; }
};

void demonstrate_memory_leak()
{
    std::cout << "\n DEMONSTRATE MEMORY LEAK \n";
    {
        std::shared_ptr<Parent> p = std::make_shared<Parent>();
        std::shared_ptr<Child> c = std::make_shared<Child>();
        std::cout << "1: Parent pointer p use count is " << p.use_count() << "\n";
        std::cout << "1: Child pointer c use count is " << c.use_count() << "\n";
        p->child_ptr = c;
        c->parent_ptr = p;
        std::cout << "Exit point of the scope.\n";
        std::cout << "2: Parent pointer p use count is " << p.use_count() << "\n";
        std::cout << "2: Child pointer c use count is " << c.use_count() << "\n";
    }
    // p and c go out of scope here.
    // Output: Nothing is destroyed! The destructors are NOT called.
}

void demonstrate_no_memory_leak()
{
    std::cout << "\n DEMONSTRATE NO MEMORY LEAK \n";
    {
        std::shared_ptr<SafeParent> p = std::make_shared<SafeParent>();
        std::shared_ptr<SafeChild> c = std::make_shared<SafeChild>();
        std::cout << "1: Parent pointer p use count is " << p.use_count() << "\n";
        std::cout << "1: Child pointer c use count is " << c.use_count() << "\n";
        p->child_ptr = c;
        c->parent_ptr = p;
        std::cout << "Exit point of the scope.\n";
        std::cout << "2: Parent pointer p use count is " << p.use_count() << "\n";
        std::cout << "2: Child pointer c use count is " << c.use_count() << "\n";
    }
    // p's count drops from 1 to 0 -> Parent DESTROYED
    // Child's count drops from 2 to 1 (when c is destroyed)
    // Then p's destructor runs, destroying p->child_ptr, dropping Child's count 1 to 0 -> Child DESTROYED
}

int main()
{
    demonstrate_memory_leak();
    demonstrate_no_memory_leak();
    return 0;
}