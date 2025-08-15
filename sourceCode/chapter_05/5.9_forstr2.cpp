// forstr2.cpp -- reversing an array

#include <iostream>
int main ()
{
    std::cout << "enter a word: ";
    std::string word;
    std::cin >> word;

    char temp;
    int i, j;
    for (int i = 0, j = word.size() - 1; i < j; i++, j--)
    {
        temp = word[i];
        word[i] = word[j];
        word[j] = temp;
    }
    
    std::cout << word << std::endl;

    return 0;
}

