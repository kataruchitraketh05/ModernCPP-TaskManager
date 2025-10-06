#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>

struct Person
{
    std::string name;
    int age;

    Person(const std::string& n, int a)
        : name(n),  // initialize member `name` with argument `n`
          age(a)   // initialize member `age` with argument `a`
        {
            // constructor body (can be empty or contain more code) 
        }
};

//This function can be used for non lambda version
bool compareByAge(const Person& a, const Person& b)
{
    return a.age < b.age;
}

int main()
{
    std::vector<Person> people {
        {"Arjun", 20},
        {"Bhuvan", 15},
        {"Charan", 25},
	    {"Dheeraj", 23},
    };
    std::cout << "People list (C++20 base version):\n";
    //Iterator variable is std::vector<Person>::iterator it;
    for(const auto& p : people)
        std::cout << p.name << " Age is " << p.age << "\n";
    
    std::ranges::sort(people, std::less<>{}, &Person::age);
    // Prior to C++ 11 Non lamda version std::sort(people.begin(), people.end(), compareByAge);

    std::cout << "\nSorted by age:\n";
    //use auto or class name
    //std::ranges::for_each(people, [](const Person& p) { std::cout << p.name << "age is "<< p.age ;});
    std::ranges::for_each(people, [](const auto& p) { std::cout << p.name << "age is "<< p.age << "\n";});
    return 0;
}
