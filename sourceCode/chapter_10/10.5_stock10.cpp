// stock10.cpp -- Stock class implementation with constructors, destructor added

#include "10.4_stock10.h"

#include <iostream>
#include <iomanip>


// constructors (verbose version)
// default constructor
Stock::Stock()
{
    std::cout << "use default constructor called.\n";
    company_ = "no name";
    shares_ = 0;
    share_val_ = 0.0;
    total_val_ = 0.0;
}

Stock::Stock(const std::string& co, long n, double pr)
{
    std::cout << "constructor using " << co << " called.\n";
    company_ = co;

    if (n < 0)
    {
        std::cout << "Number of shares can't be negative;" << company_ << " shares set to 0.\n";
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
Stock::~Stock()
{
    std::cout << "Bye, " << company_ << std::endl;
}

// other functions
void Stock::buy(long num, double price)
{
    if (num < 0) 
    {
        std::cout << "Number of shares sold can't be negative; Transaction is aborted.\n";
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
    if (num < 0 ) 
    {
        std::cout << "Number of shares sold can't be negative; Transaction is aborted.\n";
    }
    else if (num > shares_) 
    {
        std::cout << "You can't sell more than you have! Transaction is aborted.\n";
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

void Stock::show()
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Company: " << company_ << '\n'
              << "shares: " << shares_ << '\n'
              << "share price = $" << share_val_ << "\n"
              << "total price = $" << total_val_ << "\n";
}
