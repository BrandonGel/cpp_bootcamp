#include <iostream>

int main()
{
    std::string name = "Bro";
    int age = 21;
    std::string freePizzas[5] = {"pizza1","pizza2","pizza3","pizza4","pizza5"};
    
    std::string *pName = &name;
    int *pAge = &age;
    std::string *pFreePizza = freePizzas;


    std::cout << *pName << std::endl;
    std::cout << *pAge << std::endl;
    std::cout << *pFreePizza << " " << pFreePizza << " " << freePizzas << std::endl;
}