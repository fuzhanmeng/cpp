/**
 * @file 13.12_acctABC.cpp
 * @brief bank account class methods
 * @author fzm
 * @date 2025-12-15
 */
#include <iostream>

#include "13.11_acctabc.h"

// Abstract Base class
AcctABC::AcctABC(const std::string& s, long an, double bal)
{
    fullName_ = s;
    acctNum_ = an;
    balance_ = bal;
}

AcctABC::~AcctABC() {}

void AcctABC::Deposit(double amt)
{
    if (amt < 0)
    {
        std::cout << "Negative deposit not allowed; deposit is cancelled.\n" << std::endl;
    }
    else
    {
        balance_ += amt;
    }
}

void AcctABC::ViewAcct() const
{
    std::cout << "the fullName is " << fullName_ << ", the acctNum is " << acctNum_ << ", the balance is " << balance_
              << std::endl;
}

void AcctABC::Withdraw(double amt)
{
    if (amt > balance_)
    {
        std::cout << "error, the amt should < balance" << std::endl;
    }
    else
    {
        balance_ -= amt;
    }
}

// protected methods for formatting
AcctABC::Formatting AcctABC::SetFormat() const
{
    // set up ###.## format
    Formatting f;
    f.flag = std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    f.pr = std::cout.precision(2);
    return f;
}

void AcctABC::Restore(Formatting& f) const
{
    std::cout.setf(f.flag, std::ios_base::floatfield);
    std::cout.precision(f.pr);
}

// Brass methods
void Brass::Withdraw(double amt)
{
    if (amt < 0)
        std::cout << "Withdrawal amount must be positive; " << "withdrawal canceled.\n";
    else if (amt <= Balance())
        AcctABC::Withdraw(amt);
    else
        std::cout << "Withdrawal amount of $" << amt << " exceeds your balance.\n"
                  << "Withdrawal canceled.\n";
}

void Brass::ViewAcct() const
{
    Formatting f = SetFormat();
    std::cout << "the fullName is " << FullName() << std::endl;
    std::cout << "Account Number: " << AcctNum() << std::endl;
    std::cout << "Balance: $" << Balance() << std::endl;
}

BrassPlus::BrassPlus(const std::string& s, long an, double bal, double ml, double r) : AcctABC(s, an, bal)
{
    maxLon_ = ml;
    rate_ = r;
    owesBank_ = 0.0;
}

BrassPlus::BrassPlus(const Brass& ba, double ml, double r) : AcctABC(ba)
{
    maxLon_ = ml;
    rate_ = r;
    owesBank_ = 0.0;
}

void BrassPlus::ViewAcct() const
{
    Formatting f = SetFormat();

    std::cout << "Brassplus Client: " << FullName() << std::endl;
    std::cout << "Account Number: " << AcctNum() << std::endl;
    std::cout << "Balance: $" << Balance() << std::endl;
    std::cout << "Maximum loan: $" << maxLon_ << std::endl;
    std::cout << "Owed to bank: $" << owesBank_ << std::endl;
    std::cout.precision(3);
    std::cout << "Loan Rate: " << 100 * rate_ << std::endl;
    Restore(f);
}

void BrassPlus::Withdraw(double amt)
{
    Formatting f = SetFormat();

    double bal = Balance();
    if (amt <= bal)
        AcctABC::Withdraw(amt);
    else if (amt <= bal + maxLon_ - owesBank_)
    {
        double advance = amt - bal;
        owesBank_ += advance * (1.0 + rate_);
        std::cout << "Bank advance: $" << advance << std::endl;
        std::cout << "Finance charge: $" << advance * rate_ << std::endl;
        Deposit(advance);
        AcctABC::Withdraw(amt);
    }
    else
        std::cout << "Credit limit exceeded. Transaction cancelled.\n";
    Restore(f);
}
