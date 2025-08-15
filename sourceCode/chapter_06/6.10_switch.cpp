//  switch.cpp -- using the switch statement

#include <iostream>

void showmenu();
void report();
void comfort();
int main()
{
    showmenu();
    int choice;
    std::cin >> choice;
    while (5 != choice)
    {
        switch (choice)
        {
        case 1:
            std::cout << "\a\n";
            break;
        case 2:
            report();
            break;
        case 3:
            std::cout << "the boss was in all day. \n";
            break;
        case 4:
            comfort();
            break;
        default:
            std::cout << "that's not a choice.\n";
            break;
        }
        showmenu();
        std::cin >> choice;
    }
    return 0;
}

void showmenu()
{
    std::cout << "please enter 1, 2, 3, 4, or 5:\n"
                 "1) alarm         2) report\n"
                 "3) alibi         4) comfort\n"
                 "5) quit\n";                 
}

void report()
{
    std::cout << "It's been an excellent week for  business.\n"
                 "Sa;es are up 120%,. Exoenses are down 35%.\n";
}

void comfort()
{
    std::cout << "Your employees think you are the dinesr CEO\n"
                 "in the industry. the board of directors think.\n"
                 "you are the first CEO in the industry.\n";
}