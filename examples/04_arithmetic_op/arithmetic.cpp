#include <iostream>

int main()
{
    double students = 20;
    std::cout << "Students: " << students << std::endl;
    students++;
    std::cout << "Students: " << students << std::endl;
    students--;
    std::cout << "Students: " << students << std::endl;
    students*=2;
    std::cout << "Students: " << students << std::endl;
    students/=2;
    std::cout << "Students: " << students << std::endl;

    int students_int = 20;
    int remainder = students_int% 3;
    std::cout << "Remainder: " << remainder << std::endl;
       
}