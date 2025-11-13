/**
 * @file 11.9_usetime2.cpp
 * @brief using the third draft of the Time class
 * @author fzm
 * @date 2025-11-13
 */

#include <iostream>

#include "11.7_mytime2.h"

int main()
{
    Time weeding(4, 35);
    Time waxing(2, 47);
    Time total;
    Time diff;
    Time adjusted;

    std::cout << "weeding time = ";
    weeding.Show();
    std::cout << std::endl;

    std::cout << "waxing time = ";
    waxing.Show();
    std::cout << std::endl;

    // use operator+()
    std::cout << "total work time = ";
    total = weeding + waxing;
    total.Show();
    std::cout << std::endl;

    // use operator-()
    std::cout << "weeding - waxing = " << std::endl;
    diff = weeding - waxing;
    diff.Show();
    std::cout << std::endl;

    // use operator*()
    std::cout << "adjusted work time = " << std::endl;
    adjusted = total * 1.5;
    adjusted.Show();
    std::cout << std::endl;

    return 0;
}