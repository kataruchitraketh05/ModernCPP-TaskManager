#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Person
{
    std::string name;
    int age;

    Person(const std::string& n, int a)
        : name(n),
          age(a)
          {
          }
};

bool compareByAge(const Person& a, const Person& b)
{
    return a.age < b.age;
}

int main()
{
    std::vector<Person> people;
    people.push_back(Person("Arjun", 20));
    people.push_back(Person("Bhuvan", 15));
    people.push_back(Person("Charan", 25));
	people.push_back(Person("Dheeraj", 23));
    std::vector<Person>::iterator it;
    std::cout << "People list (C++11 base version, non-lambda):\n";
    for(it = people.begin(); it != people.end(); ++it)
        std::cout << it->name << " Age is " << it->age << "\n";
    
    std::sort(people.begin(), people.end(), compareByAge);

    std::cout << "\nSorted by age:\n";
    for(it = people.begin(); it != people.end(); ++it)
        std::cout << it->name << " Age is " << it->age << "\n";

    return 0;
}