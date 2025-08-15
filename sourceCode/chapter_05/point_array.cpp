//  练习数组指针和指针数组

#include <iostream>

int main ()
{
    //  指针数组 每个元素都是指针
    int a = 10, b = 20;
    int* array[5] = {&a, &b, new int(10), new int(2), nullptr};
    for (int i = 0; i < 5; i++)
    {
        if (array[i] != nullptr)
        {
            std::cout << "array value is "<< *array[i] << " address is " << array[i] << std::endl;
        }
        else
        {
            std::cout << "nullprt" << std::endl;
        }
    }
    
    //  数组指针 每个元素都是int  
    int (*arr)[5];
    for (int i = 0; i < 4; i++)
    {
        std::cout << arr[i] << std::endl;
    }
    

    return 0;
}