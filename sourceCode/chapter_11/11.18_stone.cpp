/**
 * @file 11.18_stone
 * @brief Description of the file
 * @author fzm
 * @date 2025-11-13
 */

#include <iostream>

#include "11.16_stonewt.h"

void display(const Stonewt& st, int n);

int main()
{
    Stonewt incognito = 275; // use constructor to initialize
    Stonewt wolfe(285.7);
    Stonewt taft(21, 8);

    std::cout << "-------------------------" << std::endl;

    std::cout << "the celebrity weighed ";
    incognito.show_stn();

    std::cout << "the detective weighed ";
    wolfe.show_stn();

    std::cout << "the president weighed ";
    taft.show_lbs();

    std::cout << "-------------------------" << std::endl;
    incognito = 276.8;
    taft = 325;

    std::cout << "After dinner, the celebrity weighed ";
    incognito.show_stn();

    std::cout << "After dinner, the President weighed ";
    taft.show_lbs();

    std::cout << "-------------------------" << std::endl;

    display(taft, 2);
    std::cout << "The wrestler weighed even more.\n";
    display(422, 2);
    std::cout << "No stone left unearned\n";

    return 0;
}

void display(const Stonewt& st, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << "Wow! ";
        st.show_stn();
    }
}
