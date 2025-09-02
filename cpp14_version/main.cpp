#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Person
{
    std::string name;
    int age;

    Person(const std::string& n, int a)
        : name(n),   // initialize member `name` with argument `n`
            age(a)     // initialize member `age` with argument `a`
        {
            // constructor body (can be empty or contain more code)
        }
};

int main()
{
    std::vector<Person> people;
    people.emplace_back("Arjun", 20);
    people.emplace_back("Bhuvan", 15);
    people.emplace_back("Charan", 25);
	people.emplace_back("Dheeraj", 23);
    std::cout << "People list (C++14 version, emplace_back + lambda):\n";
    for(const auto& p : people)
        std::cout << p.name << " Age is " << p.age << "\n";
    
    std::sort(people.begin(), people.end(), 
        [](const Person& a, const Person& b) { return a.age < b.age; });

    std::cout << "\nSorted by age:\n";
    for(const auto& p : people)
        std::cout << p.name << " Age is " << p.age << "\n";

    return 0;
}