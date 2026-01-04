/**
 * @file 13.13_usebrass3
 * @brief polymorphic example
 * @author fzm
 * @date 2025-12-16
 */
#include <iostream>
#include <string>

#include "13.11_acctabc.h"
const int CLIENTS = 4;

int main() {
    AcctABC *p_clients[CLIENTS];
    std::string temp;
    long tempnum;
    double tempbal;
    char kind;

    for (int i = 0; i < CLIENTS; i++) {
        std::cout << "Enter client's name: ";
        getline(std::cin, temp);
        std::cout << "Enter client's account number: ";
        std::cin >> tempnum;
        std::cout << "Enter opening balance: $";
        std::cin >> tempbal;
        std::cout << "Enter 1 for Brass Account or " << "2 for BrassPlus Account: ";
        while (std::cin >> kind && (kind != '1' && kind != '2'))
            std::cout << "Enter either 1 or 2: ";
        if (kind == '1')
            p_clients[i] = new Brass(temp, tempnum, tempbal);
        else {
            double tmax, trate;
            std::cout << "Enter the overdraft limit: $";
            std::cin >> tmax;
            std::cout << "Enter the interest rate " << "as a decimal fraction: ";
            std::cin >> trate;
            p_clients[i] = new BrassPlus(temp, tempnum, tempbal, tmax, trate);
        }
        while (std::cin.get() != '\n')
            continue;
    }
    std::cout << std::endl;
    for (int i = 0; i < CLIENTS; i++) {
        p_clients[i]->ViewAcct();
        std::cout << std::endl;
    }

    for (int i = 0; i < CLIENTS; i++) {
        delete p_clients[i]; // free memory
    }
    std::cout << "Done.\n";
    // std::cin.get();
    return 0;
}
