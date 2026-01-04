/**
 * @file 13.7_brass.h
 * @brief bank account class
 * @author fzm
 * @date 2025-12-08
 */
#ifndef BRASS_H
#define BRASS_H

#include <string>

class Brass {
public:
    Brass(const std::string& fn = "Nullbody", long an = -1, double bal = 0.0);
    ~Brass();

    void Deposit(double amt);
    double Banlance() const;

    virtual void Withdraw(double amt);
    virtual void ViewAcct() const;

private:
    std::string fullName_;
    long acctNum_;
    double balance_;
};

class BrassPlus : public Brass {
public:
    BrassPlus(const std::string& fn = "Nullbody", long an = -1, double bal = 0.0, double ml = 500, double r = 0.11125);
    BrassPlus(const Brass& ba, double ml = 500, double r = 0.11125);
    ~BrassPlus();

    void ResetMax(double m) { maxLoan_ = m; }
    void ResetRate(double r) { rate_ = r; }
    void ResetOwes() { owesBank_ = 0; }

    virtual void Withdraw(double amt);
    virtual void ViewAcct() const;

private:
    double maxLoan_;
    double rate_;
    double owesBank_;
};

#endif // BRASS_H