#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

std::atomic<int> counter = 0;

void increment_counter() 
{
    for (int i = 0; i < 10000; ++i) 
    {
        counter++;
    }
}

int main()
{
    std::vector<std::thread> threads;

    //Create and start all threads
    for(int i = 0; i < 10; i++)
    {
        threads.emplace_back(increment_counter);
    }

    for(auto& t : threads)
    {
        t.join();
    }

    std::cout << "\nFinal value of counter is " << counter << "\n";

    return 0;
}