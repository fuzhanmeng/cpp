// while.cpp -- introducing the while loop

#include <iostream> 

const int ArSize = 20;

int main ()
{
    char name[ArSize];
    std::cout << "your first name , please: ";
    std::cin >> name;

    int i = 0;
    while (name[i] != 0)
    {
        std::cout << name[i] << ": " << int(name[i]) << std::endl;
        i++;
    }

    return 0;
    
}