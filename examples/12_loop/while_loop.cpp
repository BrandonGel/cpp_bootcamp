#include <iostream>

int main()
{
    std::string name;

    while(name.empty())
    {
        std::cout << "Enter your name: ";
        std::getline(std::cin,name);    
    }
    std::cout << "Your name is " << name << std::endl;
}