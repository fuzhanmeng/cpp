/**
 * @file 11.20_stonewt1
 * @brief Stonewt class methods + conversion functions
 * @author fzm
 * @date 2025-11-13
 */
#include <iostream>

#include "11.19_stonewt1.h"

// construct Stonewt object from double value
Stonewt::Stonewt(double lbs)
{
    std::cout << "use Stonewt(double lbs)" << std::endl;
    stone = int(lbs) / Lbs_per_stn; // integer division
    pds_left = int(lbs) % Lbs_per_stn + lbs - int(lbs);
    pounds = lbs;
}

// construct Stonewt object from stone, double values
Stonewt::Stonewt(int stn, double lbs)
{
    std::cout << "use Stonewt(int stn, double lbs)" << std::endl;
    stone = stn;
    pds_left = lbs;
    pounds = stn * Lbs_per_stn + lbs;
}

Stonewt::Stonewt() // default constructor, wt = 0
{
    std::cout << "use Stonewt()" << std::endl;
    stone = pounds = pds_left = 0;
}

Stonewt::~Stonewt() // destructor
{
}

// show weight in stones
void Stonewt::show_stn() const { std::cout << stone << " stone, " << pds_left << " pounds\n"; }

// show weight in pounds
void Stonewt::show_lbs() const { std::cout << pounds << " pounds\n"; }

// conversion functions
Stonewt::operator int() const
{
    std::cout << "use operator int()" << std::endl;
    return int(pounds + 0.5);
}

Stonewt::operator double() const
{
    std::cout << "use operator double()" << std::endl;
    return pounds;
}
