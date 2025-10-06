#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
    std::cout << "People list (C++17 version):\n";
    //Iterator variable is std::vector<Person>::iterator it;
    //Use both iterator and range based loops
    for(auto it = people.begin(); it != people.end(); ++it)
        std::cout << it->name << " Age is " << it->age << "\n";
    
    std::sort(people.begin(), people.end(), 
        [](const Person& a, const Person& b) {  return a.age < b.age; });
    // Prior to C++ 11 Non lamda version std::sort(people.begin(), people.end(), compareByAge);

    std::cout << "\nSorted by age:\n";
    for(auto& [name, age] : people)
        std::cout << name << " Age is " << age << "\n";

    return 0;
}
