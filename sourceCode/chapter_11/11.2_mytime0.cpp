/**
 * @file 11.2_mytime0.cpp
 * @brief implementing Time methods
 * @author fzm
 * @date 2025-11-13
 */

#include <iostream>

#include "11.1_mytime0.h"

Time::Time()
{
    hours = 0;
    minutes = 0;
    std::cout << "run Time()" << std::endl;
}

Time::Time(int h, int m)
{
    hours = h;
    minutes = m;
    std::cout << "run Time(int h, int m)" << std::endl;
}

void Time::AddHour(int h) { hours += h; }

void Time::AddMin(int m)
{
    minutes += m;
    hours += minutes / 60;
    minutes %= 60;
}

void Time::Reset(int h, int m)
{
    hours = h;
    minutes = m;
}

void Time::Show() const
{
    std::cout << "hours = " << hours << ", minutes = " << minutes << std::endl;
}

const Time Time::Sum(const Time& t) const
{
    Time sum;
    sum.minutes = minutes + t.minutes;
    sum.hours = hours + t.hours + sum.minutes / 60;
    sum.minutes %= 60;
    return sum;
}