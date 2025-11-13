/**
 * @file 11.21_stone1
 * @brief user-defined conversion functions
 * @author fzm
 * @date 2025-11-13
 */
#include <iostream>
#include "11.19_stonewt1.h"

int main()
{
    
    Stonewt poppins(9,2.8);     // 9 stone, 2.8 pounds
    double p_wt = poppins;      // implicit conversion
    std::cout << "Convert to double => ";
    std::cout << "Poppins: " << p_wt << " pounds.\n";
    std::cout << "Convert to int => ";
    std::cout << "Poppins: " << int (poppins) << " pounds.\n";
	// std::cin.get();
    return 0; 
}
