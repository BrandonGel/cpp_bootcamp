#include <iostream>

void sort(int array[], int size);

int main()
{
    int array[] = {10,1,9,2,8,3,7,4,6,5};
    int size = std::size(array);
    sort(array,size);

    for(int element:array)
    {
        std::cout << element << " ";
    }
}

void sort(int array[], int size)
{
    int temp;
    for (int i =0; i < size-1; i++)
    {
        for(int j = i; j < size-1; j++)
        {
            if(array[j] > array[j+1])
            {
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}