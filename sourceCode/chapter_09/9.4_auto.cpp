// auto.cpp -- illustrating scope of  
#include <iostream>

void oil(int x);
int a;  // default a = 0 

int main()
{
    int texas = 31;
    int year = 2011;
    std::cout << "in main, teaxs = " << texas << " , &teaxs = " << &texas << std::endl;
    std::cout << "in main, year = " << year << " , &year = " << &year << std::endl;

    oil(texas);
    std::cout << "in main, after oil, teasx = " << texas << " , &teaxs = " << &texas << std::endl;
    std::cout << "in main, after oil, year = " << year << " , &year = " << &year << std::endl;

    std::cout << "a = " << a << std::endl;

    return 0;
}

void oil(int x)
{
    int teaxs = 5;

    std::cout << "int oil, teaxs = " << teaxs << " , &teaxs = " << &teaxs << std::endl;
    std::cout << "int oil, x = " << x << " , &x = " << &x << std::endl;

    {
        int teaxs = 113;
        std::cout << "in block, teaxs = " << teaxs << " , &teaxs = " << &teaxs << std::endl;
        std::cout << "in block, x = " << x << " , &x = " << &x << std::endl;
    }

    std::cout << "post-block teaxs = " << teaxs << " , &teaxs = " << &teaxs << std::endl;
}