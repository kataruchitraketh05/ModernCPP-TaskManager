#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex counter_mutex;

void increment_counter()
{
    for(int i = 0; i < 10000; i++)
    {
        //Lock guard inside for loop for concurrency
        std::lock_guard<std::mutex> lock(counter_mutex);
        counter ++;
    }
}

int main()
{
    std::vector<std::thread> threads;
    for(int i = 0; i < 10; i++)
    {
        threads.emplace_back(increment_counter);
    }

    for(auto& t: threads)
    {
        t.join();
    }
    std::cout << "\nFinal value of counter is " << counter << "\n";
    return 0;
}