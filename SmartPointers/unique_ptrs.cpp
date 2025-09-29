#include <iostream>
#include <memory>

class Resource
{
private:
    int value;
public:
    Resource(int v) : value(v) 
    {
        std::cout << "Resource " << value << " Created \n";
    }

    ~Resource()
    {
        std::cout << "Resource " << value << " Destroyed \n";
    }

    int getValue() const { return value; }

    void do_work()
    {
        std::cout << "Resource " << value << " is working \n";
    }
};


int main()
{
    std::unique_ptr<Resource> u1 = std::make_unique<Resource>(1);
    std::cout << "Value in unique ptr u1 is " << u1->getValue() << "\n";
    //std::unique_ptr<Resource> u2 = u1; Not possible to copy owndership and will result in compilation error
    std::unique_ptr<Resource> u2 = std::make_unique<Resource>(2);
    std::cout << "Value in unique ptr u2 is " << u2->getValue() << "\n";
    u2 = std::move(u1); //Now ownership is transfered from u1 to u2
    std::cout << "Value in unique ptr u2 after moving u1 to u2 is " << u2->getValue() << "\n";

    std::shared_ptr<Resource> s1 = std::make_shared<Resource>(3);
    std::cout << "Value in shared ptr s1 is " << s1->getValue() << "\n";
    std::shared_ptr<Resource> s2 = s1;
    std::cout << "Value in shared ptr s2 is " << s2->getValue() << "\n";
    std::shared_ptr<Resource> s3 = s2;
    std::cout << "Value in shared ptr s3 is " << s3->getValue() << "\n";
    std::cout << "Reference count for shared pointer is " << s1.use_count() << "\n";

    std::shared_ptr<Resource> s_owner = std::make_shared<Resource>(4);
    std::cout << "Value in shared ptr s_owner is " << s_owner->getValue() << "\n";
    std::weak_ptr<Resource> w_ref = s_owner;

    //Need tp use lock tp access data of s_owner via weak ptr(non owning reference)
    if(!w_ref.expired())
        std::cout << "Value in shared ptr s_owner obtained via weak ptr w_ref is " << (w_ref.lock())->getValue() << "\n";


    return 0;
}