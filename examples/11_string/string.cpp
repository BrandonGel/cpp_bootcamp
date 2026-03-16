#include <iostream>

int main()
{
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin,name);

    if(name.length() > 12)
    {
        std::cout << "Your name is longer than 12" << std::endl;
    }
    else if(name.empty())
    {
        std::cout << "You did not enter a name" << std::endl;
    }
    else
    {
        std::cout << "Your name is " << name << std::endl;
    }

    name.append("@gmail.com");
    std::cout << "An email address has been appended to your name: " << name << std::endl;

    int index = 0;
    std::cout << "The index " << index << " of your name is " << name.at(index) << std::endl;

    name.insert(index, "1)");
    std::cout << "We insert this string at index " << index << " of your name:" << name << std::endl;

    name.clear();
    std::cout << "Your name have been cleared \"" << name  << "\"" << std::endl;

    return 0;
}