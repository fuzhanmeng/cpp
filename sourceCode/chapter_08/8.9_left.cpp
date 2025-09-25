// left.cpp -- string function with a default argument 
#include <iostream>

const int ArSize = 80;
char* left(const char* str, int n = 1);
int main()
{
    char sample[ArSize];
    std::cout << "enter a string: \n";
    std::cin.get(sample, ArSize);
    char* ps = left(sample, 4);
    std::cout << ps << std::endl;
    delete[] ps;

    ps = left(sample);
    std::cout << ps << std::endl;
    delete[] ps;

    return 0;
}

// this function returns a pointer to a new string
// consisting of the first n characters int the str string
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