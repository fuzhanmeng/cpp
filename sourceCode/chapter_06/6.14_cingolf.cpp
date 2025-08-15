//  cingolf.cpp -- non-numeric input skipped

#include <iostream>
const int Max = 5;

int main()
{
    // get data
    int glof[Max];
    std::cout << "please enter your golf scores.\n";
    std::cout << "you must enter " << Max << " rounds .\n";

    int i;
    for (int i = 0; i < Max; i++)
    {
        std::cout << "round #" << i + 1 << ": ";
        while (!(std::cin >> glof[i]))
        {
            std::cin.clear();
            while ('\n' != std::cin.get())
            {
                continue;
            }
            std::cout << "please enter a number: ";
        }
    }

    //  calculate average
    double total = 0.0;
    for (int i = 0; i < Max; i++)
    {
        total += glof[i];
    }

    // report results
    std::cout << total / Max << " = average score " << Max << " rounds\n";

    return 0;
}