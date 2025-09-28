// swap.cpp -- Explicit Instantiation and Explicit Specialization

#include <iostream>
#include <string>

template<typename T>
void swap(T& a, T& b);

template<> 
void swap<int>(int& a, int& b);

int main()
{
    int a = 1, b = 2;
    std::string str1 = "apple";
    std::string str2 = "are you ok?";

    swap(a, b);
    std::cout << "a = " << a << ", b = " << b << std::endl;

    swap(str1, str2);
    std::cout << "str1 = " << str1 << ", str2 = " << str2 << std::endl;
    return 0;
}


// general template
template<typename T>
void swap(T& a, T& b)
{
    std::cout << "general template" << std::endl;
    T temp;
    temp = a;
    a = b;
    b = temp;
}

// Explicit Instantiation
template void swap<std::string>(std::string& a, std::string& b);

// Explicit Specialization
template<> 
void swap<int>(int& a, int& b)
{
    std::cout << "explicit instantiation" << std::endl;
    int temp = 0;
    temp = a;
    a = b;
    b = temp;
}
