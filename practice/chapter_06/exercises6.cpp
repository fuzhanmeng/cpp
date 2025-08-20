// 6.
// 编写一个程序，记录捐助给 “维护合法权利团体” 的资金。该程序要求用户输入捐献者数目，然后要求用户输入每一个捐献者的姓名和款项。
// 这些信息被储存在一个动态分配的结构体数组中。每个结构体有两个成员：用来储存姓名的字符数组（或 string对象）和用来存储款项的 double成员。
// 读取所有的数据后，程序将显示所有捐款超过 10000 的捐款者的姓名及其捐款数额。

// 该列表前应包含一个标题，指出下面的捐款者是重要捐款人 Grand Patrons。然后，程序将列出其他的捐款者，该列表要以 Patrons 开头。
// 如果某种类别没有捐款者，则程序将打印单词 none。该程序只显示这两种类别，而不进行排序。
#include <iostream>
#include <vector>
#include <string>
#include <limits>

struct Donor
{
    std::string name;
    double tvarps;
};

int main()
{
    std::cout << "Enter the number of donors: ";
    int numbers = 0;
    std::cin >> numbers;

    // 清理掉回车符  丢掉输入缓冲区中所有内容，直到遇到一个换行符为止
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // 错误方式：创建了一个向量数组
    // std::vector<play> public_welfare[numbers];

    // 正确方式：创建一个包含numbers个元素的向量
    std::vector<Donor> donors(numbers);
    for (int i = 0; i < numbers; i++)
    {
        std::cout << "Name:  ";
        std::getline(std::cin, donors[i].name);

        std::cout << "the tvarps of donors: ";
        std::cin >> donors[i].tvarps;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "===== Grand Patrons =====" << std::endl;
    bool GrandPatrons = false;
    for (int i = 0; i < numbers; i++)
    {
        if (donors[i].tvarps > 10000)
        {
            std::cout << "Name: " << donors[i].name << " : " << donors[i].tvarps << " tvarps" << std::endl;
            GrandPatrons = true;
        }
    }
    if (!GrandPatrons)
    {
        std::cout << "none" << std::endl;
    }

    std::cout << "===== Patrons =====" << std::endl;
    bool Patrons = false;
    for (int i = 0; i < numbers; i++)
    {
        if (donors[i].tvarps < 10000)
        {
            std::cout << "Name: " << donors[i].name << " : " << donors[i].tvarps << " tvarps" << std::endl;
            Patrons = true;
        }
    }
    if (!Patrons)
    {
        std::cout << "none" << std::endl;
    }
}