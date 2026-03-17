#include <iostream>

struct Car{
    std::string model;
    int year;
    std::string color;
};

void printCar(Car car);
void printCar2(Car &car);
void paintCar(Car &car, std::string color);

int main()
{
    // When passing structs to function, you pass in value (a copy), so passing a copy
    // If you work on the original struct, pass the address.
    Car car1,car2;

    car1.model= "Mustang";
    car1.year = 2023;
    car1.color = "red";

    car2.model = "Corvette";
    car2.year = 2024;
    car2.color = "blue";

    printCar(car1);
    printCar(car2); 

    paintCar(car1,"silver");
    paintCar(car2,"gold");

    printCar2(car1);
    printCar2(car2); 

    return 0;
}

void printCar(Car car)
{
    std::cout << &car << std::endl;
    std::cout << car.model << std::endl;
    std::cout << car.year << std::endl;
    std::cout << car.color << std::endl;
}

void printCar2(Car &car)
{
    std::cout << &car << std::endl;
    std::cout << car.model << std::endl;
    std::cout << car.year << std::endl;
    std::cout << car.color << std::endl;
}

void paintCar(Car &car, std::string color)
{
    car.color = color;
}