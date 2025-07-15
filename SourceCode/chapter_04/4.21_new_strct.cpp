// newstrct.cpp -- using new with a structure
#include <iostream>

struct inflatable
{
    char name[20];
    float volume;
    double price;
};

int main()
{
    // std::cout << &inflatable << std::endl;   inflatable是一个类型（struct的名称），而不是一个具体的变量 无法取值

    inflatable* pt = new inflatable;    //  pt指向一块足够存储 inflatable结构体的内存
    std::cout << "Enter name of inflatable item: ";
    std::cin.get(pt->name, 20);
    std::cout << "Enter volum in cubic feet: ";

    std::cin >> (*pt).volume; // 在读取数值前会自动跳过空白符（包括换行符），因此 ​​不会影响数值输入的正确性​​。
    std::cout << "Enter price: $";
    std::cin >> pt->price;

    //  *pt 是结构体实例  pt是指向这个结构体的指针
    std::cout << "Name: " << (*pt).name << std::endl;
    std::cout << "Volume: " << pt->volume << "cubic feet" << std::endl;
    std::cout << "Price: $" << pt->price << std::endl;

    delete pt;

    return 0;
}
