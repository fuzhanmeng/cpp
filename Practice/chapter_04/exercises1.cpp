//  1.

//  编写一个 C++ 程序，如下述输显示 示例所示并显示信息：

//  What is your first name? Betty Sue
//  What is your last name? Yewe
//  What letter grade do you deserve? B
//  What is your age? 22
//  Name: Yewe, Betty Sue
//  Grade: C
//  Age: 22

//    注意，该程序应接受的名字包含多个单词。另外，程序将向下调整成绩，即向上调一个字母。假设用户请求 A、B 或 C，所以不必担心 D 和 F 之间的空档。

#include <iostream>

int main()
{
    std::string first_name;
    char last_name[20];
    char grade;
    int age;

    std::cout << " What is your first name?";
    std::getline(std::cin, first_name);

    std::cout << " What is your last name?";
    std::cin.getline(last_name, 20);

    std::cout << " What letter grade do you deserve?";
    std::cin >> grade;

    std::cout << " What is your age?";
    std::cin >> age;

    std::cout << " Name: " << last_name << " , " << first_name << std::endl;

    std::cout << " Grade: " << char(grade + 1) << std::endl;

    std::cout << " Age: " << age << std::endl;

    return 0;
}