/**
 * @file 12.3_vegnews.cpp
 * @brief using new and deleted with classes
 * @author fzm
 * @date 2025-11-20
 */

#include <iostream>

#include "12.1_stringBag.h"

void callme1(StringBad& stb1);
void callme2(StringBad stb2);

int main()
{
    std::cout << "Starting an inner block." << std::endl;

    StringBad headline1("Celery Stalks at Midnight");
    StringBad headline2("lettuce Prey");
    StringBad sports("Spinach Leaves Bowl for Dollars");

    std::cout << "---------------------------" << std::endl;

    std::cout << "headline1: " << headline1 << std::endl;
    std::cout << "headline2: " << headline2 << std::endl;
    std::cout << "sports: " << sports << std::endl;

    std::cout << "---------------------------" << std::endl;

    callme1(headline1);
    std::cout << "headline1 " << headline1 << std::endl;

    std::cout << "---------------------------" << std::endl;
    callme2(headline2);
    std::cout << "headline2" << headline2 << std::endl;

    std::cout << "initialize one object to another" << std::endl;
    StringBad sailor = sports;
    std::cout << "sailor: " << sailor << std::endl;

    std::cout << "---------------------------" << std::endl;
    std::cout << "Assign one object t another" << std::endl;
    StringBad knot;
    knot = headline1;
    std::cout << "knot: " << knot << std::endl;
    std::cout << "Exiting the block" << std::endl;

    std::cout << "end of the main" << std::endl;

    return 0;
}

void callme1(StringBad& stb1)
{
    std::cout << "String passed by reference: " << std::endl;
    std::cout << stb1 << std::endl;
}

void callme2(StringBad stb2)
{
    std::cout << "String passed by value " << std::endl;
    std::cout << "   \"" << stb2 << "\n";
}