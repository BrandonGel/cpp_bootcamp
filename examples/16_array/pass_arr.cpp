#include <iostream>

double getTotal(double prices [], int size);

int main()
{
    double prices[]= {4.99, 5.99, 6.99};
    int size = std::size(prices);
    double total = getTotal(prices, size);
    std::cout << "Total: " << total << std::endl;
    return 0;
}

double getTotal(double prices[], int size)
{
    double total = 0.0;
    for(int i = 0; i < size; i++)
    {
        total += prices[i];
    }
    return total;
}