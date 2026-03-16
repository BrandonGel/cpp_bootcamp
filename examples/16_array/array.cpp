#include <iostream>

int main()
{
    std::string car[] = {"Corvette", "Mustang", "Camry"};
    std::cout << car[0] << std::endl;
    std::cout << car[1] << std::endl;
    std::cout << car[2] << std::endl;

    std::string car2[3];
    car2[0] = "Corvette";
    car2[1] = "Mustang";
    car2[2] = "Camry";
    std::cout << car2[0] << std::endl;
    std::cout << car2[1] << std::endl;
    std::cout << car2[2] << std::endl;

    return 0;
}