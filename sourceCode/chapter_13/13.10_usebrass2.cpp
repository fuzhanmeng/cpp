/**
 * @file 13.10_usebrass2.cpp
 * @brief polymorphic example
 * @author fzm
 * @date 2025-12-08
 */

#include "13.7_brass.h"
#include <iostream>
#include <string>
const int CLIENTS = 4;
int main()
{
    Brass* p_client[CLIENTS];
    std::string temp;
    long tempnum;
    double tempbal;
    char kind;

    for (int i = 0; i < CLIENTS; i++)
    {
        std::cout << "Enter client's name: ";
        std::getline(std::cin, temp);
        std::cout << "Enter client's account number: ";
        std::cin >> tempnum;
        std::cout << "Enter opening balance: $";
        std::cin >> tempbal;

        std::cout << "Enter 1 for Brass Account or 2 for BrassPlus Account: ";
        while (std::cin >> kind && (kind != '1' && kind != '2')) 
        {
            std::cout << "Enter either 1 or 2: ";
        }
        if ('1' == kind)
        {
            p_client[i] = new Brass(temp, tempnum, tempbal);
        }
        else 
        {
            double tmax, trate;
            std::cout << "Enter the overdraft limit: $";
            std::cin >> tmax;
            std::cout << "Enter the interest rate  as a decimal fraction: ";
            std::cin >> trate;

            p_client[i] = new BrassPlus(temp, tempnum, tempbal,tmax, trate);
        }
        while (std::cin.get() != '\n' ) 
        {
            continue;
        }
    }

    std::cout << "------------------------------" << std::endl;
    for (int i = 0; i < CLIENTS; i++)
    {
        p_client[i]->ViewAcct();
        std::cout << std::endl;
    }

    for (int i = 0; i < CLIENTS; i++)
    {
        delete [] p_client[i];
    }

    return 0;
}