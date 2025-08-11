// 10. 编写一个使用嵌套循环的程序，要求用户输入一个值，输出星号图案。
//     第一行包括一个星号，第二行两个星号，以此类推。每一行前面加句点，字符数等于行数。示例输出：
//     Enter number of rows: 5
//     .*
//     ..**
//     ...***
//     ....****
//     .....*****

#include <iostream>
int main()
{
    int rows = 0;
    std::cout << "Enter number of rows: ";
    std::cin >> rows;

    for (int i = 1; i <= rows; i++) // 行号从1开始
    {
        // 输出句点：每行i个句点
        for (int j = 1; j <= i; j++)
        {
            std::cout << ".";
        }

        // 输出星号：每行i个星号
        for (int k = 1; k <= i; k++)
        {
            std::cout << "*";
        }

        // 每行结束后换行
        std::cout << std::endl;
    }

    return 0;
}