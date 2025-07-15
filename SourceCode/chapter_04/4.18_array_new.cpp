// arraynew.cpp -- using the new operator for arrays

#include <iostream>

int main()
{
    double *p3 = new double[3];
    p3[0] = 0.4; // treat p3 like an array name
    p3[1] = 1.12;
    p3[2] = 22.78;

    std::cout << "p3[1] is " << p3[1] << std::endl;
    p3 = p3 + 1;    //  指向数组的下一个元素

    std::cout << "Now p3 + 1 --> p3[0] is " << p3[0] << std::endl;
    std::cout << "Now p3 + 1 --> p3[1] is " << p3[1] << std::endl;

    p3 = p3 - 1; // point back to beginning
    std::cout << "Now p3 - 1 --> p3[0] is " << p3[0] << std::endl;
    std::cout << "Now p3 - 1 --> p3[1] is " << p3[1] << std::endl;

    p3[2] = 1;
    std::cout << p3[2] << std::endl;

    delete[] p3;

    return 0;
}