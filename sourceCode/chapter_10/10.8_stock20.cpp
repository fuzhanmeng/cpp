// stock20.cpp -- augmented version
#include <iomanip>
#include <iostream>

#include "10.7_stock20.h"

Stock::Stock()
{
    shares_ = 0;
    share_val_ = 0;
    total_val_ = 0;
}

Stock::Stock(const std::string& co, long n, double pr)
{
    company_ = co;
    if (n < 0)
    {
        std::cout << "Number of shares_ can't be negative; " << company_ << " shares_ set to 0.\n";
        shares_ = 0;
    }
    else
    {
        shares_ = n;
    }
    share_val_ = pr;
    set_tot();
}

// class destructor
Stock::~Stock() { std::cout << "run destrcutor" << std::endl; }

// other methods
void Stock::buy(long num, double price)
{
    if (num < 0)
    {
        std::cout << "Number of shares_ purchased can't be negative. " << "Transaction is aborted.\n";
    }
    else
    {
        shares_ += num;
        share_val_ = price;
        set_tot();
    }
}

void Stock::sell(long num, double price)
{
    if (num < 0)
    {
        std::cout << "Number of shares_ sold can't be negative. " << "Transaction is aborted.\n";
    }
    else if (num > shares_)
    {
        std::cout << "You can't sell more than you have! " << "Transaction is aborted.\n";
    }
    else
    {
        shares_ -= num;
        share_val_ = price;
        set_tot();
    }
}

void Stock::update(double price)
{
    share_val_ = price;
    set_tot();
}

void Stock::show() const
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Company: " << company_ << '\n'
              << "shares: " << shares_ << '\n'
              << "share price = $" << share_val_ << "\n"
              << "total price = $" << total_val_ << "\n";
}

const Stock& Stock::topval(const Stock& s) const
{
    if (s.total_val_ > total_val_)
    {
        return s;
    }
    else
    {
        return *this;
    }
}