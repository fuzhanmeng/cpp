/**
 * @file exercises3.h
 * @brief practice
 * @author fzm
 * @date 2025-11-28
 */

#ifndef STOCK20_H_
#define STOCK20_H_
#include <ostream>
class Stock
{
public:
    Stock();
    Stock(const char* com, long n, double pr);
    Stock(const Stock& s);
    Stock& operator=(const Stock& s);
    // Stock& operator<<(std::ostream os,const Stock& s);
    ~Stock();

    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show() const;

    const Stock& topval(const Stock& s) const;

    friend std::ostream& operator<<(std::ostream& os, const Stock& s);

private:
    int len;
    char* company_;
    int shares_;
    double share_val_;
    double total_val_;
    void set_tot() { total_val_ = shares_ * share_val_; }
};

#endif