/**
 * @file 13.11_acctabc.h
 * @brief bank account classes
 * @author fzm
 * @date 2025-12-13
 */
#ifndef AcctABC_H
#define AcctABC_H
#include <ios>
#include <iostream>
#include <string>

class AcctABC
{
public:
    AcctABC(const std::string& s = "Nullbody", long acc = -1, double bal = 0);

    void Deposit(double amt);
    double Balance() const { return balance_; }

    virtual void Withdraw(double amt) = 0;
    virtual void ViewAcct() const = 0;

    virtual ~AcctABC();

protected:
    struct Formatting
    {
        std::ios_base::fmtflags flag;
        std::streamsize pr;
    };

    const std::string& FullName() const { return fullName_; }
    long AcctNum() const { return acctNum_; }
    Formatting SetFormat() const;
    void Restore(Formatting& f) const;

private:
    std::string fullName_;
    long acctNum_;
    double balance_;
};

class Brass : public AcctABC
{
public:
    Brass(const std::string& str = "Nullbody", long an = -1, double bal = 0) : AcctABC(str, an, bal) {}

    virtual void Withdraw(double amt);
    virtual void ViewAcct() const;

private:
};

class BrassPlus : public AcctABC
{
public:
    BrassPlus(const std::string& s, long an = -1, double bal = 0.0, double ml = 500, double r = 0.10);
    BrassPlus(const Brass& ba, double bal = 0.0, double ml = 500);

    virtual void Withdraw(double amt);
    virtual void ViewAcct() const;
    void ResetMax(double m) { maxLon_ = m; }
    void ResetRate(double r) { rate_ = r; }
    void ResetOwes() { owesBank_ = 0; }

private:
    double maxLon_;
    double rate_;
    double owesBank_;
};
#endif // AcctABC_H