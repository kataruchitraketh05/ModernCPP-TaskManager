#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <chrono>
#include <memory>
#include <sstream>
#include <condition_variable>

std::mutex cout_mutex; // one global mutex for console output

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
    Task(const std::string& n, int i) : name(n) , id(i)
    {
        s.str("");
        s.clear();
        s << "Task " << id << " created\n"; 
        safe_print(s.str());
    }

    ~Task()
    {
        s.str("");
        s.clear();
        s << "Task " << id << " destroyed\n"; 
        safe_print(s.str());
    }

    std::string getName() const { return name; };
    int getId() const { return id; };
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
        if(stop) return; //Make sure tasks are not added after shutdown
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
            stop = true;
        }
        //First lock mutex then set stop to true and notify 
        cv.notify_all();
    }
};

//Pool wons the task_queue
class ThreadPool
{
private:
   std::vector<std::thread> workers;
   TaskQueue task_queue;

   void worker_thread_function()
   {
        while(true)
        {
            auto currentTask = task_queue.popFirstTaskInQueue();
            if(!currentTask) break;

            std::stringstream s;
            s << "Thread " << std::this_thread::get_id() << " is processing task " << currentTask->getId() << " : " << currentTask->getName() << "\n";
            safe_print(s.str());
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
   }
public:
    ThreadPool(size_t numThreads)
    {
        for(size_t i = 0; i < numThreads; i++)
        {
            workers.emplace_back(&ThreadPool::worker_thread_function, this);
        }
    }

    void addTaskToQueue(const std::string& name, int id)
    {
        task_queue.addTask(name, id);
    }

    void shutdown()
    {
        //1. First shutdown queue so that no new tasks are accepted
        task_queue.shutdown();

        for(auto& worker : workers)
        {
            //2. Now wait fo all the threads finish their work and exit
            if(worker.joinable())
                worker.join();
        }
    }

    // The destructor's job is to ensure shutdown() is called if the user forgets
    ~ThreadPool()
    {
        shutdown();
    }
};

int main()
{
    ThreadPool pool(4); //Create 1 threads
    std::stringstream s;
    s << "Started adding tasks to queue \n";
    safe_print(s.str());
    pool.addTaskToQueue("Write some code", 1);
    pool.addTaskToQueue("Compile the code", 2);
    pool.addTaskToQueue("Test the code", 3);
    pool.addTaskToQueue("Fix bugs, if any", 4);
    pool.addTaskToQueue("Retest once more", 5);
    pool.addTaskToQueue("Code cleanup", 6);
    pool.addTaskToQueue("Push code to cloud", 7);
    pool.addTaskToQueue("Raise a pull request", 8);
    pool.addTaskToQueue("Address review comments, if any", 9);
    pool.addTaskToQueue("Merge PR to main branch", 10);
    s.str("");
    s.clear();
    s << "All tasks are added \n";
    safe_print(s.str());

    pool.shutdown();
    s.str("");
    s.clear();
    s << "Program finished \n";
    safe_print(s.str());
    return 0;
}