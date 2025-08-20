// 9.
// 完成练习 6,
// 但此次从文件中读取所需信息.文件的第一项是捐赠者人数,接下来是每位捐赠者的姓名和捐款额.
// 假设文件内容如下：

// 4
// Sam Stone
// 1000
// Freida Flass
// 10500
// Tammy Tubbs
// 5000
// Rich Raptor
// 55000

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>

struct Donor
{
    std::string name;
    double tvarps;
};

int main()
{
    std::cout << "Enter the number of donors: " << std::endl;

    std::ifstream inFile;

    inFile.open("text.txt");
    if (!inFile.is_open())
    {
        std::cout << "open the file failed" << std::endl;
    }

    int numbers;
    inFile >> numbers;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<Donor> donors(numbers);

    for (int i = 0; i < numbers; i++)
    {
        std::getline(inFile, donors[i].name);

        // std::getline()只能用于读取字符串，不能直接读取 double类型
        // std::getline(inFile, donors[i].tvarps);
        inFile >> donors[i].tvarps;

        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "===== Grand Patrons =====" << std::endl;
    bool isGrand;
    for (int i = 0; i < numbers; i++)
    {
        if (donors[i].tvarps > 10000)
        {
            std::cout << "Name:  " << donors[i].name << " : " << donors[i].tvarps << " tvarps" << std::endl;
            isGrand = true;
        }
    }
    if (!isGrand)
    {
        std::cout << "None" << std::endl;
    }

    std::cout << "===== Patrons =====" << std::endl;

    bool isPatrons;
    for (int i = 0; i < numbers; i++)
    {
        if (donors[i].tvarps < 10000)
        {
            std::cout << "Name:  " << donors[i].name << " : " << donors[i].tvarps << " tvarps" << std::endl;
            isPatrons = true;
        }
    }
    if (!isPatrons)
    {
        std::cout << "None" << std::endl;
    }

    return 0;
}