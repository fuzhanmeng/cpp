#include <iostream>
#include <cstring>

int main()
{
    const int Size = 15;
    char name1[Size];
    char name2[Size] = "C++owboy";

    std::cout << "Howdy! I'm" << name2 << std::endl;
    std::cout << "!What's your name?" << std::endl;

    // std::cin << std::endl 是不被允许的，因为 std::istream 没有定义 operator<<
    // std::cin >> name1 << std::endl;
    std::cin >> name1;
    std::cout << "Well " << name1 << " , your name has ";
    std::cout << strlen(name1) << " letter and is stored" << std::endl;

    std::cout << "Your initial is " << name1[0] << std::endl;
    name2[3] = '\0'; // set to null character
    std::cout << name2 << std::endl;

    return 0;
}