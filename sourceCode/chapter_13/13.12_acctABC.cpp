/**
 * @file 13.12_acctABC.cpp
 * @brief Bank account class methods implementation (Modern C++ & Google Style)
 * @author fzm
 * @date 2025-12-15
 */

#include <iostream>

#include "13.11_acctabc.h" // 假设你的头文件名为此

// =========================================================
// AcctABC (Abstract Base Class) Methods
// =========================================================

// 使用成员初始化列表 (Member Initializer List) - 高效且标准
AcctABC::AcctABC(const std::string& name, long account_num, double balance)
    : full_name_(name), account_num_(account_num), balance_(balance) {}

// Deposit 不需要是虚函数，且可以直接操作 protected 成员
void AcctABC::Deposit(double amount) {
    if (amount < 0) {
        std::cout << "Negative deposit not allowed; deposit is cancelled.\n";
    } else {
        balance_ += amount;
    }
}

// 这是一个纯虚函数的默认实现 (Default implementation for pure virtual)
// 派生类显式调用 AcctABC::Withdraw(...) 时会用到这里
void AcctABC::Withdraw(double amount) { balance_ -= amount; }

// Protected methods for formatting
AcctABC::Formatting AcctABC::SetFormat() const {
    // Set up ###.## format
    Formatting f;
    f.flag_ = std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    f.precision_ = std::cout.precision(2);
    return f;
}

void AcctABC::Restore(Formatting& f) const {
    std::cout.setf(f.flag_, std::ios_base::floatfield);
    std::cout.precision(f.precision_);
}

// =========================================================
// Brass Methods
// =========================================================

void Brass::Withdraw(double amount) {
    if (amount < 0) {
        std::cout << "Withdrawal amount must be positive; withdrawal canceled.\n";
    } else if (amount <= GetBalance()) {
        // 调用基类的实现
        AcctABC::Withdraw(amount);
    } else {
        std::cout << "Withdrawal amount of $" << amount << " exceeds your balance.\n"
                  << "Withdrawal canceled.\n";
    }
}

void Brass::ViewAcct() const {
    Formatting f = SetFormat();
    // 使用访问器或直接访问 protected 成员均可，这里为了语义清晰使用了访问器
    std::cout << "Client: " << FullName() << "\n";
    std::cout << "Account Number: " << AcctNum() << "\n";
    std::cout << "GetBalance: $" << GetBalance() << "\n";
    Restore(f);
}

// =========================================================
// BrassPlus Methods
// =========================================================

// 构造函数：参数名全称化，使用初始化列表
BrassPlus::BrassPlus(const std::string& name, long account_num, double balance, double max_loan, double rate)
    : AcctABC(name, account_num, balance), max_loan_(max_loan), rate_(rate), owes_bank_(0.0) {}

// 复制构造风格的构造函数
BrassPlus::BrassPlus(const Brass& ba, double max_loan, double rate)
    : AcctABC(ba), // 使用基类的拷贝构造（编译器自动生成或隐式调用）
      max_loan_(max_loan),
      rate_(rate),
      owes_bank_(0.0) {}

void BrassPlus::ViewAcct() const {
    Formatting f = SetFormat();

    std::cout << "BrassPlus Client: " << FullName() << "\n";
    std::cout << "Account Number: " << AcctNum() << "\n";
    std::cout << "GetBalance: $" << GetBalance() << "\n";
    std::cout << "Maximum loan: $" << max_loan_ << "\n";
    std::cout << "Owed to bank: $" << owes_bank_ << "\n";

    // 临时修改精度显示利率
    std::cout.precision(3);
    std::cout << "Loan Rate: " << 100 * rate_ << "%\n";

    Restore(f);
}

void BrassPlus::Withdraw(double amount) {
    Formatting f = SetFormat();

    double bal = GetBalance();

    if (amount <= bal) {
        AcctABC::Withdraw(amount);
    } else if (amount <= bal + max_loan_ - owes_bank_) {
        double advance = amount - bal;
        owes_bank_ += advance * (1.0 + rate_);

        std::cout << "Bank advance: $" << advance << "\n";
        std::cout << "Finance charge: $" << advance * rate_ << "\n";

        Deposit(advance); // 存入透支款
        AcctABC::Withdraw(amount); // 再全部取出
    } else {
        std::cout << "Credit limit exceeded. Transaction cancelled.\n";
    }

    Restore(f);
}