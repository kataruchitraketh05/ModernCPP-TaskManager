#include <iostream>
#include <vector>
#include <memory>

class Task 
{
    std::string name;
    int order;
public:
    Task(const std::string& n, int o) : name(n), order(o) {}
    std::string getName() const { return name; }
    int getOrder() const { return order; }
};

class TaskManager 
{
    std::vector<std::unique_ptr<Task>> tasks;

public:
    void addTask(const std::string& n, int o) 
    {
        tasks.push_back(std::make_unique<Task>(n, o));
    }

    std::size_t getTasksCount() const { return tasks.size(); }

    void printTasks() const 
    {
        for(const auto& t: tasks) 
            std::cout << "STEP " << t->getOrder() << " : " << t->getName() << "\n";
    }
};

int main() {
    TaskManager tm;
    tm.addTask("Write Code", 1);
    tm.addTask("Review the code for any improvements", 2);
    tm.addTask("Compile Code", 3);
    tm.addTask("Fix compilation errors if any", 4);
    tm.addTask("Test the code after successful compilation", 5);
    tm.addTask("Push the code and raise PR", 6);
    tm.addTask("Address review comments if any", 7);
    tm.addTask("Merge the PR to main branch", 9);
    std::cout << "\nTasks are \n";
    tm.printTasks();
    std::cout << "Total tasks: " << tm.getTasksCount() << "\n";

    return 0;
}
