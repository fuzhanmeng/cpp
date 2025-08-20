// 5.

// 结构 CandyBar 包含 3 个成员。第一个成员存储糖块的品牌，第二个成员存储糖块的重量（可以有小数），第三个成员存储糖块的卡路里含量（整数）。请编写一个程序，
// 声明这个结构，创建一个名为 snack 的 CandyBar 变量，并将其成员分别初始化为 “Mocha Munch”、2.3 和 350。初始化应在声明 snack 时进行。最后，程序显示 snack 变量的内容。

#include <iostream>
#include <string>

struct CandyBar
{
    std::string brand;
    float weigth;
    int calorice;
};

int main()
{
    CandyBar snack = {"Mocha Munch", 2.3, 350};
    std::cout << snack.brand << " " << snack.weigth << " " << snack.calorice << std::endl;

    return 0;
}