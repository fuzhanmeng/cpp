/**
 * @file 12.8_placenew1.cpp
 * @brief new, placment new, no delete
 * @author fzm
 * @date 2025-11-25
 */

#include <iostream>
#include <string>

const int BUF = 512;

class JustTesting
{
public:
    JustTesting(const std::string &s = "Just Testing", int n = 0)
    {
        words = s;
        number = n;
        std::cout << words << " constructed\n";
    }

    ~JustTesting() { std::cout << words << " destroyed\n"; }

    void show() const { std::cout << words << ", " << number << std::endl; }

private:
    std::string words;
    int number;
};

int main()
{
    char *buffer = new char[BUF]; // get a block of memory
    JustTesting *pc1, *pc2;
    pc1 = new (buffer) JustTesting;
    pc2 = new JustTesting("Heap1", 20);

    std::cout << "Memory block addresses:\n"
              << "buffer: " << (void *)buffer << "  heap: " << pc2 << std::endl;

    std::cout << "Memory contents:\n";
    std::cout << pc1 << ": ";
    pc1->show();
    std::cout << pc2 << ": ";
    pc2->show();

    JustTesting *pc3, *pc4;
    pc3 = new (buffer) JustTesting("Bad ieda", 6);
    pc4 = new JustTesting("Heap2", 10);
    std::cout << "Memory contents:\n";
    std::cout << pc3 << ": ";
    pc3->show();
    std::cout << pc4 << ": ";
    pc4->show();

    delete pc4;
    delete pc2;

    pc3->~JustTesting();
    pc1->~JustTesting();

    std::cout << "Done\n" << std::endl;
    return 0;
}