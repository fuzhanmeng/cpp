// lefrover.cpp -- overloading the left() function

#include <iostream>

unsigned long left(unsigned long num, unsigned ct);
char* left(const char* str, int n = 1);

int main()
{
    const char* trip = "Hawaill!!"; //  test value
    unsigned long n = 12345678;     //  tets value

    int i;
    char* temp;

    for (i = 0; i < 10; i++)
    {
        std::cout << left(n, i) << std::endl;
        temp = left(trip, i);
        std::cout << "temp = " << temp << std::endl;
        delete[] temp;
    }
    return 0;
}

// this function returns the first ct digits of the number num
unsigned long left(unsigned long num, unsigned ct)
{
    unsigned digits = 1;
    unsigned long n = num;

    if (0 == ct && 0 == num)
    {
        return 0;
    }

    while (n /= 10)
    {
        digits++;
    }
    std::cout << "digits = " << digits << std::endl;

    if (digits > ct)
    {
        ct = digits - ct;
        while (ct--)
        {
            num /= 10;
        }
        return num;
    }
    else
    {
        return num;
    }
}

// this function returns a pointer to a new string, consisting of the first n characters in the str string

char* left(const char* str, int n)
{
    if (n < 0)
    {
        n = 0;
    }
    char* p = new char[n + 1];
    int i;
    for (i = 0; i < n && str[i]; i++)
    {
        p[i] = str[i];
    }
    while (i <= n)
    {
        p[i++] = '\0';
    }
    return p;
}