#include <iostream>

void printInfo(const std::string name,const int age);

int main()
{
    std::string name = "Bro";
    int age = 21;
    
    printInfo(name,age);
    return 0;
}

void printInfo(const std::string name,const int age)
{
    // Does not change the parameters (read only)
    // Useful for references and pointers
    std::cout << name << std::endl;
    std::cout << age << std::endl;
}