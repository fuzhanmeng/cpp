// 8.
// 完成编程练习 7，但使用 new 来为结构分配内存，而不是声明一个结构变量。另外，让程序在请求用户输入披萨公司名称之前输入披萨的直径

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

    Pizza *p = new Pizza;
    // p->diameter = 11;

    std::cout << "Please Enter Pizza's diameter: ";
    std::cin >> p->diameter;

    std::cin.get();

    std::cout << "Please Enter Pizza's company name: ";
    std::getline(std::cin, p->Company_name);

    std::cout << "Please Enter Pizza's weigth: ";
    std::cin >> p->weigth;
    std::cout << p->Company_name << " " << p->diameter << " " << p->weigth << " " << std::endl;

    //
    delete p;
    return 0;
}