/**
 * @file 12.2_stringBag.cpp
 * @brief StringBad class methods
 * @author fzm
 * @date 2025-11-20
 */

 #include <cstring>
#include <iostream>
#include <ostream>
#include "12.1_stringBag.h"

int StringBad::num_strings = 0;

 StringBad::StringBad()
 {
    int len = 4;
    str = new char[len];
    std::strcpy(str,"c++");
    num_strings++;
    std::cout << num_strings << " \"" << str << "\"  default object created\n";
 }

 StringBad::StringBad(const char *st)
 {
    int len = std::strlen(st);
    str = new char[len + 1];
    std::strcpy(str,st);
    num_strings++;
    std::cout << num_strings << ": " << str << "  object created\n";
 }

 StringBad::~StringBad()
 {
    std::cout << "\"" << str << "object deleted, ";
    --num_strings;;
    std::cout << num_strings << " left\n";
    delete [] str;
 }

 std::ostream& operator<<(std::ostream& os, const StringBad& st)
 {
    std::cout << st.str;
    return os;
 }