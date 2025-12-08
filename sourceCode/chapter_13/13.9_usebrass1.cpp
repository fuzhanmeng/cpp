// /**
//  * @file 13.9_usebrass1.cpp
//  * @brief usebrass1.cpp testing bank account classes
//  * @author fzm
//  * @date 2025-12-08
//  */
// #include <iostream>

// #include "13.7_brass.h"

// int main()
// {
//     Brass Piggy("Porcelot Pigg", 381299, 4000);
//     BrassPlus Hoogy("Horatio Hogg", 382288, 3000);
//     Piggy.ViewAcct();
//     std::cout << std::endl;

//     Hoogy.ViewAcct();
//     std::cout << std::endl;

//     std::cout << "Depositing $1000 into the Hogg Account:\n";
//     Hoogy.Deposit(1000.00);
//     std::cout << "New balance: $" << Hoogy.Banlance() << std::endl;

//     std::cout << "Withdrawing $4200 from the pigg Account:\n";
//     Piggy.Withdraw(4200);
//     std::cout << "Pigg account balance: $" << Piggy.Banlance() << std::endl;

//     std::cout << "Withdrawing $4200 from the Hogg Account:\n";
//     Hoogy.Withdraw(4200.00);
//     Hoogy.ViewAcct();

//     return 0;
// }