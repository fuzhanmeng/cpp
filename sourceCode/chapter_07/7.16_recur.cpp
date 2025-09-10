// recur.cpp -- using recuesion

#include <iostream>

void countdown(int n);

int main ()
{
    // call the recursive function
    countdown(4);
    return 0;
}

void countdown(int n)
{
    std::cout << "counting down ... " << n << std::endl;
    if (0 < n)
    {
        countdown(n -1);
    }
    std::cout << n << ": Kaboom!" << std::endl;
}
