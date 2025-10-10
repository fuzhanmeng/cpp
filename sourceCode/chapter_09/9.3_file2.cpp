// file2.cpp -- contains functions called in file1.cpp

#include <cmath>
#include <iostream>

#include "9.1_coordin.h"

//  convert rectangular to polar coordinates
polar rect_to_polar(rect xypos)
{
    polar answer;

    answer.distance = std::sqrt(xypos.x * xypos.x + xypos.y * xypos.y);
    answer.angle = std::atan2(xypos.x, xypos.y);

    return answer;
}

//  show polar coordinates, converting angle to degrees
void show_polar(polar dapos)
{
    const double Rad_to_deg = 57.29577951;
    std::cout << "distance = " << dapos.distance;
    std::cout << ", angle = " << dapos.angle * Rad_to_deg;
    std::cout << " degrees\n";
}