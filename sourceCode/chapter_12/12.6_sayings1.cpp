/**
 * @file 12.6_sayings1.cpp
 * @brief using expanded String class
 * @author fzm
 * @date 2025-11-24
 */

#include <iostream>

#include "12.4_string1.h"

const int ArSize = 10;
const int MaxLen = 81;

int main()
{
    String name;
    std::cout << "Hi, what's your name?" << std::endl;
    std::cin >> name;

    std::cout << name << ", please enter up to " << ArSize << " short sayings <empty line to quit>:" << std::endl;

    String sayings[ArSize]; // array of objects
    char temp[MaxLen];      // temporary string storage

    int i;
    for (i = 0; i < ArSize; i++)
    {
        std::cout << i + 1 << ": ";
        std::cin.get(temp, MaxLen);
        while (std::cin && std::cin.get() != '\n')
        {
            continue;
        }
        if (!std::cin || temp[0] == '\n')
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
        std::cout << "Here are your sayings:" << std::endl;
        for (int i = 0; i < total; i++)
        {
            std::cout << sayings[i][0] << ": " << sayings[i] << std::endl;
        }

        int shortest = 0;
        int first = 0;
        for (int i = 1; i < total; i++)
        {
            if (sayings[i].length() < sayings[shortest].length())
            {
                shortest = i;
            }
            if (sayings[i] < sayings[first])
            {
                first = i;
            }
        }

        std::cout << "shortest saying: " << std::endl;
        std::cout << sayings[shortest] << std::endl;
        std::cout << "first alphabetically" << std::endl;
        std::cout << sayings[first] << std::endl;
        std::cout << "this program used " << String::HowMany() << " String objects. Bye.\n";
    }
    std::cout << "No input! Bye.\n";
    return 0;
}