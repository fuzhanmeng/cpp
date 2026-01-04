/**
 * @file 13.8_brass.cpp
 * @brief bank account class methods
 * @author fzm
 * @date 2025-12-08
 */
#include <ios>
#include <iostream>

#include "13.7_brass.h"

// formatting stuff
typedef std::ios_base::fmtflags format;
typedef std::streamsize precis;
format setFormat();
void restore(format f, precis p);

Brass::Brass(const std::string& s, long an, double bal) {
    fullName_ = s;
    acctNum_ = an;
    balance_ = bal;
}

Brass::~Brass() {}

double Brass::Banlance() const { return balance_; }

void Brass::Deposit(double amt) {
    if (amt < 0) {
        std::cout << "Negative deposit not allowed; deposit is cancelled" << std::endl;
    } else {
        balance_ += amt;
    }
}

void Brass::ViewAcct() const {
    // set up format
    format initialState = setFormat();
    precis prec = std::cout.precision(2);
    std::cout << "Client: " << fullName_ << std::endl;
    std::cout << "Account Number: " << acctNum_ << std::endl;
    std::cout << "Balance: $" << balance_ << std::endl;
    restore(initialState, prec);
}

void Brass::Withdraw(double amt) {
    format initialState = setFormat();
    precis prec = std::cout.precision(2);

    if (amt < 0) {
        std::cout << "Withdrawal amount must be positive; withdraw canceled" << std::endl;
    } else if (amt <= balance_) {
        balance_ -= amt;
    } else {
        std::cout << "Withdrawal amount of $" << amt << " exceeds your balance" << std::endl;
        std::cout << "Withdrawal canceled" << std::endl;
    }
    restore(initialState, prec);
}

BrassPlus::BrassPlus(const std::string& s, long an, double bal, double ml, double r) : Brass(s, an, bal) {
    maxLoan_ = ml;
    rate_ = r;
    owesBank_ = 0.0;
}

BrassPlus::BrassPlus(const Brass& ba, double ml, double r) : maxLoan_(ml), rate_(r) { owesBank_ = 0.0; }

BrassPlus::~BrassPlus() {}

void BrassPlus::Withdraw(double amt) {
    format initialState = setFormat();
    precis prec = std::cout.precision(2);

    double bal = Banlance();

    if (amt < bal) {
        Brass::Withdraw(amt);
    } else if (amt <= bal + maxLoan_ - owesBank_) {
        double advance = amt - bal;
        owesBank_ += advance * (1 + rate_);
        std::cout << "Bank advance: $" << advance << std::endl;
        std::cout << "Finance charge: $" << advance * rate_ << std::endl;
        Deposit(advance);
        Brass::Withdraw(amt);
    } else {
        std::cout << "Credit limit exceeded Transcantion cannceled" << std::endl;
    }
}

void BrassPlus::ViewAcct() const {
    format initialState = setFormat();
    precis prec = std::cout.precision(2);

    Brass::ViewAcct();
    std::cout << "Maximum loan: $" << maxLoan_ << std::endl;
    std::cout << "Owed t0 bank: $" << owesBank_ << std::endl;
    std::cout.precision(3);
    std::cout << "Loan Rate: " << 100 * rate_ << "%\n";
    restore(initialState, prec);
}

format setFormat() {
    // set up ###.## format
    return std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
}

void restore(format f, precis p) {
    std::cout.setf(f, std::ios_base::floatfield);
    std::cout.precision(p);
}
