7.12 复习题

1. 使用函数的3个步骤是什么?
   1. 定义函数
   2. 声明函数
   3. 调用函数

2．请创建与下面的描述匹配的函数原型.

a．igor()没有参数,且没有返回值.
   void igor();

b．tofu()接受一个int参数,并返回一个float.
   float tofu(int x);

c．mpg()接受两个double参数,并返回一个double.
   double mpg(double a, double b);

d．summation()将long数组名和数组长度作为参数,并返回一个long值.
   long arr[Size];
   long summation(const long arr[], Size);

e．doctor()接受一个字符串参数（不能修改该字符串）,并返回一个double值.
   std::string str;
   double doctor(const std::string str);

f．ofcourse()将boss结构作为参数,不返回值.
   struct boss
   {
        int x,
        float b,
        std::string str;
   }
   void odcourse(boss b);

g．plot()将map结构的指针作为参数,并返回一个字符串.
struct map
{
   int a,
   double b,
}
map my_map;
map* p = &my_map;
std::string plot(map* p);

3．编写一个接受3个参数的函数:int数组名、数组长度和一个int值,并将数组的所有元素都设置为该int值.
#include <iostream>
const int ArSize = 8;
void fun(int *ar, int ArSize, int n);
int main ()
{
    int arr[ArSize];
    fun(arr, ArSize, 2);
}
void fun(int *ar, int ArSize, int n)
{
    for(int i = 0; i < ArSize; i++)
    {
        ar[i] = n;
        std::cout << ar[i] << std::endl;
    }
}

4．编写一个接受3个参数的函数:指向数组区间中第一个元素的指针、指向数组区间最后一个元素后面的指针以及一个int值,并将数组中的每个元素都设置为该int值.
#include <iostream>
void function(int* a, const int*p, int x);
const int ArSize = 8;
int main ()
{
    int arr[ArSize];
    int* a = &arr[0];
    int* b = &arr[ArSize];

    function(a, b, 2);
    for (int i = 0; i < ArSize; i++)
    {
        std::cout << arr[i] << std::endl;
    }
    
}

void function(int* begin, const int* end, int x)
{
    for (int* a = begin; a != end; a++)
    {
        *a = x;
    }
}

5．编写将double数组名和数组长度作为参数,并返回该数组中最大值的函数.该函数不应修改数组的内容.
#include <iostream>
const int Size = 8;
double return_MaxNumber(const double *ar, int x);

int main()
{
    double ar[Size] = {12.1, 22, 676.232, 77.092, 9833.2, 24.22, 1, 56};
    double num = return_MaxNumber(ar, Size);
    std::cout << num << std::endl;
}

double return_MaxNumber(const double *ar, int x)
{
    double number = ar[0];
    for (int i = 1; i < x; i++)
    {
        if (ar[i] > number)
        {
            number = ar[i];
        }
    }
    return number;
}

6．为什么不对类型为基本类型的函数参数使用const限定符?
int, float, double, char 等原生类型
传递基本类型时，函数参数是按值传递，修改的只是参数副本，不会对参数本身产生任何影响

7．C++程序可使用哪3种C-风格字符串格式?
   1. char str[] = "apple"  char类型的字符数组
   2. char str = "apple"  char类型的字符串
   3. char* str = "apple" char类型的字符串指针

8．编写一个函数,其原型如下:该函数将字符串中所有的c1都替换为c2,并返回替换次数.
#include <iostream>
#include <string>
int replace(std::string &str, char c1, char c2);

int main()
{
    std::string str = "apple aaa halee";

    int count = 0;
    count = replace(str, 'a', 'b');

    std::cout << count << "   " << str << std::endl;
}

int replace(std::string &str, char c1, char c2)
{
    int count = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == c1)
        {
            str[i] = c2;
            count++;
        }
    }
    return count;
}

9．表达式*"pizza"的含义是什么? "taco" [2]呢?
*"pizza" 对字符串 "pizza" 取地址
"taco" [2]

10．C++允许按值传递结构,也允许传递结构的地址.如果glitz是一个结构变量,如何按值传递它?如何传递它的地址?这两种方法有何利弊?

按值传递   fun(glitz)
按地址传递 fun(&glitz)

按值传递给fun后 fun内会生成一个glitz的副本 在fun内的所有操作均不回影响glitz本身
按地址传递给fun后  fun通过地址找到glitz本身 在fun函数内的任何操作都会影响glitz本身

11．函数judge()的返回类型为int,它将这样一个函数的地址作为参数:将const char指针作为参数,并返回一个int值.请编写judge()函数的原型.

int judge()
int (*fp)(const char*)
int judge(int (*fp)(const char*))

12．假设有如下结构声明:
a．编写一个函数,它将application结构作为参数,并显示该结构的内容.
b．编写一个函数,它将application结构的地址作为参数,并显示该参数指向的结构的内容.
#include <iostream>
struct application
{
    int a;
    double b;
    std::string c;
};

// 函数声明一定要放在 struct application 定义之后
void show_application1(application);
void show_application2(application *);

int main()
{
    application a = {2, 12.21, "apple"};

    show_application1(a);
    show_application2(&a);
}

void show_application1(application a)
{
    std::cout << a.a << "  " << a.b << "  " << a.c << std::endl;
}

void show_application2(application *a)
{
    std::cout << a->a << "  " << a->b << "  " << a->c << std::endl;
}

13．假设函数f1()和f2()的原型如下:
void f1(applicant * a);
const char * f2(const applicant * a1, const applicant * a2);
请将p1和p2分别声明为指向f1和f2的指针；
将ap声明为一个数组,它包含5个类型与p1相同的指针；
将pa声明为一个指针,它指向的数组包含10个类型与p2相同的指针.
使用typedef来帮助完成这项工作.
#include <iostream>

struct applicant
{
    int a;
    std::string str;
};

void f1(applicant *a);
const char *f2(const applicant *a1, const applicant *a2);

int main()
{
    applicant a1 = {12, "Jacket"};
    applicant a2 = {77, "Sim"};

    typedef void (*p_fun1)(applicant *a);
    p_fun1 p1 = f1; // ✅ 正确，定义了变量 p1
    p1(&a1);

    typedef const char *(*p_fun2)(const applicant *a1, const applicant *a2);
    p_fun2 p2 = f2; // ✅ 正确，pf 是函数指针变量
    // p2 = f2;    // ❌ 错，p2 是类型，不是变量
    p2(&a1, &a2);

    const char *(*p3)(const applicant *a1, const applicant *a2);
    p3 = f2; // ✅ 正确，p3 已经是函数指针变量

    // ap 是一个指针数组 里面的每个元素都是一个函数值指针
    p_fun1 ap[5] = {p1, p1, p1, p1, p1};
    for (int i = 0; i < 5; i++)
    {
        std::cout << "ap[" << i << "] = ";
        ap[i](&a1);
        std::cout << "\n";
    }

    // p_fun2 ap2[10] = {f2, f2, f2, f2, f2, f2, f2, f2, f2, f2};
    // p_fun2* pa[10] = ap2;

    p_fun2 ap2[10] = {f2, f2, f2, f2, f2, f2, f2, f2, f2, f2}; // 数组，包含10个函数指针
    p_fun2 *pa1 = ap2;                                         // pa 指向 数组第一个元素（类型 p_fun2*
    p_fun2(*pa)[10] = &ap2;                                    // pa 指向整个数组
    for (int i = 0; i < 10; i++)
    {
        std::cout << "(*pa)[" << i << "] = ";
        (*pa)[i](&a1, &a2);
    }
}

void f1(applicant *a)
{
    std::cout << a->a << "  " << a->str << std::endl;
}

const char *f2(const applicant *a1, const applicant *a2)
{

    std::cout << a1->a << " " << a1->str << std::endl;
    std::cout << a2->a << " " << a2->str << std::endl;

    // return a1; 声明了返回 const char*，但没写 return → 未定义行为
    // c_str() 的主要功能是 把 C++ 的 std::string 转换成 C 风格字符串
    return a1->str.c_str();
}

编程题：
7.1 编写一个程序，不断要求用户输入两个数，直到其中的一个为 0。对于每两个数，程序将使用一个函数来计算它们的调和平均数， 并将结果返回给 main()，而后者将报告结果。调和平均数指的是倒数平均值的倒数，计算公式如下:
调和平均数 = 2.0 * x * y / (x+y)

7.2 编写一个程序，要求用户输入最多10个高尔夫成绩，并将其存储在一个数组中。程序允许用户提早结束输入，并在一行上显示所有成绩， 然后报告平均成绩。请使用3个数组处理函数来分别进行输入、显示和计算平均成绩。

7.3 下面是一个结构体的声明:

struct box {
    char maker[40];
    float height;
    float width;
    float length;
    float volume;
}

a. 编写一个函数，按值传递 box 结构体，并显示每个成员的值。 b. 编写一个函数，传递 box 结构体的地址，并将 volume 成员设置为其他三维长度的乘积。 c. 编写一个使用这两个函数的简单程序。

7.4  许多彩票发行机构都使用如程序清单7.4所示的简单彩票玩法的变体。在这些玩法中，玩家从一组被称为域号码(field number) 的号码中选择几个。例如，可以从域号码147中选择5个号码; 还可以从第二个区间(如127)选择一个号码(称为特选号码)。要赢得头奖，必 须正确猜中所有的号码。中头奖的几率是选中所有域号码的几率与选中特选号码几率的乘积。例如，在这个例子中，中头奖的几率是从47个号码 中正确选取5个号码的几率与从27个号码中正确选择1个号码的几率的乘积。请修改程序清单7.4，以计算中得这种彩票头奖的几率。

7.5   定义一个递归函数，接受一个整数参数，并返回该参数的阶乘。
    前面讲过，3的阶乘写作3!，等于32!，依此类推; 而 0! 被定义为1。通用的计算公式是，如果n大于零，则n!=n(n−1)!。 在程序中对该函数进行测试，程序使用循环让用户输入不同的值，程序将报告这些值的阶乘。

7.6编写一个程序，它使用下列函数:

    Fill_array() 将一个 double 数组的名称和长度作为参数。它提示用户输入 double 值，并将这些值存储到数组中。 当数组被填满或用户输入了非数字时，输入将停止，并返回实际输入了多少个数字;
    Show_array() 将一个 double 数组的名称和长度作为参数，并显示该数组的内容;
    Reverse-array() 将一个 double 数组的名称和长度作为参数，并将存储在数组中的值的顺序反转。

程序将使用这些函数来填充数组，然后显示数组;反转数组，然后显示数组;反转数组中除第一个和最后一个元素之外的所有元素，然后显示数组。

7.修改程序清单7.7中的3个数组处理函数，使之使用两个指针参数来表示区间。fill_array( )函数不返回实际读取了多少个数字，而是返回一个指针，该指针指向最后被填充的位置；其他的函数可以将该指针作为第二个参数，以标识数据结尾。

8.在不使用array类的情况下完成程序清单7.15所做的工作。编写两个这样的版本:

a.使用const char*数组存储表示季度名称的字符串，并使用double数组存储开支。

b.使用const char*数组存储表示季度名称的字符串，并使用一个结构，该结构只有一个成员——一个用于存储开支的double数组。这种设计与使用array类的基本设计类似。

9.这个练习让您编写处理数组和结构的函数。下面是程序的框架，请提供其中描述的函数，以完成该程序。

#include <iostream>

using namespace std;
const int SLEN = 30;

struct student {

char fullname[SLEN];

char hobby[SLEN];

int ooplevel;

};

// getinfo() has two arguments: a pointer to the first element of
// an array of student structures and an int representing the
// number of elements of the array. The function solicits and
// stores data about students. It terminates input upon filling
// the array or upon encountering a blank line for the student
// name. The function returns the actual number of array elements
// filled.
int getinfo(student pa[], int n);

// display1() takes a student structure as an argument
// and displays its contents
void display1(student st);

// display2() takes the address of student structure as an
// argument and displays the structure's contents
void display2(const student * ps);

// display3() takes the address of the first element of an array
// of student structures and the number of array elements as
// arguments and displays the contents of the structures
void display3(const student pa[], int n);

int main()
{
cout << "Enter class size: ";
int class_size;
cin >> class_size;
while (cin.get() != '\n')
continue;
student * ptr_stu = new student[class_size];
int entered = getinfo(ptr_stu, class_size);
for (int i = 0; i < entered; i++)
{
display1(ptr_stu[i]);
display2(&ptr_stu[i]);
}
display3(ptr_stu, entered);
delete [] ptr_stu;
cout << "Done\n";
return 0;
}

10. 设计一个名为calculate( )的函数，它接受两个double值和一个指向函数的指针，而被指向的函数接受两个double参数，并返回一个double值。calculate( )函数的类型也是double，并返回被指向的函数使用calculate( )的两个double参数计算得到的值。例如，假设add( )函数的定义如下:

double add(double x, double y)
{
return x + y;
}

则下述代码中的函数调用将导致calculate( )把2.5和10.4传递给add( )函数，并返回add( )的返回值(12.9):

double q = calculate(2.5, 10.4, add);

请编写一个程序，它调用上述两个函数和至少另一个与add( )类似的函数。该程序使用循环来让用户成对地输入数字。对于每对数字，程序都使用calculate( )来调用add( )和至少一个其他的函数。如果读者爱冒险，可以尝试创建一个指针数组，其中的指针指向add( )样式的函数，并编写一个循环，使用这些指针连续让calculate( )调用这些函数。提示:下面是声明这种指针数组的方式，其中包含三个指针:

double (*pf[3])(double, double);

可以采用数组初始化语法，并将函数名作为地址来初始化这样的数组。