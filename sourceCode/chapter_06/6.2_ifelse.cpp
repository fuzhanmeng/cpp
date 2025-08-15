//  ifelseif.cpp -- using the if else statement
#include <iostream>
int main ()
{
    char ch;
    std::cout << "type, and I shall repeat.\n";
    std::cin.get(ch);
    while ('.' != ch)
    {
        if ('\n' == ch)
        {
            std::cout << ch;
        } else{
            // std::cout << ++ch;
            std::cout << ch + 1;
        }
        std::cin.get(ch);
    }
    
    std::cout << "\nplease excuse the slight confusion.\n";
    return 0;
}

//++ch ch++ ch + 1
//对于ch++ 或者++ch来说 都是字符本身的值+1 a + 1 变为b  c + 1 变为d
//对于ch + 1 来说 是对应的ASCII码+1 输入a  输出98