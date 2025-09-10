// funptr.cpp -- pointers to functions
#include <iostream>
double betsy(int);
double pam(int);
void estimate(int lines, double (*fp)(int x));

int main()
{
    int code;
    std::cout << "How many lines of code do you need> " << std::endl;
    std::cin >> code;

    std::cout << "Here's Betsy's estimate: " << std::endl;
    estimate(code, betsy); // fp -> betsy
    std::cout << "Here's Pam's estimate:" << std::endl;
    estimate(code, pam); // fp -> pam

    return 0;
}

double betsy(int lns)
{
    return 0.05 * lns;
}

double pam(int lns)
{
    return 0.03 * lns + 0.0004 * lns * lns;
}

void estimate(int lines, double (*fp)(int x))
{
    std::cout << lines << "lines will take: " << fp(lines) << "time" << std::endl;
}
