以下是提取并还原图片中的排版文字内容：

---

### 6.10 复习题

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
```

```cpp
// Version 2
while (cin.get(ch))  // quit on eof
{
    if (ch == ' ')
        spaces++;
    else if (ch == '\n')
        newlines++;
}
```

第二种格式比第一种格式好在哪里呢？

2. 在程序清单 6.2 中，用 `ch+1` 替换 `+ch` 将发生什么情况呢？

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
```

假设输入如下（请在每行末尾按回车键）：

```
Hi!
Send $10 or $20 now!
```

则输出结果是什么（还记得吗，输入被缓冲）？

4. 创建表示下述条件的逻辑表达式：

- a. weight 大于或等于 115，但小于 125。
- b. ch 为小写 q。
- c. x 为偶数，但不是 26。
- d. x 为偶数，但不是 26 的倍数。
- e. donation 为 1000–2000 且 guest 为 1。
- f. ch 是小写字母或大写字母（假设小写字母是依次编码的，大写字母也是依次编码的，但在大小写字母编码的端点不是连续的）。

5. 在英语中，"I will not not speak（我不会不说）" 的意思与 "I will speak（我要说）" 相同。在 C++ 中，`!!x` 是否与 `x` 相同呢？

---

以下是按图片排版提取出的文字内容：

---

### 6.11 编程练习（续）

6. 创建一个条件表达式，求变量的绝对值。也就是说，如果变量 `x` 为正，则表达式的值为 `x`；但如果 `x` 为负，则表达式的值为 `-x`。这是一个正确值。

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

8. 对于程序清单 6.10，与使用数字相比，使用字符（如 `a` 和 `c`）表示菜单选项和 `case` 标签有何优点？（提示：想想用户输入 `a` 和输入 `5` 的情况。）

9. 将下面的代码片段改写为不使用 `break` 和 `continue` 的形式：

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
```

-----------------------------------------------------------------------------------------------------------

以下是按图片排版提取出的文字内容：

---

### 6.11 编程练习

**1.** 编写一个程序，该取键盘输入，直到遇到 @ 符号为止，并回显输入（数字除外），同时将大写字符转换为小写，将小写字符转换为大写（别忘了 cctype 标准系列）。

**2.** 编写一个程序，最多将 10 个 donation 值读入到一个 `double` 数组中（如果您愿意，也可使用模板 `array`）。程序到达文件尾时终止数组输入，并报告这些数字的平均值以及数组中有多少个数字大于平均值。

**3.** 编写一个菜单驱动的程序。该程序显示一个提供 4 个选项的菜单 —— 每个选项用一个字母标记。如果用户使用有效选项之外的字母进行输入，程序将提示用户输入一个有效的字母，直到用户这样做为止。然后，该程序使用一条 `switch` 语句，根据用户的选择执行一个简单操作。该程序的运行情况如下：

```
Please enter one of the following choices:
c) carnivore        p) pianist
t) tree             g) game
f
Please enter a c, p, t, or g: q
Please enter a c, p, t, or g: t
A maple is a tree.
```

**4.** 加入 Benevolent Order of Programmers 后，在 BOP 大会上，人们可以通过加入者的真实姓名、头衔或秘密 BOP 姓名来了解他（她）。请编写一个程序，可以使用真实姓名、头衔、秘密姓名来显示 BOP 成员的列表情况。每当该程序运行时，请使用下面的结构：

```cpp
// Benevolent Order of Programmers name structure:
struct bop {
    char fullname[strsize]; // real name
    char title[strsize];    // job title
    char bopname[strsize];  // secret BOP name
    int preference;         // 0 = fullname, 1 = title, 2 = bopname
};
```

该程序创建一个由上述结构组成的小型数组，并将其初始化为适当的值。另外，该程序使用一个循环，让用户在下面的选项中进行选择：

```
a. display by name      b. display by title
c. display by bopname   d. display by preference
q. quit
```

注意，“display by preference” 并不意味着显示成员的偏好，而是意味着根据成员的偏好来显示。例如，如果偏好号为 1，则选择 d 将显示某成员的头衔。该程序的运行情况如下：

```
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
Enter your choice: d
Wimp Macho
Junior Programmer
MIPS
Analyst Trainee
LOOPY
Next choice: q
Bye!

以下是按图片排版提取的文字内容：

---

### 第6章 分支语句和逻辑运算符  
页码：201  

**6.11 编程练习（续）**

**5.** 在 Neutronia 王国，货币单位是 tvarp，收入所得税的计算方式如下：  

- 第一个 5000 tvarps：不收税  
- 接下来的 10000 tvarps：收税 10%  
- 接下来的 20000 tvarps：收税 15%  
- 超过 35000 tvarps 的部分：收税 20%

例如，收入为 38000 tvarps 时，所得税为：  

```
5000 × 0.00 + 10000 × 0.10 + 20000 × 0.15 + 3000 × 0.20 = 4600 tvarps
```

请编写一个程序，使用循环让用户输入收入，并报告应缴税金。当用户输入负数或非数字字符时，循环结束。

**6.** 编写一个程序，记录提交给“维护公法权利和团结”团体的资金。程序要求用户输入捐赠者数量，然后要求用户输入每个捐赠者的姓名和捐款数额。这些信息被储存在一个动态分配的结构体数组中。每个结构体有两个成员：用来存储姓名的字符数组（或 `string` 对象）和用于存储捐款的 `double` 值。

读取所有数据后，程序显示所有捐款超过 10000 tvarps 的捐赠者姓名和捐款数额，这些人为 Grand Patrons。然后程序列出其他捐赠者（即 Patrons）。如果某个类别没有捐赠者，程序将打印单词 “none”。程序只显示两个类别，而不进行排序。

**7.** 编写一个程序，读取用户输入的单词，直到输入 “q” 为止。然后统计：  

- 有多少个单词以元音开头  
- 有多少个单词以辅音开头  
- 还有多少个单词不属于以上两类  

建议使用 `isalpha()` 函数判断开头字符是否为字母；之后通过 `if` 或 `switch` 判断是否是元音字母。

示例运行情况如下：


Enter words (q to quit):
the 12 awesome oxen ambled
quietly across 5 meters of lawn. q
5 words beginning with vowels
4 words beginning with consonants
2 others


**8.** 编写一个程序，打开一个文件，从文件中逐个字符读取直到到达文件末尾，报告该文件包含多少个字符。

**9.** 完成练习 6，但此次从文件中读取所需信息。文件的第一项是捐赠者人数，接下来是每位捐赠者的姓名和捐款额。假设文件内容如下：

```
4
Sam Stone
1000
Freida Flass
10500
Tammy Tubbs
5000
Rich Raptor
55000
