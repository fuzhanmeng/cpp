// 7.

// William Wingate 从事比萨饼分析服务。对于每个披萨，他都需要记录以下信息：
// 披萨公司的名称，可以有多个单词组成。
// 披萨的直径。
// 披萨的重量。
// 请设计一个能存储这些信息的结构，并编写一个使用这种结构变量的程序。程序将请求用户输入上述信息，然后显示这些信息。请使用 cin（或它的方法）和 cout。

#include <iostream>
#include <string>

struct Pizza
{
    std::string Company_name;
    double diameter;
    float weigth;
};

int main()
{
    std::cout << "William Wingate" << " Pizza Analysis Services " << std::endl;
    Pizza p;
    p.Company_name = "apple";
    p.diameter = 11.0;
    p.weigth = 4.8;

    std::cout << p.Company_name << " " << p.diameter << " " << p.weigth << " " << std::endl;

    std::cout << "Please Enter Pizza's company name: ";
    std::getline(std::cin, p.Company_name);
    // std::cin.get(p.diameter);
    // std::cin.getline(p.weigth);
    std::cout << "Please Enter Pizza's diameter: ";
    std::cin >> p.diameter;

    std::cout << "Please Enter Pizza's weigth: ";
    std::cin >> p.weigth;

    std::cout << p.Company_name << " " << p.diameter << " " << p.weigth << " " << std::endl;

    return 0;
}