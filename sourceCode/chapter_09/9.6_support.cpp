// support.cpp -- use external variable
// compile with external.cpp

#include <iostream>

extern double warming;

// function prototypes
void update(double);
void local();

void update(double dt)
{
    extern double warming;
    warming += dt;
    std::cout << "updating global warming to " << warming << " degrees.\n";
}

void local()
{
    double warming = 0.8;
    std::cout << "local warming = " << warming << " degrees.\n";
    std::cout << "but global warming = " << ::warming << " degrees.\n";
}