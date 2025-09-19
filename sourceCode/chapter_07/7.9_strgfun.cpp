// strgfun.cpp -- functions with a string atgument

#include <iostream>
unsigned int c_in_str(const char *str, char ch);

int main()
{
    char mmm[15] = "minimum"; // string in an array
    std::cout << "sizeof mmm = " << sizeof mmm << std::endl;

    const char *wail = "ululate"; // wail points to string
    std::cout << "sizeof *wail = " << sizeof(*wail) << std::endl;

    unsigned int ms = c_in_str(mmm, 'm');
    unsigned int us = c_in_str(wail, 'u');

    std::cout << "the m's number = " << ms << " in " << mmm << std::endl;
    std::cout << "thr u's number = " << us << " in " << wail << std::endl;

    return 0;
}

unsigned int c_in_str(const char *str, char ch)
{
    unsigned int count = 0;

    while (*str)
    {
        if (ch == *str)
        {
            count++;
        }
        str++;
    }

    return count;
}
