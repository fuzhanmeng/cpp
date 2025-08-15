//  cinfish.cpp -- non-numeric input terminates loop

#include <iostream>
const int Max = 5;

int main ()
{
    //get data
    double fish[Max];
    std::cout << "please enter the weights of your fish.\n";
    std::cout << "you may enter up to " << Max << " fish <q to terminate>.\n";
    std::cout << "fish #1: ";
    int i = 0;
    //  std::cin >> fish[i]返回的是 std::cin对象本身 
    // cin double true // cin int or char or ... flase 
    while (i < Max && std::cin >> fish[i])
    {
        if (++i < Max)
            std::cout << "fish # " << i + 1 << ": ";
    }
    
    //  calculate average
    double total = 0.0;
    for (int j = 0; j < i; j++)
    {
        total += fish[j];
    }

    //report results
    if (0 == i)
        std::cout << "No fish\n";
    else
        std::cout << total / i << " = average weight of " << i << " fish\n";

    std::cout << "Done.\n";
    
    return 0;
}