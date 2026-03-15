#include <iostream>

int main()
{
    // Integer
    int age = 21;
    int year = 2023;
    double daytime = 7.5;
    std::cout << "I am " << age << " in the year " << year << " at " << daytime << " hour." << std::endl;

    // Double 
    double price = 10.99;
    double gpa = 2.5;
    double temperature = 25.1;
    std::cout << "The price is " << price << " while my gpa is " << gpa << " at " << temperature << " degree Celsius." << std::endl;

    // Single Character
    char grade = 'A';
    char initials = 'B';
    std::cout << "My grade is an " << grade << " while my initial is " << initials << std::endl;

    // Boolean (true or false)
    bool student = false;
    bool power = true;
    bool forSale = true;
    std::cout << "The student's answer was " << student << "; however, his statement about power was " << power << ", and its being on sale was " << forSale << std::endl;

    // String 
    std::string name = "Bro";
    std::string day = "Friday";
    std::string food = "pizza";
    std::string address = "123 Fake St.";

    std::cout << "Hello " << name << ", Today is " << day << ", and it's free " << food << " at " << address << std::endl;

    return 0;
}