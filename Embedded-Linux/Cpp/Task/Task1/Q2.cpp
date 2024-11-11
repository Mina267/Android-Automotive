
#include <iostream>
#include <iomanip>

void convertToHMS(int totalSeconds) {
    int hours = totalSeconds / 3600;
    totalSeconds %= 3600;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    std::cout << "H:M:S - " << hours << ":" << minutes << ":" << seconds << std::endl;
}

int main() {
    int totalSeconds;
    std::cout << "Enter total seconds: ";
    std::cin >> totalSeconds;
    convertToHMS(totalSeconds);
    return 0;
}
