//  num_test.cpp -- use numeric test in for loop

#include <iostream>

int main ()
{
    int limit;
    std::cout << "Enter a limit code " << std::endl;
    std::cin >> limit;
    int i;

    for (i = limit; i ; i--)     // quits when i is 0
    {
        std::cout << "i =" << i << std::endl;
    }

    std::cout << "Done now that i = " << i << std::endl;
    return 0;
}