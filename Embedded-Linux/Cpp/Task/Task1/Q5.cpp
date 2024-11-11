
#include <iostream>
#include <string>

struct Name {
    std::string firstName;
    std::string middleName;
    std::string lastName;
};

struct DateOfBirth {
    int day;
    int month;
    int year;
};

struct Address {
    std::string street;
    std::string city;
    std::string country;
};

struct Contacts {
    std::string telephoneNumber;
    std::string mobileNumber;
    std::string emailAddress;
};

struct Salary {
    double basic;
    double additional;
    double reductions;
    double taxes;
};

struct Employee {
    Name name;
    DateOfBirth dateOfBirth;
    Address address;
    Contacts contacts;
    std::string job;
    Salary salary;
};

int main() {
    // Example of creating an employee
    Employee employee = {
        {"Mina", "Magdy", "Aziz"},                          // Name
        {26, 7, 1998},                                      // Date of Birth
        {"26", "Shoubra", "Cairo"},                         // Address
        {"01203591115", "01203591115", "mina@gmail.com"},   // Contacts
        "Software Engineer",                                // Job
        {50000.0, 5000.0, 2000.0, 10000.0}                  // Salary
    };

    // Example output
    std::cout << "Name: " << employee.name.firstName << " "
        << employee.name.middleName << " " << employee.name.lastName << std::endl;
    std::cout << "Date of Birth: " << employee.dateOfBirth.day << "/"
        << employee.dateOfBirth.month << "/" << employee.dateOfBirth.year << std::endl;
    std::cout << "Address: " << employee.address.street << ", "
        << employee.address.city << ", " << employee.address.country << std::endl;
    std::cout << "Contacts: " << std::endl;
    std::cout << "  Telephone: " << employee.contacts.telephoneNumber << std::endl;
    std::cout << "  Mobile: " << employee.contacts.mobileNumber << std::endl;
    std::cout << "  Email: " << employee.contacts.emailAddress << std::endl;
    std::cout << "Job: " << employee.job << std::endl;
    std::cout << "Salary: " << std::endl;
    std::cout << "  Basic: " << employee.salary.basic << std::endl;
    std::cout << "  Additional: " << employee.salary.additional << std::endl;
    std::cout << "  Reductions: " << employee.salary.reductions << std::endl;
    std::cout << "  Taxes: " << employee.salary.taxes << std::endl;

    return 0;
}
