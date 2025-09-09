#include <iostream>
#include <string>
#include <queue>
#include <memory>
#include <thread>
#include <functional> //for std::ref
#include <mutex>
#include <chrono>

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
    std::mutex mutex;
public:
    void addTask(const std::string& name, int id) 
    {
        std::lock_guard<std::mutex> lock(mutex);
        tasks.push(std::make_unique<Task>(name, id));
    }
    //Use auto instead of bool in C++ 17

    std::unique_ptr<Task> popFirstTaskInQueue()
    {
        std::lock_guard<std::mutex> lock(mutex);
        if(tasks.empty()) 
            return nullptr;

        auto taskToReturn = std::move(tasks.front());
        tasks.pop();
        return taskToReturn;
    }

    //C++ 17 version
    // auto popFirstTaskInQueue()
    // {
    //     //std::lock_guard<std::mutex> lock(mutex);
           //std::unique_ptr<Task> taskToReturn = nullptr;
    //     if(!isEmpty()) 
    //     {
    //         taskToReturn = std::move(tasks.front());
    //         tasks.pop();
    //     }
    //     return taskToReturn;
    // }

};

void processTasks(TaskQueue &taskQueue, const std::string& whoCalled)
{
    while(true)
    {
        auto currentTask = taskQueue.popFirstTaskInQueue();
        if(!currentTask)
            break;
        std::cout << "Processing Task " << currentTask->getId() << " : " << currentTask->getName() << " called by " << whoCalled << "\n";
         // Simulate doing some work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    TaskQueue myQueue;
    myQueue.addTask("Write some code", 1);
    myQueue.addTask("Compile the code", 2);
    myQueue.addTask("Test the code", 3);
    myQueue.addTask("Fix bugs, if any", 4);
    myQueue.addTask("Retest once more", 5);
    myQueue.addTask("Code cleanup", 6);
    myQueue.addTask("Push code to cloud", 7);
    myQueue.addTask("Raise a pull request", 8);
    myQueue.addTask("Address review comments, if any", 9);
    myQueue.addTask("Merge PR to main branch", 10);

    std::cout << "Started processing tasks \n";
    //Created a thread to process tasks Since processTasks 
    //needs queue as reference var pass myQueue as reference
    //variable using std::ref instead of by value 
    std::thread tasksProcessingThread(processTasks, std::ref(myQueue), "thread in main function");

    // The main thread also tries to process tasks at the same time.
    processTasks(myQueue, "directly by main function");

    // Wait for the worker thread to finish.
    tasksProcessingThread.join();

    std::cout << "All tasks processed \n";
    return 0;
}
