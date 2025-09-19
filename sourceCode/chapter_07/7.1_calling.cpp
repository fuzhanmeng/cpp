// calling.cpp -- defining, prototyping and calling a function

void simple();

#include <iostream>

int main()
{
    std::cout << "main() will call the simple() function()" << std::endl;
    simple();

    std::cout << "main() is finished with the simple() function" << std::endl;

    return 0;
}

// function definition
void simple() { std::cout << "I'm but a simple function" << std::endl; }
