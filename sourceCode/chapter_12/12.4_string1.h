/**
 * @file 12.4_string1.h
 * @brief fix and augmented string class definition
 * @author fzm
 * @date 2025-11-24
 */

#ifndef STRING1_H
#define STRING1_H

#include <iostream>
#include <istream>
#include <ostream>

class String
{
public:
    String();
    String(const char* st);
    String(const String& st);
    ~String();

    int length() { return len; };

    // overloaded operator methods
    String& operator=(const char* s);
    String& operator=(const String& st);
    char& operator[](int i);
    const char& operator[](int i) const;

    // overloaded operator friends
    friend bool operator<(const String& str1, const String& str2);
    friend bool operator>(const String& str1, const String& str2);
    friend bool operator==(const String& str1, const String& str2);
    friend std::ostream& operator<<(std::ostream& os, const String& st);
    friend std::istream& operator>>(std::istream& is, String& st);

    // static function
    static int HowMany();

private:
    int len;                      // length of string
    char* str;                    // pointer to string
    static int num_strings;       // number of objects
    static const int CINLIM = 80; // std::cin input limit
};

#endif // STRING1_H
