/**
 * @file 11.12_usetime3.cpp
 * @brief using the fourth draft of the Time class
 * @author fzm
 * @date 2025-11-13
 */

#include <iostream>

#include "11.10_mytime3.h"

int main()
{
    Time aida(3, 35);
    Time tosca(2, 48);
    Time temp;

    std::cout << "Aida and tosca:\n";
    std::cout << aida << "; " << tosca << std::endl;
    temp = aida + tosca;
    std::cout << "Aida + Tosca: " << temp << std::endl;

    temp = aida * 1.17;
    std::cout << "Aida * 1.17 :" << temp << std::endl;
    std::cout << "10.0 * Tosca: " << 10.0 * tosca << std::endl;

    return 0;
}
