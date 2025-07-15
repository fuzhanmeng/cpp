#include <iostream>

int main()
{
    char charr1[20];            // create an empty array
    char charr2[20] = "jaguar"; // create an initialized array

    std::string str1;             // create an empty string objec
    std::string str2 = "panther"; // create an initialized string

    std::cout << "Enter a king of feline: ";
    std::cin >> charr1;

    std::cout << "Enter another king od feline: ";
    std::cin >> str1;

    std::cout << "Here are some felines: " << std::endl;

    std::cout << charr1 << " " << charr2 << " " << str1 << " " << str2 << std::endl;

    std::cout << "The third letter in " << str2 << " is " << str2[2] << std::endl;
}