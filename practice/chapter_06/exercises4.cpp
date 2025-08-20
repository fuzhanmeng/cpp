// 4.
// 加入 Benevolent Order of Programmers 后,在 BOP 大会上,人们可以通过加入者的真实姓名、头衔或秘密 BOP 姓名来了解他(她).
// 请编写一个程序,可以使用真实姓名、头衔、秘密姓名来显示 BOP 成员的列表情况.
// 每当该程序运行时,请使用下面的结构：
// Benevolent order of programmers strcture
// struct bop
// {
//     char fullname[strsize]; // real name
//     char title[strsize];    // job title
//     char bopname[strsize];  // secret BOP name
//     int preference;         // 0 = fullname, 1 = title, 2 = bopname
// };

// 该程序创建一个有上述结构体组成的小型数组，并将其初始化为适当的值.另外，该程序使用一个循环，
// 让用户在下面的选项中进行选择：

// a.display by name b.display by title
// c.display by bopname d.display by preference
// q.quit

// 注意, display by preference 并不意味着显示成员的偏好，而是意味着根据成员的偏好来列出成员。例如，如果偏好号为 1，则选择 d 将显示成员的头衔。该程序的运行情况如下：

// Benevolent order of Programmers report.

// a. display by name     b. display by title
// c. display by bopname  d. display by preference
// q. quit

// Enter your choices: a
// Wimp Macho
// Raki Rhodes
// Celia Laiter
// Hoppy Hipman
// Pat Hand

// Next choice： d
// Wimp Macho
// Junior Programmer
// MIPS
// Analyst Trainee
// LOOPY

// Next choice: q
// Bye!

#include <iostream>
#include <vector>
#include <string>

const int strsize = 30;
struct bop
{
    char fullname[strsize]; // real name
    char title[strsize];    // job title
    char bopname[strsize];  // secret BOP name
    int preference;         // 0 = fullname, 1 = title, 2 = bopname
};

int main()
{
    std::cout << "Benevolent Order of Programmers Report" << std::endl;
    std::cout << "a. display by name           b. display by title" << std::endl;
    std::cout << "c. display by bopname        d. display by preference" << std::endl;
    std::cout << "q. quit" << std::endl;

    std::vector<bop> bop = {
        {"Wimp Macho", "Wimp macho", "WM", 0},
        {"Raki Rhodes", "Junior Programmer", "hahaha", 1},
        {"Celia Laiter", "xiongda", "MIPS", 2},
        {"Hoppy Hipman", "Analyst Trainee", "HH", 1},
        {"Pat Hand", "xionger", "LOOPY", 2}};

    std::cout << "Enter your choice: ";
    char choice;
    std::cin >> choice;

    while (choice != 'q')
    {
        switch (choice)
        {
        case 'a':
            for (const auto &b : bop)
                std::cout << b.fullname << std::endl;
            break;
        case 'b':
            for (const auto &b : bop)
                std::cout << b.title << std::endl;
            break;
        case 'c':
            for (const auto &b : bop)
                std::cout << b.bopname << std::endl;
            break;
        case 'd':
            for (const auto &b : bop)
            {
                if (b.preference == 0)
                {
                    std::cout << b.fullname << std::endl;
                }
                else if (1 == b.preference)
                {
                    std::cout << b.title << std::endl;
                }
                else
                    std::cout << b.bopname << std::endl;
            }
            break;
        default:
            std::cout << "aaaa" << std::endl;
            break;
        }
        std::cout << "Next choice: ";
        std::cin >> choice;
    }
    std::cout << "Bye!" << std::endl;
}
