//  express.cpp --- values of expressions

#include <iostream>

int main ()
{
    int x;

    std::cout << "the expression x = 100 has the values ";
    std::cout << (x = 100) << std::endl;
    std::cout << "Now x = " << x << std::endl;

    std::cout << "the expression x < 3 has the values ";
    std::cout << (x < 3) << std::endl;
    std::cout << "Now x = " << x << std::endl;

    std::cout << "the expression x > 3 has the values ";
    std::cout << (x > 3) << std::endl;
    std::cout << "Now x = " << x << std::endl;

    //  使用英文单词 true 和 false 来替代 1 和 0
    std::cout.setf(std::ios_base::boolalpha);
    
    std::cout << "the expression x < 3 has the values ";
    std::cout << (x < 3) << std::endl;

    std::cout << "the expression x > 3 has the values ";
    std::cout << (x > 3) << std::endl;

    return 0;
}