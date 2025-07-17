// 2.

// 修改程序清单 4.4，使⽤ C++ string 类⽽不是 char 数组。
// #include <iostream>
// int main()
// {
//     using namespace std;
//     const int ArSize = 20;
//     char name[ArSize];
//     char dessert[ArSize];

//     cout << "Enter your name:\n";
//     cin.getline(name, ArSize);  // reads through newline
//     cout << "Enter your favorite dessert:\n";
//     cin.getline(dessert, ArSize);
//     cout << "I have some delicious " << dessert;
//     cout << " for you, " << name << ".\n";
//     // cin.get();
//     return 0;
// }

#include <iostream>

int main()
{
    std::string name;
    std::string dessert;

    const int ArSize = 20;

    std::cout << "Enter your name:\n";
    std::getline(std::cin, name);

    std::cout << "Enter your favorite dessert:\n";
    std::getline(std::cin, dessert);
    std::cout << "I have some delicious " << dessert;
    std::cout << " for you, " << name << ".\n";

    return 0;
}