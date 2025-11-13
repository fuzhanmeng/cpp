// vect.cpp -- 
/**
 * @file 11.14_vector.cpp
 * @brief methods for the Vector class
 * @author fzm
 * @date 2025-11-13
 */

#include <cmath>
#include <iostream>
#include <ostream>

#include "11.13_vector.h"

namespace VECTOR
{
// compute degress in one dadian
const double Rad_to_deg = 45.0 / std::atan(1.0);
// should be about 57.2957795130823

// private methods
// calculates magnitude from x and y

void Vector::set_mag() { mag = std::sqrt(x * x + y * y); }
void Vector::set_ang()
{
    if (0.0 == x && 0.0 == y)
    {
        ang = 0.0;
    }
    else
    {
        ang = std::atan2(y, x);
    }
}

void Vector::set_x() { x = mag * cos(ang); }

void Vector::set_y() { y = mag * sin(ang); }

Vector::Vector()
{
    x = y = mag = ang = 0;
    mode = RECT;
}

// construct vector from rectangular coordinates if form is r
// (the default) or else from polar coordinates if form is p

Vector::Vector(double n1, double n2, Mode form)
{
    mode = form;
    if (form == RECT)
    {
        x = n1;
        y = n2;
        set_ang();
        set_mag();
    }
    else if (form == POL)
    {
        mag = n1;
        ang = n2 / Rad_to_deg;
        set_x();
        set_y();
    }
    else
    {
        std::cout << "Incorrect 3rd argument to Vector() -- ";
        std::cout << "vector set to 0\n";
        x = y = mag = ang = 0.0;
        mode = RECT;
    }
}

// reset vector from rectangular coordinates if form is
// RECT (the default) or else from polar coordinates if
// form is POL

void Vector::reset(double n1, double n2, Mode form)
{
    mode = form;
    if (form == RECT)
    {
        x = n1;
        y = n2;
        set_ang();
        set_mag();
    }
    else if (form == POL)
    {
        mag = n1;
        ang = n2 / Rad_to_deg;
        set_x();
        set_y();
    }
    else
    {
        std::cout << "Incorrect 3rd argument to Vector() -- ";
        std::cout << "vector set to 0\n";
        x = y = mag = ang = 0.0;
        mode = RECT;
    }
}

Vector::~Vector() // destructor
{
}

void Vector::rect_mode() { mode = RECT; }

void Vector::polar_mode() { mode = POL; }

// operator overloading
// add two Vectors
Vector Vector::operator+(const Vector& b) const { return Vector(x + b.x, y + b.y); }

// subtract Vector b from a
Vector Vector::operator-(const Vector& b) const { return Vector(x - b.x, y - b.y); }

// reverse sign of Vector
Vector Vector::operator-() const { return Vector(-x, -y); }

// multiply vector by n
Vector Vector::operator*(double n) const
{
    std::cout << "operator *" << std::endl;
    return Vector(x * n, y * n);
}

// friend methods
// multioly n by Vector a
Vector operator*(double n, const Vector& a)
{
    std::cout << "friend operator" << std::endl;
    return a * n;
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    if (v.mode == Vector::RECT)
    {
        os << "(x,y) = (" << v.x << ", " << v.y << ")";
    }
    else if (v.mode == Vector::POL)
    {
        os << "(m,a) = (" << v.mag << ", " << v.ang * Rad_to_deg << ")";
    }
    else
    {
        os << "Vector object mode is invalid";
    }
    return os;
}

} // namespace VECTOR