// vector.h -- 
/**
 * @file 11.13_vector.cpp
 * @brief Vextor class with <<, mode state
 * @author fzm
 * @date 2025-11-13
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include <ostream>

namespace VECTOR
{
class Vector
{
public:
    // RECT for rectangular, POL for Polar modes
    enum Mode
    {
        RECT,
        POL
    };

public:
    Vector();
    Vector(double n1, double n2, Mode from = RECT);
    ~Vector();

    void reset(double n1, double n2, Mode form = RECT);
    double getxval() const { return x; }
    double getyval() const { return y; }
    double getmagval() const { return mag; }
    double getangval() const { return ang; }
    void polar_mode();
    void rect_mode();

    // operator voerloading
    Vector operator+(const Vector& b) const;
    Vector operator-(const Vector& b) const;
    Vector operator-() const;
    Vector operator*(double n) const;

    // friends
    friend Vector operator*(double n, const Vector& a);
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);

private:
    double x;   // horizontal value
    double y;   // vertical value
    double mag; // length of vector
    double ang; // direction of vector in degrees
    Mode mode;  // RECT or POL

private:
    // private methods for setting values
    void set_mag();
    void set_ang();
    void set_x();
    void set_y();
};
} // namespace VECTOR

#endif