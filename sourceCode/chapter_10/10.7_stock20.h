// stock20.h -- augmented version
#ifndef STOCK20_H_
#define STOCK20_H_

#include <string>
class Stock
{
public:
    Stock();
    Stock(const std::string& co, long n, double pr);
    ~Stock();

    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show() const;

    const Stock& topval(const Stock& s) const;

private:
    std::string company_;
    int shares_;
    double share_val_;
    double total_val_;
    void set_tot() { total_val_ = shares_ * share_val_; }
};

#endif