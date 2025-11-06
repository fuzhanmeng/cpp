// usetime1.cpp -- using the second draft of the Time class
// compile usetime1.cpp and mytime1.cpp together
#include <iostream>

#include "11.4_mytime1.h"

int main()
{
    Time planning;
    Time coding(2, 40);
    Time fixing(5, 55);
    Time total;

    std::cout << "planning time = ";
    planning.Show();
    std::cout << std::endl;

    std::cout << "coding time = ";
    coding.Show();
    std::cout << std::endl;

    std::cout << "fixing time = ";
    fixing.Show();
    std::cout << std::endl;

    total = coding + fixing;
    // operator notation
    std::cout << "coding + fixing = ";
    total.Show();
    std::cout << std::endl;

    Time morefixing(3, 28);
    std::cout << "more fixing time = ";
    morefixing.Show();
    std::cout << std::endl;

    total = morefixing.operator+(total);
    std::cout << "morefixing.operator+(total) = ";
    total.Show();
    std::cout << std::endl;

    return 0;
}