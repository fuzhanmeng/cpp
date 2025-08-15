// block.cpp -- use a block statement
// 重点在作用域  for循环如果不加{} 只会执行for后紧跟的第一条语句 
#include <iostream>
int main ()
{
    std::cout << "the Amazing Account will sum and average ";
    std::cout << " five numbers for you " << std::endl;
    std::cout << "please enter five values: " << std::endl;

    double number;
    double sum = 0.0;

    for (int i = 0; i < 5; i++)
    {
        std::cout << "Value: " << i << " : ";
        std::cin >> number;
        sum += number;
    }
    
    std::cout << "five exquisite choices indeed! ";
    std::cout << "the sum to " << sum << std::endl;
    std::cout << "and average to " << sum / 5 << std::endl;
    std::cout << "the Amazing Account bids you adieu! " << std::endl;

    return 0;
}