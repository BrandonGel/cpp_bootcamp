#include <iostream>

class Animal{
    public:
        bool alive = true;
    void eat()
    {
        std::cout << "This animal is eating." << std::endl;
    }
};

class Dog:public Animal{
    public:
    
    void bark()
    {
        std::cout <<"The dog goes woof!" << std::endl;
    }
};

class Cat: public Animal{
    public:
    void meow()
    {
        std::cout << "The cat goes meow!" << std::endl;
    }
};

class Shape{
    public:
        double area;
        double volume;
};

class Cube: public Shape{
    public:
        double side;
    Cube(double side)
    {
        this->side = side;
        this->area = side*side*6;
        this->volume = side*side*side;
    }
};

class Sphere: public Shape{
    public:
        double radius;
    Sphere(double radius)
    {
        this->radius = radius;
        this->area = 4*3.1459*(radius*radius);
        this->volume = (4/3)*3.1459*(radius*radius*radius);
    }
};

int main()
{
    // inheritance = a class can be based on another class, using the same implementation and adding new features to it
    //              also known as an "is a" relationship
    Dog dog;
    std::cout << dog.alive << std::endl;
    dog.eat();
    dog.bark();

    Cat cat;
    std::cout << cat.alive << std::endl;
    cat.eat();
    cat.meow();

    Cube cube(10);
    std::cout << "Area: : " << cube.area << "cm^2" << std::endl;
    std::cout << "Volume: " << cube.volume << "cm^3" << std::endl;

    Sphere sphere(5);
    std::cout << "Area: " << sphere.area << "cm^2" << std::endl;
    std::cout << "Volume: " << sphere.volume << "cm^3" << std::endl;

    return 0;
}