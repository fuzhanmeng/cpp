/**
 * @file 13.11_acctabc.h
 * @brief Bank account classes (Google Style & Modern C++)
 * @author fzm
 * @date 2025-12-13
 */

#ifndef ACCTABC_H
#define ACCTABC_H

#include <ios>
#include <string>

class AcctABC {
public:
    // modern c++ use static constexper define constants to replace magic number
    static constexpr const char* kDefaultName = "Nullbody";
    static constexpr long kDefaultAcctNum = -1;
    static constexpr double kDefaultBalance = 0.0;

    explicit AcctABC(const std::string& name = kDefaultName, long account_num_ = kDefaultAcctNum,
                     double balance_ = kDefaultBalance);

    // modern virtual destructor use default
    virtual ~AcctABC() = default;

    void Deposit(double amount);

    double GetBalance() const { return balance_; }

    virtual void Withdraw(double amount) = 0;
    virtual void ViewAcct() const = 0;

protected:
    struct Formatting {
        std::ios_base::fmtflags flag_; // 添加下划线
        std::streamsize precision_; // 添加下划线
    };
    const std::string& FullName() const { return full_name_; }
    long AcctNum() const { return account_num_; }

    Formatting SetFormat() const;
    void Restore(Formatting& f) const;

private:
    // 数据成员：snake_case_
    std::string full_name_;
    long account_num_;
    double balance_;
};

// 派生类 Brass
class Brass : public AcctABC {
public:
    explicit Brass(const std::string& name = AcctABC::kDefaultName, long account_num = AcctABC::kDefaultAcctNum,
                   double balance = AcctABC::kDefaultBalance)
        : AcctABC(name, account_num, balance) {}

    // 【Modern C++】显式继承构造函数 (C++11)，如果不需要额外逻辑，
    // 也可以考虑 use 'using AcctABC::AcctABC;' 但为了明确默认参数，手写通常更安全。

    // 【Modern C++】禁止拷贝（派生类通常也会自动删除，但显式写出更好）
    Brass(const Brass&) = delete;
    Brass& operator=(const Brass&) = delete;

    // 【Modern C++】使用 override，去掉 virtual
    void Withdraw(double amount) override;
    void ViewAcct() const override;
};

// 派生类 BrassPlus
class BrassPlus : public AcctABC {
public:
    static constexpr double kDefaultMaxLoan = 500.0;
    static constexpr double kDefaultRate = 0.10;

    explicit BrassPlus(const std::string& name = AcctABC::kDefaultName, long account_num = AcctABC::kDefaultAcctNum,
                       double balance = AcctABC::kDefaultBalance, double max_loan = kDefaultMaxLoan,
                       double rate = kDefaultRate);

    explicit BrassPlus(const Brass& ba, double balance = AcctABC::kDefaultBalance, double max_loan = kDefaultMaxLoan);

    // 禁止拷贝
    BrassPlus(const BrassPlus&) = delete;
    BrassPlus& operator=(const BrassPlus&) = delete;

    void Withdraw(double amount) override;
    void ViewAcct() const override;

    void ResetMax(double max) { max_loan_ = max; }
    void ResetRate(double rate) { rate_ = rate; }
    void ResetOwes() { owes_bank_ = 0; }

private:
    double max_loan_;
    double rate_;
    double owes_bank_;
};

#endif // ACCTABC_H_