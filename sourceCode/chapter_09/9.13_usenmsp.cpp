// usenamesapce.cpp -- using namesapce
#include <iostream>
#include "9.11_namesp.h"

void other(void);
void another(void);

int main()
{
    using debts::Debt;
    using debts::showDebt;

    Debt golf = {{"Benny", "Goatsniff"}, 120.0};
    showDebt(golf);
    other();
    another();

    return 0;
}

void other(void)
{
    std::cout << "enter other" << std::endl;
    using namespace debts;
    Person dg = {"Doodles", "Glister"};
    showPerson(dg);
    std::cout << std::endl;
    Debt zippy[3];
    
    for (int i = 0; i < 3; i++) 
    {
        getDebt(zippy[i]);
    }

    for (int i = 0; i < 3; i++) 
    {
        showDebt(zippy[i]);
    }

    std::cout << "Total debt: $" << sumDebts(zippy, 3) << std::endl;

    return;
}

void another(void)
{
    std::cout << "enter another" << std::endl;
    using pers::Person;

    Person collector = {"Milo", "Rightshift"};
    pers::showPerson(collector);
    std::cout << std::endl;
}