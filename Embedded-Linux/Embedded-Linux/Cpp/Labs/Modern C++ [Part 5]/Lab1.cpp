#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) 
	{
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }

    std::vector<int> numbers;
    int number;
    while (inputFile >> number) 
	{
        numbers.push_back(number);
    }

    if (numbers.empty()) 
	{
        std::cout << "No data in input file!" << std::endl;
        return 1;
    }

    int sum = 0;
    int min = 0x7FFFFFFF;
    int max = 0x80000000;

    for (int num : numbers) {
        sum += num;
        if (num < min) min = num;
        if (num > max) max = num;
    }

    double avg = static_cast<double>(sum) / numbers.size();

    // Use fixed widths for each column According to the max condition, the maximum value of a single input value is 100000.
    int colWidth = 10;

    outputFile << std::fixed << std::setprecision(2);
    
    outputFile  << "| " << std::setw(5) << " " << std::setw(7) << std::left << "Sum"
        << " | " << std::setw(5) << " " << std::setw(7) << std::left << "Avg"
        << " | " << std::setw(5) << " " << std::setw(7) << std::left << "Min"
        << " | " << std::setw(5) << " " << std::setw(7) << std::left << "Max" << " |" << std::endl;


    outputFile << std::setw((colWidth * 6) + 1) << std::setfill('-') << "" << std::endl << std::setfill(' ');

    
    outputFile << "| " << std::setw(3) << " " << std::setw(9) << sum
        << " | " << std::setw(3) << " " << std::setw(9) << avg
        << " | " << std::setw(3) << " " << std::setw(9) << min
        << " | " << std::setw(3) << " " << std::setw(9) << max << " |" << std::endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
