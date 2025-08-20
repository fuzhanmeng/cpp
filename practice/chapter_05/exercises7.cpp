// 7. 设计一个名为car的结构，用它存储下述有关汽车的信息：
//    生产商（存储在字符数组或string对象中的字符串
//    生产年份（整数）
//    编写程序，询问用户有多少辆车。随后使用new创建相应数量的car结构体数组。接下来，提示用户输入每辆车的生产者（可能是多个词组成）和生产年份。注意，这将需要调用`cin.get()`，因为它将交替读取数组值和字符串（见第4章）。最后，程序将显示结构内容。
//    程序运行示例：
//
//    How many cars do you wish to catalog? 2
//    Car #1:
//    Please enter the make: Hudson Hornet
//    Please enter the year made: 1952
//    Car #2:
//    Please enter the make: Kaiser
//    Please enter the year made: 1951
//    Here is your collection:
//    1952 Hudson Hornet
//    1951 Kaiser
//

#include <iostream>
#include <cstring>
#include <limits>

struct car_Info
{
    int year;
    std::string make;
};

int main()
{
    int num;
    std::cout << "How many cars do you wish to catalog? ";
    // std::cin.get() >> num; // 错误用法
    std::cin >> num;
    // 清楚换行符
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Car #1:" << std::endl;

    car_Info *ptr = new car_Info[num];

    for (int i = 0; i < num; i++)
    {
        std::cout << "Please enter the make: ";
        std::getline(std::cin, ptr[i].make);

        std::cout << "Please enter the year made: ";
        // std::cin.get() >> ptr[i].year; // 错误用法
        std::cin >> ptr[i].year;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除换行符
    }

    // 输出结果
    for (int i = 0; i < num; i++)
    {
        std::cout << ptr[i].year << " " << ptr[i].make << std::endl;
    }

    delete[] ptr;
    return 0;
}