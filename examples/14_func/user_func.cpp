#include <iostream>


void happyBirthday(std::string name);

int main()
{
    std::string name = "bro";
    happyBirthday(name);
    return 0;
}

void happyBirthday(std::string name){
    std::cout << "Happy Birthday to " << name << std::endl;
}
