/**
 * @file 12.1_stringBag.h
 * @brief flawed string class definition
 * @author fzm
 * @date 2025-11-20
 */

#include <iostream>
#include <istream>
#include <ostream>

#ifndef STRINGBAG_H
#define STRINGBAG_H

class StringBad
{
public:
    StringBad();              // default constructor
    StringBad(const char* s); // constructor
    ~StringBad();             // destructor

    // friend function
    friend std::ostream& operator<<(std::ostream& os, const StringBad& st);

private:
    char* str;              // point to string
    int len;                // length of string
    static int num_strings; // number of objects
};

#endif // STRINGBAG_H