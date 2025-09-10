// arrobj.cpp -- functions with array objects

#include <iostream>
#include <array>
#include <string>

const int Seasons = 4;
const std::array<std::string, Seasons> Snames = {"Spring", "Summer", "Fall", "Winter"};
void fill(std::array<double,Seasons> * pa);
void show(std::array<double,Seasons> pa);

int main ()
{
    std::array<double, 4> expenses;

    fill(&expenses);
    show(expenses);

    return 0;
}


void fill(std::array<double,Seasons> * pa)
{
    for (int i = 0; i < Seasons; i++)
    {
        std::cout << "Enter " << Snames[i] << " expenses: ";
        std::cin >> (*pa)[i];
    }
}

void show(std::array<double,Seasons> pa)
{
    double total = 0;
    std::cout << "\nEXPENSEX";

    for (int i = 0; i < Seasons; i++)
    {
        std::cout << Snames[i] << " : $" << pa[i] << std::endl;
        total += pa[i];
    }
    std::cout << "the total = " << total << std::endl;

}
