//  forloop.cpp --- introducing for loop

#include <iostream>

int main ()
{
    int i = 0;
    for (size_t i = 0; i < 5; i++)
    {
        std::cout << "C++ knows loops i = " << i << std::endl;
    }
    
    std::cout << "C++ knows when to stop" << std::endl;

    return 0;
}
