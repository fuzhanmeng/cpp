// file1.cpp -- example of a three-file program

#include <iostream>

#include "9.1_coordin.h"

int main()
{
    rect rplace;
    polar pplace;

    std::cout << "enter the x and y values: ";
    while (std::cin >> rplace.x >> rplace.y)
    {
        pplace = rect_to_polar(rplace);
        show_polar(pplace);
        std::cout << "Next two numbers (q to quit): ";
    }

    std::cout << "Bye!\n";

    return 0;
}