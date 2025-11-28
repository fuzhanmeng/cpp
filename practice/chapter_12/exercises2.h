/**
 * @file exercises2.h
 * @brief exercises2
 * @author fzm
 * @date 2025-11-28
 */

#ifndef STRING1_H
#define STRING1_H

#include <cstring>
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
    friend String operator+(const String& str1, const String& str2);

    // static function
    static int HowMany();

    // function
    String& stringlow();
    String& stringup();
    int frequency(const char s);

private:
    int len;                      // length of string
    char* str;                    // pointer to string
    static int num_strings;       // number of objects
    static const int CINLIM = 80; // std::cin input limit
};

#endif // STRING1_H
