#include <iostream>
#include <string>
#include <utility> // Required for std::forward

template <typename T>
class Pair
{
private:
    T first;
    T second;
public:
    // Best Practice: Accept by const reference to handle Lvalues and Rvalues safely, 
    // and then copy/move into the member variables.
    Pair(const T& f, const T& s) : first(f), second(s) {}

    T getFirst() const { return first; }
    T getSecond() const { return second; }
};

template <typename T>
class StdForwardPair
{
private:
    T first;
    T second;
public:
    // Step 1: Use new template parameters U1, U2 to create Universal References
    // Step 2:Use std::forward to preserve the Lvalue/Rvalue nature
    // This ensures a MOVE occurs if the argument was a temporary (Rvalue).
    template<typename U1, typename U2>
    StdForwardPair(U1&& f, U2&& s) : first(std::forward<U1>(f)), second(std::forward<U2>(s)) {}

    T getFirst() const { return first; }
    T getSecond() const { return second; }
};
int main()
{
    int a = 20;
    int b = 40;
    std::string str_a = "world";
    std::string str_b = "using std forward";
    Pair<int> integer_pair(10, a);
    Pair<std::string> string_pair("hello", str_a);

    StdForwardPair<int> new_integer_pair(30, b);
    StdForwardPair<std::string> new_string_pair("new class", str_b);

    std::cout << "Members of integer pair created are " << integer_pair.getFirst() << "->" << integer_pair.getSecond() << std::endl;
    std::cout << "Members of string pair created are " << string_pair.getFirst() << "->" << string_pair.getSecond() << std::endl;

    std::cout << "Members of new integer pair created are " << new_integer_pair.getFirst() << "->" << new_integer_pair.getSecond() << std::endl;
    std::cout << "Members of new string pair created are " << new_string_pair.getFirst() << "->" << new_string_pair.getSecond() << std::endl;
    return 0;
}