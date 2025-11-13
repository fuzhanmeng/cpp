/**
 * @file 11.1_mytime0.h
 * @brief Time class before operator over loading
 * @author fzm
 * @date 2025-11-13
 */

#ifndef MYTIME0_H_
#define MYTIME0_H_

class Time
{
public:
    Time();
    Time(int h, int m = 0);

    void AddMin(int m);
    void AddHour(int h);
    void Reset(int h = 0, int m = 0);
    void Show() const;
    const Time Sum(const Time& t) const;

private:
    int hours;
    int minutes;
};

#endif