// 6.

// 结构 CandyBar 包含 3 个成员，如编程练习 5 所示。请编写一个程序，创建一个包含 3 个元素的 CandyBar 数组，并将它们初始化为所选的值，然后显示每个结构的内容。

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
    // CandyBar snack[3];
    // snack[0] = {"Mocha Munch", 2.3, 350};
    // snack[1] = {"defu", 44.1, 110};
    // snack[2] = {"feililuo", 2.21, 2220};
    CandyBar snack[3] = {{"Mocha Munch", 2.3, 350}, {"defu", 44.1, 110}, {"feililuo", 2.21, 2220}};

    std::cout << snack[0].variety << " " << snack[0].weigth << " " << snack[0].Calories << std::endl;
    std::cout << snack[1].variety << " " << snack[1].weigth << " " << snack[1].Calories << std::endl;
    std::cout << snack[2].variety << " " << snack[2].weigth << " " << snack[2].Calories << std::endl;

    CandyBar *pt = new CandyBar[3];
    pt->Calories = 22;
    pt->weigth = 3.22;
    pt->variety = "hao chi de ";

    std::cout << pt->variety << " " << pt->weigth << " " << pt->Calories << " " << std::endl;

    return 0;
}