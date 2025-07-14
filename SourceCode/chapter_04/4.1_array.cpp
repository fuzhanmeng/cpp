#include <iostream>

int main()
{
    int yams[3];
    yams[0] = 5;
    yams[1] = 8;
    yams[2] = 2;

    int yamscosts[3] = {20, 30, 5};

    std::cout << "Total yams is " << yams[0] + yams[1] + yams[2] << std::endl;

    std::cout << "The package with " << yams[1] << " yams costs";
    std::cout << yamscosts[1] << "cents per yam" << std::endl;

    int total = yams[0] * yamscosts[0] + yams[1] * yamscosts[1];
    total = total + yams[2] * yamscosts[2];

    std::cout << "The total yams expense is " << total << std::endl;

    std::cout << "Size of yams array = " << sizeof yams;
    std::cout << "bytes.\n";
    std::cout << "sizeof one element =  " << sizeof yams[0];
    std::cout << "bytes.\n";

    return 0;
}