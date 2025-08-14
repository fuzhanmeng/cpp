//  ifelseif.cpp -- using if else if else

const int Fave = 27;
#include <iostream>
int main()
{
    int n;
    std::cout << "Enter a number in the range 1-100 to find ";
    std::cout << "my favorite number: ";

    do
    {
        std::cin >> n;
        if (n < Fave)
        {
            std::cout << "too low -- guess again: ";
        }
        else if (n > Fave)
        {
            std::cout << "too high -- guess again: ";
        }
        else
        {
            std::cout << Fave << " is right!\n";
        }
    } while (Fave != n);
    return 0;
}