// mytime1.h -- Time class before operator over loading
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