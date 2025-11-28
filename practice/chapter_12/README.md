### 12.9 复习题

1. 假设String类有如下私有成员：
```cpp
class String
{
private:
    char * str;     // points to string allocated by new
    int len;        // holds length of string
//...
};
```
a. 下述默认构造函数有什么问题？
```cpp
String::String() {}
```
没有正确的初始化str指针 str 未初始化（野指针）

b. 下述构造函数有什么问题？
```cpp
String::String(const char * s)
{
    str = s;
    len = strlen(s);
}
```
浅拷贝，str指向了s， 如果s是临时对象，那么str在s销毁后就成为了野指针
str 指向外部内存（浅拷贝）
c. 下述构造函数有什么问题？
```cpp
String::String(const char * s)
{
    strcpy(str, s);
    len = strlen(s);
}
```
str是野指针 未通过new来分配内存

2. 如果您定义了一个类，其指针成员是使用new初始化的，请指出可能出现的3个问题以及如何纠正这些问题。
1、 野指针问题，指针在构造函数中必须初始化
2、 浅拷贝问题，拷贝构造函数中要注意浅拷贝导致的双重释放问题
3、 内存泄露问题，在赋值构造函数中，要先释放旧的内存，再去申请新内存

3. 如果没有显式提供类方法，编译器将自动生成哪些类方法？请描述这些隐式生成的函数的行为。
1、默认构造函数
2、默认析构函数
3、默认拷贝构造函数
4、默认拷贝赋值运算符
5、默认移动构造函数
6、默认移动赋值运算符

4. 找出并改正下述类声明中的错误：
```cpp
class nifty
{
// data
    char personality[];
    //  C++不允许声明未指定大小的可变数组 char personality[]没有指定数组的大小
    int talents;
// methods
    nifty();
    nifty(char * s);
    ostream & operator<<(ostream & os, nifty & n);
};

nifty::nifty()
{
    personality = NULL;
    talents = 0;
    // personality 是一个char类型的数组  初始化不能用null去赋值 应该使用 personality[0] = '\0'
}

nifty::nifty(char * s) // 参数应该是const char*
{
    personality = new char [strlen(s)];
    personality = s;
    talents = 0;
    // new char [strlen(s)]; 应该+1 -> new char [strlen(s) + 1];
    // 赋值应该使用 strcpy(personality,s)
    
}

ostream & nifty::operator<<(ostream & os, nifty & n)
{
    os << n;
    // 缺少 return os
    // operator<< 声明错误：不能作为类成员函数 应该声明为友元函数
    // 应该输出n的具体成员 而不是输出整个对象 
    // os << n 会再次调用 ostream& operator<<(ostream&, nifty&)，导致 无限递归
}
```
```cpp

#include <iostream>
#include <cstring>  // 包含 strcpy、strlen 函数
using namespace std;

class nifty
{
// data：修改为指针类型（修正错误1）
    char* personality;  // 指针，指向动态分配的字符串
    int talents;
// methods
    nifty();
    nifty(const char* s);  // 修正错误3：参数改为 const char*
    ~nifty();  // 修正错误5：补充析构函数
    nifty(const nifty& other);  // 修正错误5：补充拷贝构造函数（深拷贝）
    nifty& operator=(const nifty& other);  // 修正错误5：补充赋值运算符（深拷贝）
    
    // 修正错误2：声明为友元函数（而非类成员）
    friend ostream& operator<<(ostream& os, const nifty& n);
};

// 1. 默认构造函数（修正错误7）
nifty::nifty()
{
    talents = 0;
    // 初始化指针为合法空字符串（避免野指针）
    personality = new char[1];  // 分配1字节存 '\0'
    personality[0] = '\0';      // 字符串结束符（不是 '\n'）
}

// 2. 带参构造函数（修正错误3、4）
nifty::nifty(const char* s)
{
    talents = 0;
    int len = strlen(s);
    personality = new char[len + 1];  // 修正：+1 存 '\0'
    strcpy(personality, s);           // 修正：拷贝内容（而非指针赋值）
}

// 3. 析构函数（修正错误5：释放动态内存）
nifty::~nifty()
{
    delete[] personality;  // 释放new分配的字符串内存
}

// 4. 拷贝构造函数（修正错误5：深拷贝）
nifty::nifty(const nifty& other)
{
    talents = other.talents;
    // 深拷贝：为新对象分配独立内存
    int len = strlen(other.personality);
    personality = new char[len + 1];
    strcpy(personality, other.personality);
}

// 5. 赋值运算符重载（修正错误5：深拷贝+避免自赋值+释放旧内存）
nifty& nifty::operator=(const nifty& other)
{
    if (this == &other) return *this;  // 防止自赋值（a = a）
    
    // 释放当前对象的旧内存（避免内存泄漏）
    delete[] personality;
    
    // 深拷贝新内容
    talents = other.talents;
    int len = strlen(other.personality);
    personality = new char[len + 1];
    strcpy(personality, other.personality);
    
    return *this;  // 支持链式赋值（a = b = c）
}

// 6. operator<< 友元函数实现（修正错误2、6）
ostream& operator<<(ostream& os, const nifty& n)
{
    // 输出具体成员（避免递归调用），加const保证不修改对象
    os << "Personality: " << n.personality << ", Talents: " << n.talents;
    return os;  // 修正：补充return os
}

// 测试代码（验证所有功能）
int main()
{
    nifty n1;                  // 调用默认构造
    nifty n2("Friendly");      // 调用带参构造
    nifty n3 = n2;             // 调用拷贝构造
    n1 = n2;                   // 调用赋值运算符
    
    cout << n1 << endl;        // 调用operator<<，输出：Personality: Friendly, Talents: 0
    cout << n2 << endl;
    cout << n3 << endl;
    
    return 0;
}

5. 对于下面的类声明：
```cpp
class Golfer
{
private:
    char * fullname;     // points to string containing golfer's name
    int games;           // holds number of golf games played
    int * scores;        // points to first element of array of golf scores
public:
    Golfer();
    Golfer(const char * name, int g = 0);
    // creates empty dynamic array of g elements if g > 0
    Golfer(const Golfer &);
    ~Golfer();
};
```
a. 下列各条语句将调用哪些类方法？
```cpp
Golfer nancy;                          // #1   默认构造函数
Golfer lulu ("Little Lulu");           // #2   含参构造函数
Golfer roy ("Roy Hobbs", 12);          // #3   含参构造函数
Golfer * par = new Golfer;             // #4   默认构造函数
Golfer next = lulu;                    // #5   拷贝构造函数
Golfer hazzard = "Weed Thwacker";      // #6   1、含参构造函数 2、拷贝构造函数
*par = nancy;                          // #7   赋值运算符重载
nancy = "Nancy Putter";                // #8   1、含参构造函数 2、赋值运算符重载函数
```

b. 很明显，类需要有另外几个方法才能更有用，但是类需要那些方法才能防止数据被损坏呢？
Golfer类含有2个指针
在进行操作时，要特别注意指针的复制导致的double free情况
所以必不可少的函数是 赋值运算符重载函数 
