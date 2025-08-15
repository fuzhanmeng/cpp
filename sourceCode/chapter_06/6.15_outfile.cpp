//  outfile.cpp -- writing ti a file
#include <iostream>
#include <fstream>

int main ()
{
    char automobile[50];
    int year;
    double a_price;
    double d_price;

    std::ofstream outFile;
    outFile.open("carinfo.txt");

    std::cout << "enter the make and model of automobile: ";
    std::cin.getline(automobile,50);
    std::cout << "enter the model year: ";
    std::cin >> year;
    std::cout << "enter the original asking price: ";
    std::cin >> a_price;
    d_price = 0.913 * a_price;

    //  display information on screen with cout

    std::cout << std::fixed;    //  设置浮点数以​​定点表示法​​输出
    std::cout.precision(2);     //  设置浮点数输出的​​精度​​
    std::cout.setf(std::ios_base::showpoint);   //  强制显示浮点数的小数点和尾随零
    std::cout << "Make and model: " << automobile << std::endl;
    std::cout << "Year: " << year << std::endl;
    std::cout << "Was asking $" << a_price << std::endl;
    std::cout << "Now asking $" << d_price << std::endl;

    //  now do exact same things using outFile instead of cout

    outFile << std::fixed;
    outFile.precision(2);
    outFile.setf(std::ios_base::showpoint);
    outFile << "Make and model: " << automobile << std::endl;
    outFile << "Year: " << year << std::endl;
    outFile << "Was asking $" << a_price << std::endl;
    outFile << "Now asking $" << d_price << std::endl;

    outFile.close();

    return 0;
}