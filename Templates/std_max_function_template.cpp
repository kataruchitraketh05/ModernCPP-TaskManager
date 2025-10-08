#include <iostream>
#include <string>
#include <algorithm> //We are implementing our own version of std::max present in this header

//Universal reference can bind to both locator(l value) and read(r value)
//T& in the arumenst is only for l value
template <typename T>
T Max(const T&& a, const T&& b)
{
    return (a > b) ? a : b;
}

int main()
{
    std::cout << "Max function template implementation" << std::endl;
    std::cout << "Maximum of 10, 20 is: " << Max(10, 20) << std::endl;
    std::cout << "Maximum of 3.14, 2.71 is: " << Max(3.14, 2.71) << std::endl;
    //If we do not include std::string the data type is deduced as const char * and pointer
    //address would be used for comparison instead of the actual alphabetical content
    std::cout << "Maximum of \"apple\" and \"banana\" is: " << Max(std::string("apple"), std::string("banana")) << std::endl;
    std::cout << "Maximum of 'z' and 'a' is: " << Max('z', 'a') << "\n"; 
    return 0;
}