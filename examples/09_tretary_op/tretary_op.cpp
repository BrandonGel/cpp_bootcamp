#include <iostream>

int main()
{
    int grade = 50;
    grade >= 60 ? std::cout << "You pass!" << std::endl : std::cout << "You fail!" << std::endl;

    int num = 9;
    num % 2 ? std::cout << "ODD" << std::endl: std::cout << "EVEN" << std::endl;

    bool hungry = true;
    hungry ? std::cout << "You are hungry" << std::endl: std::cout << "You are full" << std::endl;
    std::cout << (hungry ? "You are hungry" : "You are full") << std::endl;
}