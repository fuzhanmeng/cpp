// forstr1.cpp -- using for with string
#include <iostream>
#include <string>

int main ()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    // std::cout << word.size() << std::endl;
    // size_t i = word.size() - 1; 避免数组越界
    // std::cout << word[i] << std::endl;
    // size_t 类型（无符号整数），所以 i >= 0 永远为真。
    for (int i = word.size() - 1; i >= 0; i--)
    {
        std::cout << "word["<< i << "] =" << i << word[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}