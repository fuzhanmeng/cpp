// twoarg.cpp -- a function with 2 arguments

#include <iostream>
void n_char(char a, int b);
int main()
{
    int times;
    char ch;

    std::cout << "Enter a character: " << std::endl;
    std::cin >> ch;

    while ('q' != ch)
    {
        std::cout << "Enter an integer: ";
        std::cin >> times;
        n_char(ch, times); // function with two arguments
        std::cout << "\nEnter another character or press the q-key to quit" << std::endl;
        std::cin >> ch;
    }
    std::cout << "The value of times is " << times << std::endl;
    std::cout << "Bye" << std::endl;

    return 0;
}

void n_char(char a, int b)
{
    while (b-- > 0)
    {
        std::cout << a;
    }
}
