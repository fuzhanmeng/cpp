// addpntrs.cpp -- pointer addition
#include <iostream>

int main()
{
    double wages[3] = {10000.0, 20000.0, 30000.0};
    short stacks[3] = {3, 2, 1};

    double *pw = wages;
    short *ps = &stacks[0];

    std::cout << "pw = " << pw << ", *pw = " << *pw << std::endl;
    std::cout << "&wages = " << &wages << std::endl;
    pw = pw + 1;
    std::cout << "add 1 to the pw pointer" << std::endl;
    std::cout << "pw = " << pw << ", *pw = " << *pw << std::endl;

    std::cout << "ps = " << ps << ", *ps = " << *ps << std::endl;
    std::cout << "&stacks = " << &stacks << std::endl;
    ps = ps + 1;
    std::cout << "add 1 to the ps pointer" << std::endl;
    std::cout << "ps = " << ps << ", *ps = " << *ps << std::endl;

    std::cout << "access two elements with array notation " << std::endl;
    std::cout << "stack[0] = " << stacks[0] << ", stacks[1] = " << stacks[1] << std::endl;
    std::cout << "access two elements with pointer notation " << std::endl;

    //  数组名可以像指针一样使用​​数组名会隐式转换为指向首元素的short*指针
    std::cout << "*stacks = " << *stacks << ", *(stacks + 1) = " << *(stacks + 1 )<< std::endl;

    std::cout << sizeof(wages) << " = size of wages array " << std::endl;
    std::cout << sizeof(pw) << " = size of pw pointer " << std::endl;

    return 0;    
}