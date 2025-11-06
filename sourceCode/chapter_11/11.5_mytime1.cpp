// mytime1.h -- Time class before operator overloading

#include <iostream>
#include "11.4_mytime1.h"

Time::Time()
{
    hours = 0;
    minutes = 0;
}

Time::Time(int h, int m)
{
    hours = h;
    minutes = m;
}

void Time::AddMin(int m)
{
    minutes = m;
    hours += minutes / 60;
    minutes += minutes % 60;
}

void Time::Addhour(int h)
{
    hours += h;
}

void Time::Reset(int h, int m)
{
    hours = h;
    minutes = m;
}

void Time::Show() const
{
    std::cout << hours << " hours, " << minutes << " minutes" << std::endl;
}

Time Time::operator+(const Time& t) const
{
    Time sum;
    sum.minutes = minutes + t.minutes;
    sum.hours = hours +t.hours + sum.minutes / 60;
    sum.minutes %= 60;

    return sum;
}