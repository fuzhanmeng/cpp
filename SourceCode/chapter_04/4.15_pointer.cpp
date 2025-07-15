// pointer.cpp -- our first pointer variable
#include <iostream>

int main()
{
    int updates = 6;
    int *p_updates;

    std::cout << p_updates << std::endl;

    p_updates = &updates;

    // express values two ways
    std::cout << "Values: updates = " << updates;
    std::cout << ", *p_updates = " << *p_updates << std::endl;

    // express address two ways
    std::cout << "Address: &updates is " << &updates;
    std::cout << ", p_updates is " << p_updates << std::endl;

    // use pointer to change value
    *p_updates = *p_updates + 2;
    std::cout << "Now updates value is " << updates << std::endl;

    // Output the address again and find that the address remains unchanged
    std::cout << "Address: &updates is " << &updates;
    std::cout << ", p_updates is " << p_updates << std::endl;

    // p_updates is a address
    return 0;
}