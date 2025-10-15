// external.cpp -- external varibale
// compile with support.cpp

#include <iostream>

double warming = 0.3;
int a;
// function prototypes
void update(double);
void local();

int main()
{
    std::cout << "global warming is " << warming << " , degrees.\n";
    update(0.1);
    std::cout << "global warming is " << warming << " , degrees.\n";
    local();
    std::cout << "global warming is " << warming << " , degrees.\n";
}