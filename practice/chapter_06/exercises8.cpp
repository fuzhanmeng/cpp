// 8.
// 编写一个程序,打开一个文件,从文件中逐个字符读取直到到达文件末尾,报告该文件包含多少个字符.

#include <iostream>
#include <fstream>
#include <string> // 添加 string 头文件用于 getline

int main()
{
    std::cout << "Enter file name: ";
    std::string filename;
    std::getline(std::cin, filename); // 允许输入带路径的文件名

    std::ifstream inFile;
    inFile.open(filename);

    if (!inFile.is_open())
    {
        std::cout << "Failed to open file: " << filename << std::endl;
        return 1; // 返回非零表示错误
    }

    char ch;
    int count = 0;

    // 逐个字符读取
    while (inFile.get(ch))
    {
        count++;
    }

    // 先检查是否读取失败（非文件结束原因）
    if (inFile.fail() && !inFile.eof())
    {
        std::cout << "Error reading file" << std::endl;
    }
    else
    {
        std::cout << "Reached end of file" << std::endl;
    }

    std::cout << "Total characters: " << count << std::endl;

    inFile.close(); // 显式关闭文件

    return 0;
}