/**
 * @file exercises3
 * @brief practice
 * @author fzm
 * @date 2025-11-28
 */

#include "exercises3.h"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <ostream>

Stock::Stock()
{
    company_ = new char[1];
    company_[0] = '\0';
    shares_ = 0;
    share_val_ = 0;
    total_val_ = 0;
}

Stock::Stock(const char* com, long n, double pr)
{
    len = std::strlen(com);
    company_ = new char[len + 1];
    std::strcpy(company_, com);

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

Stock::Stock(const Stock& s)
{
    len = s.len;
    company_ = new char[len + 1];
    std::strcpy(company_, s.company_);
}

Stock& Stock::operator=(const Stock& s)
{
    if (this == &s)
    {
        return *this;
    }

    delete[] company_;
    len = s.len;
    company_ = new char[len + 1];
    std::strcpy(company_, s.company_);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Stock& s)
{
    os << "Company: " << s.company_ << "  Shares: " << s.shares_ << "  Share Price: " << s.share_val_
       << "  Total Worth: $" << s.total_val_;
    return os;
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