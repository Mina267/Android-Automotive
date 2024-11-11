#include <iostream>
#include <thread>
#include <chrono>


void beepFunction(int delay) {
    while (true) {
        std::cout << '\a' << std::flush; // Beep
        std::this_thread::sleep_for(std::chrono::seconds(delay));
    }
}

void waitForEnter() {
    std::cout << "Press Enter to stop the beep..." << std::endl;
    std::cin.get();
    std::cout << "Beep stopped terminated." << std::endl;
    exit(0);
}

int main() {
    bool running = true;

    std::thread beepThread(beepFunction, 3);

    std::thread inputThread(waitForEnter);

    beepThread.join();
    inputThread.join();

    
    return 0;
}
