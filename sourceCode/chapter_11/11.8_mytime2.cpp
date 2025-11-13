/**
 * @file 11.8_mytime2.cpp
 * @brief implementing Time methods
 * @author fzm
 * @date 2025-11-13
 */

#include <iostream>
#include "11.7_mytime2.h"

Time::Time()
{
}

Time::Time(int h, int m)
{
    hours = h;
    minutes = m;
}

void Time::Addmin(int m)
{
    minutes += m;
    hours += minutes / 60;
    minutes %= 60;
}

void Time::Addhours(int h)
{
    hours += h;
}

void Time::Reset(int h, int m)
{
    hours = h;
    minutes = m;
}

Time Time::operator+(const Time& t) const
{
    Time sum;
    sum.minutes = minutes + t.minutes;
    sum.hours = hours + t.hours + sum.minutes / 60;
    sum.minutes %= 60;

    return sum;
}

Time Time::operator-(const Time& t) const
{
    Time diff;
    int tot1, tot2;
    tot1 = t.minutes + t.hours * 60;
    tot2 = minutes + hours * 60;

    diff.minutes = (tot2 - tot1)  % 60;
    diff.hours = (tot2 - tot1) / 60;

    return diff;

}

Time Time::operator*(double mult) const
{
    Time result;
    long totalminutes = hours * mult * 60 + minutes * mult;
    result.hours = totalminutes / 60;
    result.minutes = totalminutes % 60;

    return result;
}

void Time::Show() const
{
    std::cout << hours << " hours, " << minutes << " minutes";
}