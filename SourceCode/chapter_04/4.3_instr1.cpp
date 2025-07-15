#include <iostream>

int main ()
{
    const int ArSize = 20;
    char name[ArSize];
    char desert[ArSize];

    std::cout << "Enter your name: " << std::endl;
    std::cin >> name;
    std::cout << " Enter your favorite dessert: " << std::endl;
    std::cin >> desert;

    std::cout << "I have some delicious " << desert;
    std::cout << " for you, " << name << std::endl;

    return 0;
}