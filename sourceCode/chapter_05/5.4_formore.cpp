// formore.cpp --- more looping with for

#include <iostream>
const int ArSize = 16;

int main ()
{
    long long factorials[ArSize];

    factorials[0] = factorials[1] = 1LL;

    for (size_t i = 2; i < ArSize; i++)
    {
        factorials[i] = i * factorials[i -1];
    }

    for (size_t i = 0; i < ArSize; i++)
    {
        std::cout << i << "!" << factorials[i] << std::endl;
    }
    
    return 0;
}