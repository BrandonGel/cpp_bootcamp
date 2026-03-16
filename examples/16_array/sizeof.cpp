#include <iostream>

int main()
{
    double gpa = 2.5;
    std::cout << "gpa size: " << sizeof(gpa) << " bytes" << std::endl;

    std::string name = "Bro";
    std::cout << "name size: " << sizeof(name) << " bytes" << std::endl;

    char grade = 'F';
    std::cout << "grade size: " << sizeof(grade) << " bytes" << std::endl;

    bool student = true;
    std::cout << "student size: " << sizeof(student) << " bytes" << std::endl;

    char grades[] = {'A', 'B', 'C', 'D', 'F'};
    std::cout << "grades size: " << sizeof(grades) << " bytes" << std::endl;
    std::cout << sizeof(grades)/sizeof(char) << " elements" << std::endl;
    std::cout << std::size(grades) << " elements" << std::endl;

    return 0;
}