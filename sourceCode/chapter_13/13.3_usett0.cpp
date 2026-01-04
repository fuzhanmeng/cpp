/**
 * @file 13.3_usett0.cpp
 * @brief using a base class
 * @author fzm
 * @date 2025-12-02
 */
#include <iostream>

#include "13.1_tabtenn0.h"

int main() {
    TableTennisPlayer player1("Chuck", "Blizzard", true);
    TableTennisPlayer player2("Tara", "Boomdea", false);
    player1.Name();
    if (player1.HasTable()) {
        std::cout << "has a table" << std::endl;
    } else {
        std::cout << "hasn't a table " << std::endl;
    }

    player2.Name();
    if (player2.HasTable()) {
        std::cout << "has a table" << std::endl;
    } else {
        std::cout << "hasn't a table " << std::endl;
    }

    return 0;
}