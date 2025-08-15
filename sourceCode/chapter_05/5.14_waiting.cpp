// waiting.cpp -- using clock() in a time-delay loop
#include <iostream>
#include <ctime>  // 包含clock()函数和clock_t类型

//  clock() 程序消耗的 CPU 时间​​
int main()
{
    std::cout << "enter the delay time, in seconds: ";
    float secs;
    std::cin >> secs;  // 从用户获取等待秒数
    
    // 将秒数转换为时钟周期数
    clock_t delay = secs * CLOCKS_PER_SEC;  
    
    std::cout << "starting " << std::endl;
    clock_t start = clock();  // 记录开始时间点
    
    // 空循环等待，直到经过指定时间
    while (clock() - start < delay)
    {
        // 空循环体，纯粹消耗CPU时间
    }
    
    std::cout << "done " << std::endl;
    return 0;
}