/**
 * @file 11.4_mytime1.h
 * @brief Time class before operator over loading
 * @author fzm
 * @date 2025-11-13
 */

#ifndef MYTIME1_H_
#define MYTIME1_H_

class Time
{
public:
    Time();
    Time(int h, int m = 0);

    void AddMin(int m);
    void Addhour(int h);
    void Reset(int h, int m);
    void Show() const;

    Time operator+(const Time& t) const;

private:
    int hours;
    int minutes;
};

#endif