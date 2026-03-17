#include <iostream>

void swap(std::string &x, std::string &y);

int main()
{
    std::string x = "Kool-Aid";
    std::string y = "Water";
    
    swap(x,y);
    std::cout << "x: " << x << " " << &x << std::endl;
    std::cout << "y: " << y << " " << &y << std::endl;

}

void swap(std::string &x, std::string &y)
{
    // Swap the value of x and y, but not the memory address of x and y
    std::cout << "x: " << x << " " << &x << std::endl;
    std::cout << "y: " << y << " " << &y << std::endl;
    std::string temp;
    temp = x;
    x = y;
    y = temp;
}