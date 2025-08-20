// 3.
// 编写一个菜单驱动的程序.该程序显示一个提供 4 个选项的菜单---每个选项用一个字母标记.
// 如果用户使用有效选项之外的字母进行输入,程序将提示用户输入一个有效的字母,直到用户这样做为止.
// 然后,该程序使用一条 switch 语句,根据用户的选择执行一个简单操作.该程序的运行情况如下：
// Please enter one of the following choices:

// c) carnivore    p) pianist
// t) tree         g) game
// f

// Please enter a c, p, t, or g: q
// A maple is a tree.

#include <iostream>

int main()
{
    std::cout << "Please enter one of the following choices:" << std::endl;
    std::cout << "c) carnivore p) pianist" << std::endl;
    std::cout << "t) tree g) game" << std::endl;
    std::cout << "f\n";

    char ch;
    std::cin.get(ch);
    while ('q' != ch)
    {
        switch (ch)
        {
        case 'c':
            std::cout << "c) carnivore" << std::endl;
            break;
        case 'p':
            std::cout << "p) pianist" << std::endl;
            break;
        case 't':
            std::cout << "A maple is a  tree" << std::endl;
            break;
        case 'g':
            std::cout << "g) game" << std::endl;
            break;
        default:
            std::cout << "Please enter a c, p, t, or g: q" << std::endl;
            break;
        }
        std::cin.get(ch);
    }

    return 0;
}