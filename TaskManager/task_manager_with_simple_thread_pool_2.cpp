#include <iostream>
#include <condition_variable>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <chrono>
#include <memory>
#include <vector>
#include <sstream>

std::mutex cout_mutex; //Global mutex for non overlapping prints

void safe_print(const std::string& msg)
{
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << msg << std::endl;
}

class Task
{
private:
    std::string name;
    int id;
    std::stringstream s;
public:
    Task(const std::string& n, int i) : name(n), id(i)
    {
        s.str("");
        s.clear();
        s << "Task " << id << " created";
        safe_print(s.str());
    }

    std::string getName() const { return name; }
    int getId() const { return id; }

    ~Task()
    {
        s.str("");
        s.clear();
        s << "Task " << id << " destroyed";
        safe_print(s.str());
    }
};

class TaskQueue
{
private:
    std::queue<std::unique_ptr<Task>> tasks;
    std::mutex queue_mutex;
    std::condition_variable cv;
    bool stop{false};
public:
   void addTask(const std::string& name, int id)
    {
       std::lock_guard<std::mutex> lock(queue_mutex);
       if(stop) return; //Do not add tasks after shutdown
       tasks.push(std::make_unique<Task>(name, id));
       cv.notify_one();
    }

    std::unique_ptr<Task> popFirstTaskInQueue()
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        //Thread continues to execute if predicate is true, else lock is released and theread sleeps
        cv.wait(lock, [this] { return (stop || !tasks.empty()); });
        //Above line without predicate wait until negation of predicate is true
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
            std::lock_guard<std::mutex> lock(queue_mutex);
            stop = false;
        }
        cv.notify_all();
    }
};

class ThreadPool
{
private:
    std::vector<std::thread> workers;
    TaskQueue& task_queue;

    void worker_thread_function()
    {
        while(true)
        {
            auto currentTask = task_queue.popFirstTaskInQueue();
            if(!currentTask) break;

            std::stringstream s;
            s << "Thread " << std::this_thread::get_id() << " is processing " << currentTask->getId() << " : " << 
            currentTask->getName() << "\n";
            safe_print(s.str());
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    }
public:
    ThreadPool(TaskQueue& queue, size_t numThreads) : task_queue(queue)
    {
        for(size_t i = 0; i < numThreads; i++)
        {
            workers.emplace_back(&ThreadPool::worker_thread_function, this);  
        }
    }

    void shutdown()
    {
        task_queue.shutdown();
        for(auto& worker : workers)
        {
            if(worker.joinable())
                worker.join();
        }
    }

    ~ThreadPool()
    {
        shutdown();
    }
};

int main()
{
    TaskQueue myQueue;
    ThreadPool pool(myQueue, 4);
    std::stringstream s;
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
    s << "All tasks added \n";
    safe_print(s.str());

    pool.shutdown();
    s.str("");
    s.clear();
    s << "Program finished \n";
    safe_print(s.str());
    return 0;
}