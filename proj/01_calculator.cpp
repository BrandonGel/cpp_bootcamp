#include <iostream>

int main()
{
    char op;
    double num1, num2,result;
    
    std::cout << "******** CALCULATOR ********" << std::endl;
    std::cout << "Enter either (+ - * /): ";
    std::cin >> op;

    std::cout << "Enter the first number: ";
    std::cin >> num1;

    std::cout << "Enter the second number: ";
    std::cin >> num2;

    switch(op)
    {
        case '+':
            result = num1 + num2;
            std::cout<< "Results: " << result <<std::endl;
            break;
        case '-':
            result = num1 - num2;
            std::cout<< "Results: " << result <<std::endl;
            break;
        case '*':
            result = num1 * num2;
            std::cout<< "Results: " << result <<std::endl;
            break;
        case '/':
            result = num1 / num2;
            std::cout<< "Results: " << result <<std::endl;
            break;
        default:
            break;
    }

    std::cout << "*************************" << std::endl;

}