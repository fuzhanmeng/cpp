// topfive.cpp -- handling an array of string objects

#include <iostream>
#include <string>
const int SIZE = 5;
void display(const std::string list[], int size);

int main()
{
    std::string list[SIZE];
    std::cout << "Enter your " << SIZE << " favorites astronomical sights:" << std::endl;

    for (int i = 0; i < SIZE; i++)
    {
        std::cout << i + 1 << " : ";
        std::getline(std::cin, list[i]);
    }

    std::cout << "Your list: " << std::endl;
    display(list, SIZE);
    return 0;
}

void display(const std::string list[], int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << i + 1 << " : " << list[i] << std::endl;
    }
}
