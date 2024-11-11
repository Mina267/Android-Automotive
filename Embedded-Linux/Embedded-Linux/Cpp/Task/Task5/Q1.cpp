#include <iostream>
#include <iomanip>

class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    // Constructor initializing time to 0
    Time() : hours(0), minutes(0), seconds(0) {}

    // Constructor initializing time to specific values
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
        normalizeTime();
    }

    // Function to display time in 11:59:59 format
    void display() const {
        std::cout << std::setfill('0') << std::setw(2) << hours << ":"
            << std::setfill('0') << std::setw(2) << minutes << ":"
            << std::setfill('0') << std::setw(2) << seconds << std::endl;
    }

    // Function to add two Time objects
    void addTime(const Time& t1, const Time& t2) {
        hours = t1.hours + t2.hours;
        minutes = t1.minutes + t2.minutes;
        seconds = t1.seconds + t2.seconds;
        normalizeTime();
    }

private:
    // Normalize the time so that minutes and seconds are within proper range
    void normalizeTime() {
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
    }
};

int main() {
    const Time t1(2, 45, 30); 
    const Time t2(1, 20, 45); 
    Time t3;                  

    t3.addTime(t1, t2); // Add t1 and t2, store the result in t3

    std::cout << "Time 1: ";
    t1.display();
    std::cout << "Time 2: ";
    t2.display();
    std::cout << "Sum of Time 1 and Time 2: ";
    t3.display();

    return 0;
}
