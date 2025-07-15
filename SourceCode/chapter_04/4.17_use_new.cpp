// use_new.cpp -- using the new operator

#include <iostream>

int main ()
{
    int nights = 1001;
    int* pt = new int;  //  在堆上分配​​足够存储一个 int的内存空间 pt指向这个int
    *pt = 1001;

    std::cout << "nights value  = " << nights << std::endl;
    std::cout << "nights location = " << &nights << std::endl;

    std::cout << "int value = " << *pt << std::endl;
    std::cout << "int location = " << pt << std::endl;

    double* pd = new double;
    *pd = 1000000.1;

    std::cout << "double value = " << *pd << std::endl;
    std::cout << "double location = " << pd << std::endl;
   
    std::cout << "location of pointer pd : " << &pd << std::endl;

    std::cout << "size of pt = " << sizeof(pt) << std::endl;
    std::cout << "size of *pt =" << sizeof(*pt) << std::endl;
    std::cout << "size of pd = " << sizeof(pd) << std::endl;
    std::cout << "size of *pd = " << sizeof(*pd) << std::endl;

    return 0;
}