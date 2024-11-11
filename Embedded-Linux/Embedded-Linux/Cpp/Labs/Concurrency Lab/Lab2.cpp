#include <iostream>
#include <thread>
#include <atomic>

class Spinlock {

    std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:

    void lock() {
        int counter = 0;
        while (flag.test_and_set(std::memory_order_acquire)) {
            ++counter;
            if (counter >= 20) {
                std::this_thread::yield(); 
                counter = 0;
            }
        }
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }

};


// Shared variable
int shared_var = 50;

// Spinlock instance
Spinlock spinlock;

void multiply_by_two() {
    for (int i = 0; i < 10; ++i) {
        spinlock.lock();
        shared_var *= 2;
        std::cout << "Multiplied by 2: " << shared_var << std::endl;
        spinlock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void divide_by_two() {
    for (int i = 0; i < 10; ++i) {
        spinlock.lock();
        shared_var /= 2;
        spinlock.unlock();
        std::cout << "Divided by    2: " << shared_var << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    int shared_var = 1;
    Spinlock spinlock;

    std::thread t1(multiply_by_two);
    std::thread t2(divide_by_two);

    t1.join();
    t2.join();

    return 0;
}



