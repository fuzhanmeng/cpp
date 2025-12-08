/**
 * @file 13.6_usett1.cpp
 * @brief using base class and derived class
 * @author fzm
 * @date 2025-12-03
 */
#include <codecvt>
#include <iostream>
#include <ostream>
#include <string>

#include "13.4_tabtenn1.h"

int main()
{
    TableTennisPlayer player1("Trar", "Boomdea", false);
    RatedPlayer rplayer1(1140, "Mallory", "Duck", true);

    player1.Name();
    if (player1.HasTable())
        std::cout << "has a table" << std::endl;
    else 
        std::cout << "hasn't a table" << std::endl;
     
    rplayer1.Name();
    if (rplayer1.HasTable())
        std::cout << "has a table " << std::endl;
    else 
        std::cout << "hasn't a table " << std::endl;

    std::cout << "Name: ";
    rplayer1.Name();
    std::cout << "Rating: " << rplayer1.Rating() << std::endl;
    
    RatedPlayer Rplayer2(1212,player1);
    std::cout << "Name: ";
    Rplayer2.Name();
    std::cout << "Rating: " << Rplayer2.Rating() << std::endl;

    return 0;
}