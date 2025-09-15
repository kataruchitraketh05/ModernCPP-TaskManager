#include <iostream>
#include <queue>
#include <memory>


class Task 
{
private:
    std::string name;
    int id;
public:
    Task(const std::string& n, int i) : name(n), id(i) 
    {
        std::cout << "Task " << id << " created\n"; 
    }

    ~Task()
    {
        std::cout << "Task " << id << " destroyed\n"; 
    }

    std::string getName() const { return name; }
    int getId() const { return id; } 
};

class TaskQueue
{
private:
    std::queue<std::unique_ptr<Task>> tasks;
public:
    void addTask(const std::string& name, int id) 
    {
        tasks.push(std::make_unique<Task>(name, id));
    }
    bool isEmpty() { return tasks.empty(); }
    //auto  isEmpty() { return tasks.empty(); } C++ 17

    std::unique_ptr<Task> popFirstTaskInQueue()
    {
        if(isEmpty()) 
            return nullptr;

        auto taskToReturn = std::move(tasks.front());
        tasks.pop();
        return taskToReturn;
    }

    //C++ 17 version
    // auto popFirstTaskInQueue()
    // {
    //     std::unique_ptr<Task> taskToReturn = nullptr;
    //     if(!isEmpty()) 
    //     {
    //         taskToReturn = std::move(tasks.front());
    //         tasks.pop();
    //     }
    //     return taskToReturn;
    // }

};


int main()
{
    TaskQueue myQueue;
    myQueue.addTask("Write some code", 1);
    myQueue.addTask("Compile the code", 2);
    myQueue.addTask("Test the code", 3);

    std::cout << "Started processing tasks \n";
    while(!myQueue.isEmpty())
    {
        auto currentTask = myQueue.popFirstTaskInQueue();
        if(currentTask)
            std::cout << "Processing Task " << currentTask->getId() << " : " << currentTask->getName() << "\n";
    }

    std::cout << "All tasks processed \n";
    return 0;
}
