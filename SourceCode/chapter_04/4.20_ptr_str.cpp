// ptrstr.cpp -- using pointers to strings
#include <iostream>
#include <cstring>

int main()
{
    char animal[20] = "bear";
    const char *bird = "wren";
    char* ps;

    std::cout << animal << " and ";
    std::cout << bird << std::endl;

    std::cout << "Enter a kind of animal: ";
    std::cin >> animal;

    ps = animal;    // ps point to animal 
    std::cout << "animal = " << animal << std::endl;
    std::cout << "*ps = " << *ps << std::endl;
    ps[1] = 'a';
    std::cout << "---------------------------------" << std::endl;
    std::cout << "animal = " << animal << std::endl;
    std::cout << "*ps = " << *ps << std::endl;

    std::cout << "ps和 animal直接输出时,std::cout会打印字符串内容(因为它们是 char*类型)" << std::endl;
    std::cout << ps << "   " << animal << std::endl;
    std::cout << "Before using strcpy(): " << std::endl;

    std::cout << "如果想输出地址，需强制转换为 void* / int* " << std::endl;
    std::cout << animal << " at " << (int *)animal << std::endl; //animal is a address
    std::cout << ps << " at " << (int *)ps << std::endl; // ps is a address
    std::cout << "---------------ps------------------" << std::endl;
    std::cout << ps << " at " << ps << std::endl; // ps = fax

    ps = new char[strlen(animal) + 1];
    std::cout << "strlen(animal) + 1 = " << (strlen(animal) + 1) << std::endl;

    strcpy(ps, animal); //  将 animal字符串的内容（包括 '\0'）​​逐字符复制​​到 ps指向的内存中
    std::cout << "After using strcpy(): " << std::endl;
    std::cout << ps << " at " << (int *)ps << " " << &ps << std::endl;
    delete[] ps;
    ps = nullptr;  // 避免悬空指针
    std::cout << "---------------------------------" << std::endl;
    char str[] = "hello";
    char *c1 = str;  
    std::cout << c1 << std::endl; // 输出 "hello"，而非地址
    std::cout << (int*)c1 << std::endl;
    std::cout << &str << std::endl;

    return 0;
}