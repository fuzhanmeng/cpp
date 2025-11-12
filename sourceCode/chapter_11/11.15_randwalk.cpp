// randwalk.cpp -- using the Vector class
// compile with the vect.cpp file

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "11.13_vector.h"

int main()
{
    // using VECTOR::Vector;
    srand(time(0)); // seed random-number generator

    double direction;

    VECTOR::Vector step;
    VECTOR::Vector result(0.0, 0.0);

    unsigned long steps = 0;
    double target;
    double dstep;

    std::cout << "Enter target distance (q to quit): ";
    while (std::cin >> target)
    {
        std::cout << "Enter steps length: ";
        if (!(std::cin >> dstep))
        {
            // enter error, cin return false, !false is trus, enter if
            break;
        }

        while (result.getmagval() < target)
        {
            direction = rand() % 360;
            step.reset(dstep, direction, VECTOR::Vector::POL);
            result = result + step;
            steps++;
        }

        std::cout << "After " << steps << " steps, the subject has the following location:\n";
        std::cout << result << std::endl;
        result.polar_mode();
        std::cout << " or\n" << result << std::endl;
        std::cout << "Average outward distance per step = " << result.getmagval() / steps << std::endl;
        steps = 0;
        result.reset(0.0, 0.0);
        std::cout << "Enter target distance (q to quit): ";
    }

    return 0;
}