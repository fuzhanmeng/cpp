// 7.
// 编写一个程序,读取用户输入的单词,直到输入 "q" 为止.然后统计：
// - 有多少个单词以元音开头
// - 有多少个单词以辅音开头
// - 还有多少个单词不属于以上两类
// 建议使用 `isalpha()` 函数判断开头字符是否为字母；之后通过 `if` 或 `switch` 判断是否是元音字母.

// 示例运行情况如下：

// Enter words (q to quit):
// the 12 awesome oxen ambled
// quietly across 5 meters of lawn. q
// 5 words beginning with vowels
// 4 words beginning with consonants
// 2 others

#include <iostream>
#include <cctype>
#include <string>

int main()
{
    std::string words;
    int vowelsCounts = 0;
    int consonantsCounts = 0;
    int otherCounts = 0;

    std::cout << "Enter words (q to quit):" << std::endl;

    while (std::cin >> words && words != "q")
    {
        if (isalpha(words[0]))
        {
            char lowerChar = std::towlower(words[0]);
            switch (words[0])
            {
            case 'a':;
            case 'e':;
            case 'i':;
            case 'o':;
            case 'u':;
                vowelsCounts++;
                break;

            default:
                consonantsCounts++;
                break;
            }
        }
        else
            otherCounts++;
    }

    std::cout << vowelsCounts << " words beginning with vowels" << std::endl;
    std::cout << consonantsCounts << " words beginning with consonants" << std::endl;
    std::cout << otherCounts << " others" << std::endl;
}