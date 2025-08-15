#include <iostream>

int main ()
{
    std::cout << "What's years was your house build? " << std::endl;

    int year;
    std::cin >> year;

    //std::cin 不会读取/0 /会留在缓冲区 所以需要    std::cin.get()将缓冲区的/0读取掉
    std::cin.get();
    std::cout << "What's is its streer address? " << std::endl;
    

    char address[80];
    std::cin.getline(address,80);
    std::cout << "year build " << year << std::endl;
    std::cout << "address: " << address << std::endl;
    std::cout << "Done!" << std::endl;

    return 0;
}