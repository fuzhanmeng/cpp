// strgback.cpp -- a function that returns a pointer tp char
#include <iostream>
char* buildStr(char ch, int times);

int main ()
{
    int times;
    char ch;

    std::cout << "Enter a character: ";
    std::cin >> ch;

    std::cout << "Enter an integer: ";
    std::cin >> times;

    char *ps = buildStr(ch, times);
    std::cout << ps << std::endl;
    delete [] ps;

    ps = buildStr('+', 20);
    std::cout << ps << "-DONE-" << ps << std::endl;
    delete []ps;

    return 0;
}

// builds string made of n c characters
char* buildStr(char ch, int times)
{
    char * pstr = new char [times + 1];
    pstr[times] = '\0';

    while (times-- > 0)
    {
        pstr[times] = ch;
    }

    return pstr;
}
