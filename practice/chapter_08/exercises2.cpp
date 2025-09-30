// 2.
// CandyBar结构包含3个成员:第一个成员存储candy bar的品牌名称；第二个成员存储candy
// bar的重量（可能有小数）；第三个成员存储candy bar的热量（整数）
// 请编写一个程序，它使用一个这样的函数，即将CandyBar的引用、char指针、double和int作为参数，并用最后3个值设置相应的结构成员。最后3个参数的默认值分别为“Millennium
// Munch”、2.85和350。另外，该程序还包含一个以CandyBar的引用为参数，并显示结构内容的函数。请尽可能使用const

#include <cstring>
#include <iostream>

struct CandBar
{
    char name[20];
    double weight;
    int calories;
};

void set_struct(CandBar& cb, const char* name = "Millennium Munch", double weight = 2.85, int calories = 350);
void show_struct(CandBar& cb);

int main()
{
    CandBar cb;
    set_struct(cb); // 使用默认值
    show_struct(cb);

    std::cout << "-----" << std::endl;

    set_struct(cb, "Snickers", 1.75, 250); // 使用自定义值
    show_struct(cb);

    return 0;
}
// void set_struct(CandBar& cb, const char* name = "Millennium Munch", double weight = 2.85, int calories = 350)
// {
//     std::strncpy(cb.name, name,sizeof(cb.name) - 1);
//     cb.weight = weight;
//     cb.calories = calories;
// }

// 定义：不要再写默认值
void set_struct(CandBar& cb, const char* name, double weight, int calories)
{
    std::strncpy(cb.name, name, sizeof(cb.name) - 1);
    cb.name[sizeof(cb.name) - 1] = '\0'; // 防止字符串未终止
    cb.weight = weight;
    cb.calories = calories;
}

void show_struct(CandBar& candBar)
{
    std::cout << "the CandBar = " << std::endl;
    std::cout << "CandBar name = " << candBar.name << std::endl;
    std::cout << "CandBar weigth = " << candBar.weight << std::endl;
    std::cout << "CandBar calories = " << candBar.calories << std::endl;
}