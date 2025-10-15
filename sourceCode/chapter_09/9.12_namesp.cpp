// namesp.cpp -- use namespaces

#include <iostream>
#include "9.11_namesp.h"

namespace pers 
{
    void getPerson(Person & rp)
    {
        std::cout << "enter first name: ";
        std::cin >> rp.fname;
        std::cout << "enter last name: ";
        std::cin >> rp.lname;
    }

    void showPerson(const Person & rp)
    {
        std::cout << rp.fname << ", " << rp.lname << "  ";
    }
}

namespace debts 
{
    void getDebt(Debt & rd)
    {
        getPerson(rd.name);
        std::cout << "enter debts: ";
        std::cin >> rd.amount;
    }

    void showDebt(const Debt & rd)
    {
        showPerson(rd.name);
        std::cout << ": $" << rd.amount << std::endl;
    }

    double sumDebts(const Debt *ar, int n)
    {
        double total = 0;
        for (int i = 0; i < n; i++) 
        {
            total += ar[i].amount;
        }

        return total;
    }

}

