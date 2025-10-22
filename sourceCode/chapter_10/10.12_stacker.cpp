// stacker.cpp -- testing the Stack class
#include <cctype>
#include <iostream>

#include "10.10_stack.h"

int main()
{
    // create Stack
    Stack st;

    char ch;
    unsigned long po;
    std::cout << "Please enter A to add a purchase order,\n"
              << "P to process a PO, or Q to quit.\n";

    while (std::cin >> ch && toupper(ch) != 'Q')
    {
        while (std::cin.get() != '\n')
        {
            continue;
        }
        if (!isalpha(ch))
        {
            std::cout << "\a";
            continue;
        }

        switch (ch)
        {
            case 'A':
            case 'a':
                std::cout << "Enter a PO number to add: ";
                std::cin >> po;
                if (st.isfull())
                {
                    std::cout << "the stack is full.\n";
                }
                else
                {
                    st.push(po);
                }
                break;
            case 'P':
            case 'p':
                std::cout << "pop stack.\n";
                if (st.isempty())
                {
                    std::cout << "the stack is empty.\n";
                }
                else
                {
                    st.pop(po);
                    std::cout << "po #" << po << " popped.\n";
                }
                break;
        }
        std::cout << "Please enter A to add a purchase order,\n"
                  << "P to process a PO, or Q to quit.\n";
    }
    std::cout << "bye.\n";
    return 0;
}