// 10.
// 编写一个程序，要求用户输入3次40码跑的成绩(也可以输入40米跑的成绩)，并显示次数和平均成绩
// 请使用一个array对象来存书数据(如果编译器不支持array类，请使用数组)

#include <iostream>
#include <array>
#include <string>

int main()
{
    std::array<float, 3> grade;

    std::cout << "Please Enter grade[0]: ";
    std::cin >> grade[0];

    std::cout << "Please Enter grade[0]: ";
    std::cin >> grade[1];

    std::cout << "Please Enter grade[0]: ";
    std::cin >> grade[2];

    std::cout << " 3 times the results are : " << grade[0] << " " << grade[1] << " " << grade[2] << std::endl;

    float avg = (grade[0] + grade[1] + grade[2]) / 3;
    std::cout << "Average Grade is : " << avg << std::endl;

    return 0;
}