#include <iostream>

int getDigit(const int number);
int sumOddDigits(const std::string cardNumber);
int sumEvenDigits(const std::string cardNumber);

int main()
{
    std::string cardNumber;
    int result = 0;

    std::cout << "Enter a credit card #: ";
    std::cin >> cardNumber;

    result = sumEvenDigits(cardNumber) + sumOddDigits(cardNumber);

    bool isValid = result%10 == 0;
    if(isValid)
    {
        std::cout << "Your credit number is valid" << std::endl;
    }
    else
    {
        std::cout << "Your credit number is NOT valid" << std::endl;
    }
    
    return 0;
}


int getDigit(const int number)
{
    return number %10 + (number/10)%10;
}

int sumOddDigits(const std::string cardNumber)
{
    int sum = 0;
    for (int i = cardNumber.size() -1; i >= 1; i-=2)
    {
        sum += cardNumber[i]-'0';
    }
    return sum;
}

int sumEvenDigits(const std::string cardNumber)
{
    int sum = 0;
    for (int i = cardNumber.size() -2; i >= 0; i-=2)
    {
        sum += getDigit((cardNumber[i]-'0')*2);
    }
    return sum;
}