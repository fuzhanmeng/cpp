// compstr2.cpp -- comparing strings using arrays

#include <iostream>
#include <string>

int main ()
{
    std::string word = "?ate";

    //  compare std::string
    for (char ch = 'a'; word != "mate"; ch++)
    {
        std::cout << word << std::endl;
        word[0] = ch;
    }
    std::cout << "after loop ends, word is " << word << std::endl;

    return 0;
}