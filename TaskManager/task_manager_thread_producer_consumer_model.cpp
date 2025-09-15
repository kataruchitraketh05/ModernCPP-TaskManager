#include <iostream>
#include <string>
#include <queue>
#include <memory>
#include <thread>
#include <functional> //for std::ref
#include <mutex>
#include <chrono>
#include <condition_variable> // New header for condition variables

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
    std::condition_variable cv;
    bool stop{false};
public:
    void addTask(const std::string& name, int id)
    {
        std::lock_guard<std::mutex> lock(mutex); //A simple light weight lock is enough here
        if(stop) return; //do not add tasks after shutdown
        tasks.push(std::make_unique<Task>(name, id));
        cv.notify_one();
    }

    std::unique_ptr<Task> popFirstTaskInQueue()
    {
        std::unique_lock<std::mutex> lock(mutex);
        //handle spurious wakeups
        cv.wait(lock, [this] { return (stop || !tasks.empty()); }); //Captures only class instance
        //Without predicate it actually means wait until neg of predicate is true
        // while(!stop && tasks.empty())
        //     cv.wait(lock);

        if(!tasks.empty())
        {
            auto taskToReturn = std::move(tasks.front());
            tasks.pop();
            return taskToReturn;
        }

        return nullptr;
    }

    void shutdown()
    {
        {
            std::lock_guard<std::mutex> lock(mutex);
            stop = true;
        }
        //Notify after mutex is unlocked and stop is true
        cv.notify_all();
    }

};

void processTasks(TaskQueue& taskQueue)
{
    while(true)
    {
        auto processTask = taskQueue.popFirstTaskInQueue();
        if(!processTask) break;
        std::cout << "Processing task " << processTask->getId() << " : " << processTask->getName() << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate work
    }
}

int main()
{
    TaskQueue myQueue;
    std::thread worker(processTasks, std::ref(myQueue));
    myQueue.addTask("Write some code", 1);
    myQueue.addTask("Compile the code", 2);
    myQueue.addTask("Test the code", 3);
    myQueue.addTask("Fix bugs, if any", 4);
    myQueue.addTask("Retest once more", 5);

    //simulate main thread doing some work then later add tasks
    std::this_thread::sleep_for(std::chrono::milliseconds(150)); 
    myQueue.addTask("Code cleanup", 6);
    myQueue.addTask("Push code to cloud", 7);
    myQueue.addTask("Raise a pull request", 8);
    myQueue.addTask("Address review comments, if any", 9);
    myQueue.addTask("Merge PR to main branch", 10);

    myQueue.shutdown();

    // Wait for the worker thread to finish.
    worker.join();

    std::cout << "All tasks processed \n";
    return 0;
}
