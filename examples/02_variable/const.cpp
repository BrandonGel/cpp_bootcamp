#include <iostream>

using namespace std;

int main()
{
    // const will set the variable to be NOT changed
    const double PI = 3.1415;
    double radius = 10;
    double circumference = 2*PI*radius;

    std::cout << circumference << " cm" << std::endl;
}