/**
 * @file 12.5_string1.cpp
 * @brief String class methods
 * @author fzm
 * @date 2025-11-24
 */

#include <cstring>
#include <istream>
#include <ostream>

#include "12.4_string1.h"

int String::num_strings = 0;

// static method
int String::HowMany()
{
    return num_strings;
}


String::String()
{
    len = 4;
    str = new char[1];
    str[0] = '\0';
    num_strings++;
}

String::String(const char* s)
{
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    num_strings++;
}

String::String(const String& st)
{
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
    num_strings++;
}

String::~String()
{
    num_strings--;
    delete[] str;
}

// assign a C string to a String
String& String::operator=(const char* s)
{
    delete[] str;
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    return *this;
}

// assign a String to a String
String& String::operator=(const String& st)
{
    if (this == &st)
    {
        return *this;
    }
    delete[] str;
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
    return *this;
}

// read-write char access for non-const String
char& String::operator[](int i) { return str[i]; }

// read-only char access for const String
const char& String::operator[](int i) const { return str[i]; }

// overload friends

bool operator<(const String& st1, const String& st2) { return (std::strcmp(st1.str, st2.str) < 0); }

bool operator>(const String& st1, const String& st2) { return st2 < st1; }

bool operator==(const String& st1, const String& st2) { return (std::strcmp(st1.str, st2.str) == 0); }

// simple String output
std::ostream& operator<<(std::ostream& os, const String& st)
{
    os << st.str;
    return os;
}

// quick and dirty String input
std::istream& operator>>(std::istream& is, String& st)
{
    char temp[String::CINLIM];
    is.get(temp, String::CINLIM);
    if (is)
    {
        st = temp;
    }
    while (is && is.get() != '\n')
    {
        continue;
    }
    return is;
}
