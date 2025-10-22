// stock10.h -- Stock class declaration with constructors, destructor added

#ifndef STOCK1_H_
#define STOCK1_H_

#include <string>
class Stock
{
public:
    Stock(); // default constructor
    Stock(const std::string& co, long n = 0, double pr = 0.0);
    ~Stock();

    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show();

private:
    std::string company_;
    long shares_;
    double share_val_;
    double total_val_;
    void set_tot() { total_val_ = shares_ * share_val_; }
};

#endif