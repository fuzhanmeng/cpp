​8.7 复习题​​

1. 哪种函数适合定义为内联函数
比较简单的函数、调用频繁的小函数、模板函数

2. 假设 song() 函数的原型如下：
void song(const char *name, int times);

a. 如何修改原型,使 times 的默认值为 1?
void song(const char* name, int times = 1);

b. 函数定义需要做哪些修改?
函数定义不需要改，只要声明里带默认值即可

c. 能否为 name 提供默认值 “O.My Papa”?
void song(const char* name = "O.My Papa",int times = 1);

3. 编写 iquote() 的重载版本——显示其用双引号括起的参数.编写 3 个版本：
   一个用于 int 参数,一个用于 double 参数,另一个用于 string 参数.
iquote(int x);
iquote(double x);
iquote(std::string str);

4. 下面是一个结构模板：
struct box
{
    char maker[40];
    float height;
    float width;
    float length;
    float volume;
};
a．请编写一个函数,它将box结构的引用作为形参,并显示每个成员的值.
#include <iostream>

struct box
{
    char maker[40];
    float height;
    float width;
    float length;
    float volume;
};

void show_struct(box& b);

int main()
{
    std::cout << "use box&" << std::endl;
    box b = {"apple", 3, 4, 5, 2333};
    show_struct(b);

    return 0;
}

void show_struct(box& b)
{
    std::cout << "maker: " << b.maker << "\n";
    std::cout << "hight: " << b.height << "\n";
    std::cout << "width: " << b.width << "\n";
    std::cout << "length: " << b.length << "\n";
    std::cout << "volume: " << b.volume << "\n";
}

b．请编写一个函数,它将box结构的引用作为形参,并将volume成员设置为其他3边的乘积.
#include <iostream>

struct box
{
    char maker[40];
    float height;
    float width;
    float length;
    float volume;
};

void show_struct(box& b);

int main()
{
    std::cout << "use box&" << std::endl;
    box b = {"apple", 3, 4, 5, 2333};
    show_struct(b);

    return 0;
}

void show_struct(box& b)
{
    std::cout << "maker: " << b.maker << "\n";
    std::cout << "hight: " << b.height << "\n";
    std::cout << "width: " << b.width << "\n";
    std::cout << "length: " << b.length << "\n";
    std::cout << "volume: " << b.volume << "\n";
    b.volume = b.length * b.width * b.height;
    std::cout << "volume: " << b.volume << "\n";
}


5. 为让函数fill()和show()使用引用参数,需要对程序清单7.15做哪些修改?
// arrobj.cpp -- functions with array objects

#include <array>
#include <iostream>
#include <string>

const int Seasons = 4;
const std::array<std::string, Seasons> Snames = {"Spring", "Summer", "Fall", "Winter"};
void fill(std::array<double, Seasons>& pa);
void show(std::array<double, Seasons>& pa);

int main()
{
    std::array<double, 4> expenses;

    fill(expenses);
    show(expenses);

    return 0;
}

void fill(std::array<double, Seasons>& pa)
{
    for (int i = 0; i < Seasons; i++)
    {
        std::cout << "Enter " << Snames[i] << " expenses: ";
        std::cin >> (pa)[i];
    }
}

void show(std::array<double, Seasons>& pa)
{
    double total = 0;
    std::cout << "\nEXPENSEX";

    for (int i = 0; i < Seasons; i++)
    {
        std::cout << Snames[i] << " : $" << pa[i] << std::endl;
        total += pa[i];
    }
    std::cout << "the total = " << total << std::endl;
}

6. 指出下面每个目标是否可以使用默认参数或函数重载完成,或者这两种方法都无法完成,并提供合适的原型.

a. mass(density, volume)返回密度为density、体积为volume的物体的质量,而mass(denstity)返回密度为density、体积为1.0立方米的物体的质量.这些值的类型都为double.
默认参数
double mass(double density, double volume = 1.0);
int mass(density, 1) {return density/1}

b．repeat(10, “I'm OK”)将指定的字符串显示10次,而repeat(“Butyou're kind of stupid”)将指定的字符串显示5次.


c．average(3, 6)返回两个int参数的平均值（int类型）,而average(3.0, 6.0)返回两个double值的平均值（double类型）.
重载
int average(int a, int b);
double average(double a, double b);

d．mangle(“I'm glad to meet you”)根据是将值赋给char变量还是char*变量,分别返回字符I和指向字符串“I'm mad to gleet you”的指针.
char mangle(const char* s);
const char* mangle(char* s)

#include <iostream>
#include <string>

// a. mass(density, volume) 和 mass(density)
double mass(double density, double volume = 1.0) { return density * volume; }

// b. repeat(10, "I'm OK") 和 repeat("But you're kind of stupid")
void repeat(int n, const std::string& str)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << str << "\n";
    }
}

void repeat(const std::string& str)
{ // 固定 5 次
    for (int i = 0; i < 5; i++)
    {
        std::cout << str << "\n";
    }
}

// c. average(int, int) 和 average(double, double)
int average(int a, int b)
{
    std::cout << "[int version]\n";
    return (a + b) / 2;
}

double average(double a, double b)
{
    std::cout << "[double version]\n";
    return (a + b) / 2.0;
}

// d. mangle
char mangle(const char* s)
{
    return s[0]; // 返回首字符
}

const char* mangle(char* s)
{
    return "I'm mad to gleet you"; // 返回一个指针
}

int main()
{
    // a. mass
    std::cout << "mass(10, 2) = " << mass(10, 2) << "\n";
    std::cout << "mass(8) = " << mass(8) << "\n"; // 默认 volume = 1.0

    // b. repeat
    std::cout << "\nrepeat(3, \"I'm OK\"):\n";
    repeat(3, "I'm OK");
    std::cout << "\nrepeat(\"But you're kind of stupid\"):\n";
    repeat("But you're kind of stupid");

    // c. average
    std::cout << "\naverage(3, 6) = " << average(3, 6) << "\n";
    std::cout << "average(3.0, 6.0) = " << average(3.0, 6.0) << "\n";

    // d. mangle
    const char* s1 = "I'm glad to meet you";
    char str2[] = "I'm glad to meet you"; // 可修改的数组
    std::cout << "\nmangle(const char*) = " << mangle(s1) << "\n";
    std::cout << "mangle(char*) = " << mangle(str2) << "\n";

    return 0;
}



7. 编写返回两个参数中较大值的函数模板.
template <typename T>
T return_Max(T& a, T& b) {return a > b ? a : b}


8. 给定复习题6的模板和复习题 4 的 box 结构,提供一个模板具体化,它接受两个 box 参数,并返回体积较大的一个.
#include <iostream>

struct box
{
    char maker[40];
    float height;
    float width;
    float length;
    float volume;
};

template<typename T>
float volume(T& b1, T& b2);

int main()
{
    std::cout << "b1" << std::endl;
    box b1 = {"apple1", 3, 4, 5, 2333};

    std::cout << "b1" << std::endl;
    box b2 = {"apple2", 4, 5, 6, 12121};

    float value = volume(b1, b2);

    std::cout << "value = " << value << std::endl;

    return 0;
}

template<typename T>
float volume(box& b1, box& b2)
{
    float v1 = b1.height * b1.width * b1.length;
    float v2 = b2.height * b2.width * b2.length;
    return v1 > v2 ? v1 : v2;
}


9. 在下述代码（假定这些代码是一个完整程序的一部分）中,v1 v2 v3 v4 和 v5 分别是哪种类型?

int g(int x);
float m = 5.5f;
float& rm = m;

decltype(m) v1 = m; float
decltype(rm) v2 = m; float&
decltype((m)) v3 = m; 
decltype(g(100)) v4; int 
decltype(2.0 * m) v5; 



8.8 编程练习

1.  编写通常接受一个参数（字符串的地址），并打印该字符串的函数。然而，如果提供了第二个参数（int类型），且该参数不为0，则该函数打印字符串的次数将为该函数被调用的次数（注意，字符串的打印次数不等于第二个参数的值，而等于函数被调用的次数）。是的，这是一个非常可笑的函数，但它让您能够使用本章介绍的一些技术。在一个简单的程序中使用该函数，以演示该函数是如何工作的。

2.  CandyBar结构包含3个成员。第一个成员存储candy bar的品牌名称；第二个成员存储candy bar的重量（可能有小数）；第三个成员存储candy bar的热量（整数）。请编写一个程序，它使用一个这样的函数，即将CandyBar的引用、char指针、double和int作为参数，并用最后3个值设置相应的结构成员。最后3个参数的默认值分别为“Millennium Munch”、2.85和350。另外，该程序还包含一个以CandyBar的引用为参数，并显示结构内容的函数。请尽可能使用const。

3.  编写一个函数，它接受一个指向string对象的引用作为参数，并将该string对象的内容转换为大写，为此可使用表6.4描述的函数toupper( )。然后编写一个程序，它通过使用一个循环让您能够用不同的输入来测试这个函数，该程序的运行情况如下:

    Enter a string (q to quit): go away
    GO AWAY
    Next string (q to quit): good grief!
    GOOD GRIEF!
    Next string (q to quit): q
    Bye.
    

4.  下面是一个程序框架:
    #include <iostream>
    using namespace std;
    #include <cstring>      // for strlen(), strcpy()
    
    struct stringy {
        char * str;          // points to a string
        int ct;            // length of string (not counting '\0')
    };
    
    // prototypes for set(), show(), and show() go here
    
    int main()
    {
        stringy beany;
        char testing[] = "Reality isn't what it used to be.";
        set(beany, testing);    // first argument is a reference,
                        // allocates space to hold copy of testing,
                        // sets str member of beany to point to the
                        // new block, copies testing to new block,
                        // and sets ct member of beany
    

    接续部分：
        show(beany);     // prints member string once
        show(beany, 2);   // prints member string twice
        testing[0] = 'D';
        testing[1] = 'u';
        show(testing);   // prints testing string once
        show(testing, 3); // prints testing string thrice
        show("Done!");
        return 0;
    }
    

    请提供其中描述的函数和原型，从而完成该程序。注意，应有两个show( )函数，每个都使用默认参数。请尽可能使用const参数。set( )使用new分配足够的空间来存储指定的字符串。这里使用的技术与设计和实现类时使用的相似。（可能还必须修改头文件的名称，删除using编译指令，这取决于所用的编译器。）

5.  编写模板函数max5( )，它将一个包含5个T类型元素的数组作为参数，并返回数组中最大的元素（由于长度固定，因此可以在循环中使用硬编码，而不必通过参数来传递）。在一个程序中使用该函数，将T替换为一个包含5个int值的数组和一个包含5个double值的数组，以测试该函数。

6.  编写模板函数maxn( )，它将由一个T类型元素组成的数组和一个表示数组元素数目的整数作为参数，并返回数组中最大的元素。在程序对它进行测试，该程序使用一个包含6个int元素的数组和一个包含4个double元素的数组来调用该函数。程序还包含一个具体化，它将char指针数组和数组中的指针数量作为参数，并返回最长的字符串的地址。如果有多个这样的字符串，则返回其中第一个字符串的地址。使用由5个字符串指针组成的数组来测试该具体化。

7.  修改程序清单8.14，使其使用两个名为SumArray()的模板函数来返回数组元素的总和，而不是显示数组的内容。程序应显示thing的总和以及所有debt的总和。

