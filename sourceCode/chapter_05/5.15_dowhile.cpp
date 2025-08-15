// dowhile.cpp -- exit-condition loop

#include <iostream>
int main ()
{
    int n;
    std::cout << "enter numbers in the range 1-10 to find ";
    std::cout << "my favorite number is " << std::endl;

    do
    {
        std::cin >> n;
    } while (n != 7);
     
     return 0;
}