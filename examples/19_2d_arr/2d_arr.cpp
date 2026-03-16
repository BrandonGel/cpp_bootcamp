#include <iostream>

int main()
{
    std::string cars[][3] = {{"Mustang", "Escape", "F-150"},
                            {"Corvette", "Equinox", "Silverado"},
                            {"Challenger", "Durango", "Ram 1500"}};
    int rows = std::size(cars);
    int cols = std::size(cars[0]);
    for (int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            std::cout << cars[i][j] << " ";
        }
        std::cout << std::endl;
    }
}