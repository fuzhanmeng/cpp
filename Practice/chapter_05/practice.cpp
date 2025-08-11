#include <iostream>

int main ()
{
    int a[7];
    a[0] = 1;
    for (int i = 0; i < 7; i++)
    {
        a[i + 1] = 2 * a[i];
        std::cout << a[i] << std::endl;
    }
    return 0;
}