//  compstr1.cpp -- comparing strings using arrays

#include <iostream>
#include <cstring>

int main ()
{
    char word[5] = "?ate";

    //  strcmp if word == mate return 0 else return 1
    for (char ch = 'a'; strcmp(word, "mate"); ch++)
    {
        std::cout << word << std::endl;
        word[0] = ch;
    }
    
    std::cout << "after loop ends, word is " << word << std::endl;

    return 0;
}