#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <numeric>

// Mutex and condition variable for synchronization
std::mutex results_mutex;
std::condition_variable cv;

int fibonacci(int n) {
    if (n <= 1)
        return n;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

void calculate_fibonacci(int n, std::vector<int>& fibonacci_results, bool& results_ready) {
    int result = fibonacci(n);
    {
        std::lock_guard<std::mutex> lock(results_mutex);
        fibonacci_results.push_back(result);
    }
    cv.notify_one();
}

void print_results_and_sum(std::vector<int>& fibonacci_results, bool& results_ready) {
    std::unique_lock<std::mutex> lock(results_mutex);
    cv.wait(lock, [&results_ready] { return results_ready; });

    std::cout << "Fibonacci results: ";
    for (const auto& result : fibonacci_results) {
        std::cout << result << " ";
    }
    std::cout << std::endl;

    int sum = std::accumulate(fibonacci_results.begin(), fibonacci_results.end(), 0);
    std::cout << "Sum of Fibonacci results: " << sum << std::endl;
}

int main() {
    std::vector<int> fib_numbers = { 4, 9, 14, 17 };
    std::vector<int> fibonacci_results;
    bool results_ready = false;

    std::vector<std::thread> threads;
    for (int n : fib_numbers) {
        threads.emplace_back(calculate_fibonacci, n, std::ref(fibonacci_results), std::ref(results_ready));
    }

    std::thread printer_thread(print_results_and_sum, std::ref(fibonacci_results), std::ref(results_ready));

    for (auto& thread : threads) {
        thread.join();
    }

    {
        std::lock_guard<std::mutex> lock(results_mutex);
        results_ready = true;
    }
    cv.notify_one();
    printer_thread.join();

    return 0;
}
