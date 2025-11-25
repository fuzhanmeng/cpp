/**
 * @file 12.7_sayings2
 * @brief using pointers to objects
 * @author fzm
 * @date 2025-11-25
 */

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "12.4_string1.h"

const int ArSize = 10;
const int MaxLen = 81;

int main()
{
    String name;
    std::cout << "Hi, what's your name ?" << std::endl;
    std::cin >> name;
    std::cout << name << ", please enter up to " << ArSize << " short sayings <empty line to quit:\n";

    String sayings[ArSize];
    char temp[MaxLen];
    int i;
    for (i = 0; i < ArSize; i++)
    {
        std::cout << i + 1 << ": ";
        std::cin.get(temp, MaxLen);
        while (std::cin && std::cin.get() != '\n')
        {
            continue;
        }
        if (!std::cin || temp[0] == '\0')
        {
            break;
        }
        else
        {
            sayings[i] = temp;
        }
    }

    int total = i;
    if (total > 0)
    {
        std::cout << "Here are your sayings: \n";
        for (int i = 0; i < total; i++)
        {
            std::cout << sayings[i] << std::endl;
        }

        // use pointers to keep track of shortese, first strings
        String* shortest = &sayings[0];
        String* fisrt = &sayings[0];
        for (int i = 1; i < total; i++)
        {
            if (sayings[i].length() < shortest->length())
            {
                shortest = &sayings[i];
            }
            if (sayings[i] < *fisrt)
            {
                fisrt = &sayings[i];
            }
        }

        std::cout << "shortest saying: \n" << *shortest << std::endl;
        std::cout << "first alphabetically:\n" << *fisrt << std::endl;

        srand(time(0));
        int choice = rand() % total;

        // use new to create, initialize new String object
        String* favorite = new String(sayings[choice]);
        std::cout << "My favorite saying:\n" << *favorite << std::endl;
        delete favorite;
    }
    else
    {
        std::cout << "Not much to say, eh?\n";
    }
    std::cout << "bye.\n";
    return 0;
}