// protos.cpp -- using prototypes and function calls
#include <iostream>

void cheers(int x);
double cube(double x);

int main()
{
    cheers(5);

    std::cout << "give me a number: ";
    double side;
    std::cin >> side;

    double volume = cube(side);
    std::cout << "A " << side << "-foot cube has a volume of ";
    std::cout << volume << " cubic feet" << std::endl;

    cheers(cube(2));

    return 0;
}

void cheers(int x)
{
    for (int i = 0; i < x; i++)
    {
        std::cout << "cheers" << i << std::endl;
    }
}

double cube(double x)
{
    return x * x * x;
}
