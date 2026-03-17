#include <iostream>

class Stove{
    private:
        int temperature = 0;
    public:
    
    int getTemperature()
    {
        return temperature;
    }
    void setTemperature(int temperature)
    {
        if(temperature <0)
        {
            this->temperature = 0;
        }
        else if(temperature > 500)
        {
            this->temperature = 500;
        }
        else
        {
            this->temperature = temperature;
        }
    }
};

int main()
{
    Stove stove;
    stove.setTemperature(350);
    std::cout << "The temperature setting is: " << stove.getTemperature() << std::endl;
    return 0;
}