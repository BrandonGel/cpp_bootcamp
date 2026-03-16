#include <iostream>

void bakePizza();
void bakePizza(std::string topping);
void bakePizza(std::string topping1,std::string topping2);

int main()
{
    bakePizza();
    bakePizza("pepperoni");
    bakePizza("pepperoni", "mushroom");
    return 0;
}

void bakePizza()
{
    std::cout << "Here is your pizza!" << std::endl;
}

void bakePizza(std::string topping)
{
    std::cout << "Here is your " <<  topping << " pizza!" << std::endl;
}

void bakePizza(std::string topping1,std::string topping2)
{
    std::cout << "Here is your " <<  topping1 << " and " << topping2 << " pizza!" << std::endl;
}