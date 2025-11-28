/**
 * @file exercises2.cpp
 * @brief
 * @author fzm
 * @date 2025-11-28
 */

#include "exercises2.h"

#include <cctype>
#include <cstring>
#include <iostream>
#include <string>


int String::num_strings = 0; 
String::String()
{
    len = 0;
    str = new char[1];
    str[0] = '\0';
}

String::String(const char* st)
{
    len = std::strlen(st);
    str = new char[len + 1];
    std::strcpy(str, st);
    num_strings++;
}

String::String(const String& st)
{
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
    num_strings++;
}

String::~String() { delete[] str; }

String& String::operator=(const char* s)
{
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    num_strings++;
    return *this;
}

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
    num_strings++;

    return *this;
}

char& String::operator[](int i) { return str[i]; }

const char& String::operator[](int i) const { return str[i]; }

bool operator<(const String& str1, const String& str2) { return (std::strcmp(str1.str, str2.str) < 0); }

bool operator>(const String& str1, const String& str2) { return str2 < str2; }

bool operator==(const String& str1, const String& str2) { return (std::strcmp(str1.str, str2.str) == 0); }

// std::ostream& operator<<(std::ostream& os, const String& st)
// {
//     std::cout << st.len << std::endl;
//     std::cout << st.str << std::endl;
//     return os;
// }

std::ostream& operator<<(std::ostream& os, const String& st)
{
    // ❌ 删除：std::cout << st.len << std::endl;
    
    // ✅ 修复：直接输出字符串内容。
    // 注意：这里使用 os 而不是 std::cout
    os << st.str; 
    
    // ❗ 重要：不要在这里添加 std::endl 或 '\n'，让调用者控制换行
    return os;
}

// std::istream& operator>>(std::istream& is, String& st)
// {
//     std::cin >> st.len;
//     std::cin >> st.str;
//     return is;
// }
std::istream& operator>>(std::istream& is, String& st)
{
    char temp[String::CINLIM]; // 使用类中定义的输入限制 CINLIM (通常是 80)
    
    // 1. 使用 getline 安全地读取一行输入
    is.get(temp, String::CINLIM);

    // 2. 检查读取是否成功且输入流是否在良好状态
    if (is)
    {
        // 3. 释放旧内存
        delete [] st.str;
        
        // 4. 为新字符串分配内存
        st.len = std::strlen(temp);
        st.str = new char[st.len + 1];
        std::strcpy(st.str, temp);
    }
    
    // 5. 处理输入流中可能残留的回车
    while (is && is.get() != '\n')
        continue; // 丢弃剩余字符
        
    return is;
}

String operator+(const String& str1, const String& str2)
{
    String result;

    delete[] result.str;

    result.len = str1.len + str2.len;
    result.str = new char[result.len + 1]; // ✅ 修复：赋值给 result.str 成员

    std::strcpy(result.str, str1.str);
    std::strcat(result.str, str2.str);

    return result;
}

String& String::stringlow()
{
    for (int i = 0; i < len; i++)
    {
        str[i] = std::tolower(str[i]);
    }
    return *this;
}

String& String::stringup()
{
    for (int i = 0; i < len; i++)
    {
        str[i] = std::toupper(str[i]);
    }

    return *this;
}

// 接收`char`参数并返回该字符在字符串中出现的次数
int String::frequency(const char s)
{
    int times = 0;
    // len = st.len; 将当前对象的长度覆盖成了参数 st 的长度。这个函数的功能只是计数，不应该修改任何对象的内部状态
    for (int i = 0; i < len; i++)
    {
        if (s == str[i])
        {
            times++;
        }
    }

    return times;
}