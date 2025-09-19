// 7.3
// 下面是一个结构体的声明:
// struct box {
//     char maker[40];
//     float height;
//     float width;
//     float length;
//     float volume;
// }
// a. 编写一个函数，按值传递 box 结构体，并显示每个成员的值。 b.
// 编写一个函数，传递 box 结构体的地址，并将 volume
// 成员设置为其他三维长度的乘积。 c. 编写一个使用这两个函数的简单程序。

#include <iostream>

struct box
{
    char maker[40];
    float height;
    float width;
    float length;
    float volume;
};

void show_box(box b);
void set_Volume(box &b);

int main()
{
    box b = {"myBox", 3.0f, 5.0f, 12.0f, 234.0f};
    show_box(b);
    set_Volume(b);
}

void show_box(box b)
{
    std::cout << "height = " << b.height << "width = " << b.width << "  length = " << b.length
              << "  volume = " << b.volume << std::endl;
}

void set_Volume(box &b)
{
    b.volume = b.height * b.length * b.width;
    std::cout << "the volume = " << b.volume << std::endl;
}