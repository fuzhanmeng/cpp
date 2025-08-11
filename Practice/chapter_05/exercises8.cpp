// 8. 编写一个程序，使用char数组和循环依次读取单词，直到用户输入“done”为止
//    随后，程序将显示用户输入了多少个单词（不包括“done”）。示例输出：

//    Enter words (to stop, type the word done):
//    anteater birthday category dumpster
//    entry finagle ganery done for sure
//    You entered a total of 7 words.

//    程序应包含头文件`cstring`并使用`strcmp()`函数进行比较。
#include <iostream>
#include <cstring>

int main()
{
    char ch[20] = "";
    int sum = 0;
    std::cout << "Enter words (to stop, type the word done): " << std::endl;

    //  先读取一个单词 才能做判断
    std::cin >> ch;
    while (strcmp(ch, "done")) // trcmp(ch, "done")在相等时返回0(假),不相等时返回非0(真)
    {
        std::cin >> ch;
        sum++;
    }

    std::cout << "You entered a total of " << sum << " words.  " << std::endl;
}