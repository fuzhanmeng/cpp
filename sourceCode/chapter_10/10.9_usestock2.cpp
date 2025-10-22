// usestock2.cpp -- using the Stock class
// compile with stock20.cpp

#include <iostream>

#include "10.7_stock20.h"

const int STKS = 4;
int main()
{
    // create an array of initialized objects
    Stock stocks[STKS] = 
    {
        Stock("NanoSmart", 12, 20.0),
        Stock("Boffo Objects", 200, 2.0),
        Stock("Monolithic", 130, 3.25),
        Stock("Fleep Enterprises", 60, 6.5),
    };

    std::cout << "Stock holdings:\n";
    int st;
    for (int st = 0; st < STKS; st++)
    {
        stocks[st].show();
    }

    // set pointer to first element
    const Stock* top = &stocks[0];

    for (st = 1; st < STKS; st++)
    {
        // topval return a object
        top = &top->topval(stocks[st]);
    }

    std::cout << "\nMost valuable holding:\n";
    top->show();

    return 0;
}