// mytime2.h -- 
/**
 * @file 11.7_mytime2.h
 * @brief Time class after operator voerloading
 * @author fzm
 * @date 2025-11-13
 */

#ifndef MYTIME2_H_
#define MYTIME2_H_

class Time
{
public:
    Time();
    Time(int h, int m = 0);

    void Addmin(int m);
    void Addhours(int h);
    void Reset(int h = 0, int m = 0);

    Time operator+(const Time& t) const;
    Time operator-(const Time& t) const;
    Time operator*(double mult) const;

    void Show() const;

private:
    int hours;
    int minutes;
};

#endif