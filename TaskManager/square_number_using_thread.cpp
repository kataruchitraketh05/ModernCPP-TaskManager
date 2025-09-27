#include <iostream>
#include <thread>
#include <future>

int square(int num)
{
    return num * num;
}

void calculate_square_with_promise(int x, std::promise<int> p)
{
    int result = square(x);
    p.set_value(result);
}

void simple_thread_approach(int num)
{
    int result = 0;
    std::thread t([&result, &num] {
        result = square(num);
    });

    t.join();

    std::cout << "Square of " << num << " using simple thread is " << result << "\n";
}

void thread_promise_approach(int num)
{
    std::promise<int> promise_result;
    std::future<int> square_result_from_promise = promise_result.get_future();
    std::thread t(calculate_square_with_promise, num, std::move(promise_result));
    int result = square_result_from_promise.get();

    t.join();

   std::cout << "Square of " << num << " using promise/future thread is " << result << "\n";
}

void async_approach(int num)
{
    std::future<int> future_result = std::async(square, num);
    int result = future_result.get();
    std::cout << "Square of " << num << " using async is " << result << "\n";
}

int main()
{
    simple_thread_approach(15);
    thread_promise_approach(20);
    async_approach(176);
    return 0;
}