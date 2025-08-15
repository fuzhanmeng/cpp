//  jump.cpp -- using continute and break

#include <iostream>
const int ArSize = 80;

int main()
{
    char line[ArSize];
    int spaces = 0;

    std::cout << "enter a line of text:" << std::endl;
    std::cin.get(line,ArSize);
    std::cout << "Complete line:\n" << line << std::endl;
    for (int i = 0; line[i] != '\0'; i++)
    {
        // std::cout << line[i];
        std::cout << line[i] << std::flush;
        if ('.' == line[i])
            break;
        if(' ' != line[i])
            continue;   //  会跳过后面的内容(spaces++;) 回到条件判断的地方
        spaces++;
    }
    std::cout << "\n" << spaces << " spaces\n";
    std::cout << "Done.\n";
    return 0;
}