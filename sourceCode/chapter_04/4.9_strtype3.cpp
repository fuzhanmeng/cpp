// strtype3.cpp -- more string class features --- strcpy strcat

#include <iostream>
#include <string>  // make string class available
#include <cstring> // C-style string library

int main()
{
    char charr1[20];
    char charr2[20] = "jaguar";
    std::string str1;
    std::string str2 = "panther";

    // assignment for string objects and character arrays
    str1 = str2;            // copy str2 to str1
    std::cout << str1 << std::endl;
    strcpy(charr1, charr2); // copy charr2 to charr1
    std::cout << charr1 << std::endl;

    // appending for string objects and character arrays
    str1 += "paste";         // add paste to end of str1
    strcat(charr1, "juice"); // add juice to end of charr1

    // finding the length of a string object and a C-style string
    int len1 = str1.size();    // obtain length of str1
    int len2 = strlen(charr1); // obtain length of charr1

    std::cout << "The string " << str1 << " contains " << len1 << " characters" << std::endl;
    std::cout << "The string " << charr1 << " contains " << len2 << " characters." << std::endl;

    return 0;
}