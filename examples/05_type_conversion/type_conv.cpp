#include<iostream>

int main()
{
    double x = 3.14;
    std::cout << x << std::endl;
    std::cout << (int)x << std::endl;

    char c = 100;
    std::cout << c << std::endl;
    std::cout << (char)100 << std::endl;

    int correct = 8;
    int questions = 10;
    double score = correct/(double)questions * 100;
    std::cout << score << "%" <<std::endl;

}