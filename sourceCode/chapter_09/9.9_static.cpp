// static.cpp -- using a static local variable

#include <iostream>
const int ArSize = 10;

// function prototype
void strcount(const char* str);

int main()
{
    char input[ArSize];
    char next;

    std::cout << "enter a line: \n";
    std::cin.get(input, ArSize);
    while (std::cin)
    {
        std::cin.get(next);
        while (next != '\n')
        {
            std::cin.get(next);
        }
        strcount(input);
        std::cout << "enter next line(empty line to quit):\n";
        std::cin.get(input, ArSize);
    }
    std::cout << "Bye\n";
}

void strcount(const char* str)
{
    static int total = 0;
    int count = 0;
    std::cout << "\"" << str << "\" contains";
    while (*str++)
    {
        count++;
    }
    total += count;

    std::cout << "count = " << count << " characters\n";
    std::cout << "total = " << total << " characters\n";
}