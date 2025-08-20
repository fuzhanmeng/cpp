# 6.10 复习题

1. 请看下面两个计算空格和换行符数目的代码片段：

```cpp
// Version 1
while (cin.get(ch))  // quit on eof
{
    if (ch == ' ')
        spaces++;
    if (ch == '\n')
        newlines++;
}

// Version 2
while (cin.get(ch))  // quit on eof
{
    if (ch == ' ')
        spaces++;
    else if (ch == '\n')
        newlines++;
}

第二种格式比第一种格式好在哪里呢？

1、对于ch 为空格时  Version1 判断2次 Version2 只需判断1次
2、对于ch 为换行时  Version1 和 Version2 都需要判断两次


2. 在程序清单 6.2 中,用ch+1替换+ch将发生什么情况呢？

1、 对于++ch --- 是对应的字符+1  如 ch == a  那么  ++ch 就是b ch变为b

2、对于 ch + 1 --- 是ch对应的字符ASCII码+1 ch == a  那么 ch + 1 就是 a对应的ASCII码 + 1
char被隐式转换为 int 不修改原始变量​​ ch

3. 请认真考虑下面的程序：

```cpp
#include <iostream>
using namespace std;
int main()
{
    char ch;
    int ct1, ct2;

    ct1 = ct2 = 0;
    while ((ch = cin.get()) != '$')
    {
        cout << ch;
        ct1++;
        if (ch != '$')
            ct2++;
        cout << ch;
    }
    cout << "ct1 = " << ct1 << ", ct2 = " << ct2 << "\n";
    return 0;
}

假设输入如下(请在每行末尾按回车键)：

Hi!
Send $10 or $20 now!

则输出结果是什么(还记得吗,输入被缓冲)？

4. 创建表示下述条件的逻辑表达式：

- a. weight 大于或等于 115,但小于 125
    weight >= 115 && weight < 125

- b. ch 为小写 q
    ch == 'q'

- c. x 为偶数,但不是 26
    x % 2 == 0 && x != 26

- d. x 为偶数,但不是 26 的倍数
    x % 2 == 0 && x % 26 == 0
    正确答案应为
    x % 2 == 0 && x % 26 != 0

- e. donation 为 1000–2000 且 guest 为 1
    donation == (1000-2000) && guest == 1
    错误  看成了 1000-2000  实际上是1000 - 2000 之间
    donation > 1000 && donation < 2000 && guest == 1
    
- f. ch 是小写字母或大写字母(假设小写字母是依次编码的,大写字母也是依次编码的,但在大小写字母编码的端点不是连续的)
    (ch > 'a' && ch < 'z') || (ch > 'A' && ch < 'Z')

5. 在英语中,"I will not not speak(我不会不说)" 的意思与 "I will speak(我要说)" 相同.在 C++ 中,`!!x` 是否与 `x` 相同呢？
    !!x 和 x 不同
    if x = 2 
    !!x = !(!x) 
    !x = 0 
    !!x = !(!x) = 1
    所以  if x = 2  那么 !!x = 1

6. 创建一个条件表达式,求变量的绝对值.也就是说,如果变量x为正,则表达式的值为x；但如果x为负,则表达式的值为-x.这是一个正确值.
    x > 0 ? x :: -x
    未考虑 x = 0 的时候
    (x >= 0 ) ? x : -x

7. 用 `switch` 改写下面的代码片段：

```cpp
if (ch == 'A')
    a_grade++;
else if (ch == 'B')
    b_grade++;
else if (ch == 'C')
    c_grade++;
else if (ch == 'D')
    d_grade++;
else
    f_grade++;
```

```cpp
    switch(ch)
    {
    case 'A':
        a_grade++;
        break;
    case 'B':
        b_grade++;
        break;
    case 'C':
        c_grade++;
        break;
    case 'D':
        d_grade++;
        break;
    default:
        f_grade++;
        break;
    }

8. 对于程序清单 6.10,与使用数字相比,使用字符(如a和c)表示菜单选项和case标签有何优点？(提示：想想用户输入a和输入5的情况)

chocie 类型为int 时  如果不小心输入了其他字符 
设置输入流的失败状态（failbit）
导致后续输入操作被跳过
程序陷入无限循环（因为 choice未被更新）

chocie 类型为字符时
不符合case 的默认执行default 不会失败

9. 将下面的代码片段改写为不使用 break和 continue 的形式：

原始代码：

```cpp
int line = 0;
char ch;
while (cin.get(ch))
{
    if (ch == 'Q')
        break;

    if (ch != '\n')
        continue;
    line++;
}

//  写法有问题
while (cin.get(ch))
{
    if (ch == 'Q')
        return;
    else if (ch != '\n')\
    line++;
}

### 6.11 编程练习


1. 编写一个程序,该取键盘输入,直到遇到 @ 符号为止,并回显输入(数字除外),同时将大写字符转换为小写,将小写字符转换为大写(别忘了 cctype 标准系列).

```cpp
#include <iostream>
#include <cctype>

int main()
{
    char ch;
    std::cout << "enter ch in while" << std::endl;

    while (std::cin.get(ch) && '@' != ch)
    {
        if (isdigit(ch))
        {
        }
        else if (islower(ch))
        {
            ch = toupper(ch);
            std::cout << ch;
        }
        else if (isupper(ch))
        {
            ch = tolower(ch);
            std::cout << ch;
        }
        else
            std::cout << ch;
    }

    return 0;
}


2. 编写一个程序,最多将 10 个 donation 值读入到一个 `double` 数组中(如果您愿意,也可使用模板 `array`).程序到达文件尾时终止数组输入,并报告这些数字的平均值以及数组中有多少个数字大于平均值.

```cpp
#include <iostream>
#include <array>

int main()
{
    std::array<double, 10> donation;
    int sum = 0;
    int count = 0;
    int num = 0;
    int average = 0;
    for (int i = 0; i < 10; i++)
    {
        std::cout << "enter an number: " << std::endl;
        std::cin >> donation[i];
        if (donation[i] == EOF)
        {
            break;
        }
        else
        {
            sum += donation[i];
            count++;
        }
        std::cout << "the count is " << count << std::endl;
        average = sum / count;
    }

    for (int i = 0; i < count; i++)
    {
        if (donation[i] > average)
        {
            num++;
        }
    }

    std::cout << "averange is " << average << " and > averange numbers is " << num << std::endl;
}

3. 编写一个菜单驱动的程序.该程序显示一个提供 4 个选项的菜单 —— 每个选项用一个字母标记.如果用户使用有效选项之外的字母进行输入,程序将提示用户输入一个有效的字母,直到用户这样做为止.然后,该程序使用一条 `switch` 语句,根据用户的选择执行一个简单操作.该程序的运行情况如下：

Please enter one of the following choices:
c) carnivore p) pianist
t) tree g) game
f
Please enter a c, p, t, or g: q
Please enter a c, p, t, or g: t
A maple is a tree.

```cpp
#include <iostream>

int main()
{
    std::cout << "Please enter one of the following choices:" << std::endl;
    std::cout << "c) carnivore p) pianist" << std::endl;
    std::cout << "t) tree g) game" << std::endl;
    std::cout << "f\n";

    char ch;
    std::cin.get(ch);
    while ('q' != ch)
    {
        switch (ch)
        {
        case 'c':
            std::cout << "c) carnivore" << std::endl;
            break;
        case 'p':
            std::cout << "p) pianist" << std::endl;
            break;
        case 't':
            std::cout << "A maple is a  tree" << std::endl;
            break;
        case 'g':
            std::cout << "g) game" << std::endl;
            break;
        default:
            std::cout << "Please enter a c, p, t, or g: q" << std::endl;
            break;
        }
        std::cin.get(ch);
    }

    return 0;
}

4. 加入 Benevolent Order of Programmers 后,在 BOP 大会上,人们可以通过加入者的真实姓名、头衔或秘密 BOP 姓名来了解他(她).请编写一个程序,可以使用真实姓名、头衔、秘密姓名来显示 BOP 成员的列表情况.每当该程序运行时,请使用下面的结构：

```cpp
// Benevolent Order of Programmers name structure:
struct bop {
    char fullname[strsize]; // real name
    char title[strsize];    // job title
    char bopname[strsize];  // secret BOP name
    int preference;         // 0 = fullname, 1 = title, 2 = bopname
};

该程序创建一个由上述结构组成的小型数组,并将其初始化为适当的值.另外,该程序使用一个循环,让用户在下面的选项中进行选择：

a. display by name      b. display by title
c. display by bopname   d. display by preference
q. quit

注意,"display by preference" 并不意味着显示成员的偏好,而是意味着根据成员的偏好来显示.例如,如果偏好号为 1,则选择 d 将显示某成员的头衔.该程序的运行情况如下：

Benevolent Order of Programmers Report
a. display by name      b. display by title
c. display by bopname   d. display by preference
q. quit
Enter your choice: a
Wimp Macho
Raki Rhodes
Celia Laiter
Hoppy Hipman
Pat Hand
Next choice: d
Wimp Macho
Junior Programmer
MIPS
Analyst Trainee
LOOPY
Next choice: q
Bye!

```cpp
#include <iostream>
#include <vector>
#include <string>

const int strsize = 30;
struct bop
{
    char fullname[strsize]; // real name
    char title[strsize];    // job title
    char bopname[strsize];  // secret BOP name
    int preference;         // 0 = fullname, 1 = title, 2 = bopname
};

int main()
{
    std::cout << "Benevolent Order of Programmers Report" << std::endl;
    std::cout << "a. display by name           b. display by title" << std::endl;
    std::cout << "c. display by bopname        d. display by preference" << std::endl;
    std::cout << "q. quit" << std::endl;

    std::vector<bop> bop = {
        {"Wimp Macho", "Wimp macho", "WM", 0},
        {"Raki Rhodes", "Junior Programmer", "hahaha", 1},
        {"Celia Laiter", "xiongda", "MIPS", 2},
        {"Hoppy Hipman", "Analyst Trainee", "HH", 1},
        {"Pat Hand", "xionger", "LOOPY", 2}};

    std::cout << "Enter your choice: ";
    char choice;
    std::cin >> choice;

    while (choice != 'q')
    {
        switch (choice)
        {
        case 'a':
            for (const auto &b : bop)
                std::cout << b.fullname << std::endl;
            break;
        case 'b':
            for (const auto &b : bop)
                std::cout << b.title << std::endl;
            break;
        case 'c':
            for (const auto &b : bop)
                std::cout << b.bopname << std::endl;
            break;
        case 'd':
            for (const auto &b : bop)
            {
                if (b.preference == 0)
                {
                    std::cout << b.fullname << std::endl;
                }
                else if (1 == b.preference)
                {
                    std::cout << b.title << std::endl;
                }
                else
                    std::cout << b.bopname << std::endl;
            }
            break;
        default:
            std::cout << "aaaa" << std::endl;
            break;
        }
        std::cout << "Next choice: ";
        std::cin >> choice;
    }
    std::cout << "Bye!" << std::endl;
}


5. 在 Neutronia 王国,货币单位是 tvarp,收入所得税的计算方式如下：  

- 第一个 5000 tvarps：不收税  
- 接下来的 10000 tvarps：收税 10%  
- 接下来的 20000 tvarps：收税 15%  
- 超过 35000 tvarps 的部分：收税 20%

例如,收入为 38000 tvarps 时,所得税为：  

5000 × 0.00 + 10000 × 0.10 + 20000 × 0.15 + 3000 × 0.20 = 4600 tvarps

请编写一个程序,使用循环让用户输入收入,并报告应缴税金.当用户输入负数或非数字字符时,循环结束.

```cpp
#include <iostream>
#include <cctype>

int main()
{
    int tvarps;
    std::cout << "cin your tvarps: ";
    double tax = 0;
    std::cin >> tvarps;

    while (tvarps >= 0 && !isdigit(tvarps))
    {
        double tax = 0.0;
        // (0 < tvarps)结果是布尔值（0 或 1），然后与 5000 比较
        if (tvarps <= 5000)
        {
            tax = 0;
        }
        else if (tvarps <= 15000)
        {
            tax = (tvarps - 5000) * 0.1;
        }
        else if (tvarps <= 35000)
        {
            tax = (10000 * 0.1) + ((tvarps - 15000) * 0.15);
        }
        else if (tvarps > 35000)
        {
            tax = (10000 * 0.10) + (20000 * 0.15) + ((tvarps - 35000) * 0.20);
        }

        std::cout << "taxation = " << tax << " tveaps" << std::endl;
        std::cout << "cin your tvarps: ";
        std::cin >> tvarps;
    }
}

6. 编写一个程序,记录提交给"维护公法权利和团结"团体的资金.程序要求用户输入捐赠者数量,然后要求用户输入每个捐赠者的姓名和捐款数额.这些信息被储存在一个动态分配的结构体数组中.每个结构体有两个成员：用来存储姓名的字符数组(或 string 对象)和用于存储捐款的 double 值.
读取所有数据后,程序显示所有捐款超过 10000 tvarps 的捐赠者姓名和捐款数额,这些人为 Grand Patrons.然后程序列出其他捐赠者(即 Patrons).如果某个类别没有捐赠者,程序将打印单词 "none".程序只显示两个类别,而不进行排序.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <limits>

struct Donor
{
    std::string name;
    double tvarps;
};

int main()
{
    std::cout << "Enter the number of donors: ";
    int numbers = 0;
    std::cin >> numbers;

    // 清理掉回车符  丢掉输入缓冲区中所有内容，直到遇到一个换行符为止
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // 错误方式：创建了一个向量数组
    // std::vector<play> public_welfare[numbers];

    // 正确方式：创建一个包含numbers个元素的向量
    std::vector<Donor> donors(numbers);
    for (int i = 0; i < numbers; i++)
    {
        std::cout << "Name:  ";
        std::getline(std::cin, donors[i].name);

        std::cout << "the tvarps of donors: ";
        std::cin >> donors[i].tvarps;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "===== Grand Patrons =====" << std::endl;
    bool GrandPatrons = false;
    for (int i = 0; i < numbers; i++)
    {
        if (donors[i].tvarps > 10000)
        {
            std::cout << "Name: " << donors[i].name << " : " << donors[i].tvarps << " tvarps" << std::endl;
            GrandPatrons = true;
        }
    }
    if (!GrandPatrons)
    {
        std::cout << "none" << std::endl;
    }

    std::cout << "===== Patrons =====" << std::endl;
    bool Patrons = false;
    for (int i = 0; i < numbers; i++)
    {
        if (donors[i].tvarps < 10000)
        {
            std::cout << "Name: " << donors[i].name << " : " << donors[i].tvarps << " tvarps" << std::endl;
            Patrons = true;
        }
    }
    if (!Patrons)
    {
        std::cout << "none" << std::endl;
    }
}

7. 编写一个程序,读取用户输入的单词,直到输入 "q" 为止.然后统计：  

- 有多少个单词以元音开头  
- 有多少个单词以辅音开头  
- 还有多少个单词不属于以上两类  

建议使用 `isalpha()` 函数判断开头字符是否为字母；之后通过 `if` 或 `switch` 判断是否是元音字母.

示例运行情况如下：

Enter words (q to quit):
the 12 awesome oxen ambled
quietly across 5 meters of lawn. q
5 words beginning with vowels
4 words beginning with consonants
2 others

```cpp
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

8. 编写一个程序,打开一个文件,从文件中逐个字符读取直到到达文件末尾,报告该文件包含多少个字符.

```cpp
#include <iostream>
#include <fstream>
#include <string> // 添加 string 头文件用于 getline

int main()
{
    std::cout << "Enter file name: ";
    std::string filename;
    std::getline(std::cin, filename); // 允许输入带路径的文件名

    std::ifstream inFile;
    inFile.open(filename);

    if (!inFile.is_open())
    {
        std::cout << "Failed to open file: " << filename << std::endl;
        return 1; // 返回非零表示错误
    }

    char ch;
    int count = 0;

    // 逐个字符读取
    while (inFile.get(ch))
    {
        count++;
    }

    // 先检查是否读取失败（非文件结束原因）
    if (inFile.fail() && !inFile.eof())
    {
        std::cout << "Error reading file" << std::endl;
    }
    else
    {
        std::cout << "Reached end of file" << std::endl;
    }

    std::cout << "Total characters: " << count << std::endl;

    inFile.close(); // 显式关闭文件

    return 0;
}

9. 完成练习 6,但此次从文件中读取所需信息.文件的第一项是捐赠者人数,接下来是每位捐赠者的姓名和捐款额.假设文件内容如下：

4
Sam Stone
1000
Freida Flass
10500
Tammy Tubbs
5000
Rich Raptor
55000     

```cpp
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>

struct Donor
{
    std::string name;
    double tvarps;
};

int main()
{
    std::cout << "Enter the number of donors: " << std::endl;

    std::ifstream inFile;

    inFile.open("text.txt");
    if (!inFile.is_open())
    {
        std::cout << "open the file failed" << std::endl;
    }

    int numbers;
    inFile >> numbers;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<Donor> donors(numbers);

    for (int i = 0; i < numbers; i++)
    {
        std::getline(inFile, donors[i].name);

        // std::getline()只能用于读取字符串，不能直接读取 double类型
        // std::getline(inFile, donors[i].tvarps);
        inFile >> donors[i].tvarps;

        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "===== Grand Patrons =====" << std::endl;
    bool isGrand;
    for (int i = 0; i < numbers; i++)
    {
        if (donors[i].tvarps > 10000)
        {
            std::cout << "Name:  " << donors[i].name << " : " << donors[i].tvarps << " tvarps" << std::endl;
            isGrand = true;
        }
    }
    if (!isGrand)
    {
        std::cout << "None" << std::endl;
    }

    std::cout << "===== Patrons =====" << std::endl;

    bool isPatrons;
    for (int i = 0; i < numbers; i++)
    {
        if (donors[i].tvarps < 10000)
        {
            std::cout << "Name:  " << donors[i].name << " : " << donors[i].tvarps << " tvarps" << std::endl;
            isPatrons = true;
        }
    }
    if (!isPatrons)
    {
        std::cout << "None" << std::endl;
    }

    return 0;
}