//  enum.cpp -- using enum

//  当枚举定义中没有显式指定值时，编译器会自动从 0 开始分配整数值
enum
{
    red,
    orange,
    yellow,
    green,
    blue,
    violet,
    indigo
};
#include <iostream>

int main()
{
    std::cout << "enter cloor code (0-6)";
    int code;
    std::cin >> code;

    while (code >= red && code <= indigo)
    {
        switch (code)
        {
        case red:
            std::cout << "Her lips were red.\n";
            break;
        case orange:
            std::cout << "Her hair was orange.\n";
            break;
        case yellow:
            std::cout << "Her shoes were yellow.\n";
            break;
        case green:
            std::cout << "Her nails were green.\n";
            break;
        case blue:
            std::cout << "Her sweatsuit was blue.\n";
            break;
        case violet:
            std::cout << "Her eyes were violet.\n";
            break;
        case indigo:
            std::cout << "Her mood was indigo.\n";
            break;
        default:
            std::cout << "the cout is default.\n";
            break;
        }

        std::cout << "Enter color code (0 - 6): ";
        std::cin >> code;
    }

    std::cout << "Byn\n";
    return 0;
}
