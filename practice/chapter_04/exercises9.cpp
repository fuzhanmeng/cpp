// 9.
// 修改编程练习 6，但使用 new 来动态分配数组，而不是声明一个包含 3 个元素的 CandyBar 数组

#include <iostream>
#include <string>

struct CandyBar
{
    std::string variety;
    float weigth;
    int Calories;
};

int main()
{
    CandyBar *pt = new CandyBar;      // ✅ 分配一个 CandyBar 对象
    CandyBar *ptr = new CandyBar[10]; // ✅ 分配一个包含 10 个 CandyBar 的数组

    pt->variety = "apple";
    pt->weigth = 22.3;
    pt->Calories = 1552;

    ptr[2].variety = "hahaha";
    ptr[2].weigth = 2323;
    ptr[2].Calories = 5746;

    std::cout << pt->variety << " " << pt->weigth << " " << pt->Calories << std::endl;
    std::cout << ptr[2].variety << " " << ptr[2].weigth << " " << ptr[2].Calories << std::endl;

    delete pt;
    delete[] ptr;
    return 0;
}