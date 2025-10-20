// stock00.cpp -- implementing the Stock class
// version00

#include "10.1_stock00.h"

#include <iostream>
#include <ostream>

void Stock::acquire(const std::string& co, long n, double pr)
{
    company = co;
    if (n < 0)
    {
        std::cout << "Number of shares can't be negative;" << company << "share set to 0.\n";
        shares = 0;
    }
    else
    {
        shares = n;
    }

    share_val = pr;
    set_tot();
}

void Stock::buy(long num, double price)
{
    if (num < 0)
    {
        std::cout << "Number of shares purchased can't be negative, Transaction is aborted.\n";
    }
    else
    {
        shares += num;
        share_val = price;
        set_tot();
    }
}

void Stock::sell(long num, double price)
{
    if (num < 0)
    {
        std::cout << "Number of shares sold can't be negative, Transaction is aborted.\n";
    }
    else if (num > shares)
    {
        std::cout << "You can't sell more than you have! Transcation is aborted.\n";
    }
    else
    {
        shares -= num;
        share_val = price;
        set_tot();
    }
}

void Stock::update(double price)
{
    share_val = price;
    set_tot();
}

#include <iostream>
#include <iomanip>

void Stock::show()
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Company: " << company << '\n'
              << "shares: " << shares << '\n'
              << "share price = $" << share_val << "\n"
              << "total price = $" << total_val << "\n";
}
