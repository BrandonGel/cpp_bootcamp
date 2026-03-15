#include <iostream>

int main()
{
    std::string name;
    std::cout << "What's your name?: ";
    std::cin >> name;

    std::string fullName;
    std::cout<< "What's your full name?: ";
    std::getline(std::cin >> std::ws, fullName);

    int age;
    std::cout << "What is your age?: ";
    std::cin >> age;

    std::cout << "Hello " << name << std::endl;
    std::cout << "Your full name is " << fullName << std::endl;
    std::cout << "You are " << age << std::endl;
}
