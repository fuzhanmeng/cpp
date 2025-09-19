// 10.
// 设计一个名为calculate()的函数，它接受两个double值和一个指向函数的指针，而被指向的函数接受两个double参数，并返回一个double值。
// calculate()函数的类型也是double，并返回被指向的函数使用calculate() 的两个double参数计算得到的值。
// 例如，假设add()函数的定义如下：

// double add(double x, double y)
// {
//      return x + y;
// }

// 则下述代码中的函数调用将导致calculate( )把2.5和10.4传递给add( )函数，并返回add( )的返回值(12.9):
// double q = calculate(2.5, 10.4, add);
// 请编写一个程序，它调用上述两个函数和至少另一个与add()类似的函数。该程序使用循环来让用户成对地输入数字。
// 对于每对数字，程序都使用calculate() 来调用add()和至少一个其他的函数。
// 如果读者爱冒险，可以尝试创建一个指针数组，其中的指针指向add()样式的函数，并编写一个循环，使用这些指针连续让calculate()
// 调用这些函数。提示：下面是声明这种指针数组的方式，其中包含三个指针：
// double (*pf[3])(double, double);
// 可以采用数组初始化语法，并将函数名作为地址来初始化这样的数组。

#include <iomanip>
#include <iostream>
#include <limits>

double add(double x, double y);
double subtract(double x, double y);
double multiply(double x, double y);
double calculate(double a, double b, double (*fp)(double x, double y));

int main()
{
    typedef double (*func)(double x, double y);
    func fp = add;
    // double (*func[3])(double, double) ={add, subtract, multiply};
    func fp1[3] = {add, subtract, multiply};
    double a, b;
    std::string fun_name[3] = {"add", "subtract", "multiply"};
    while (true)
    {
        std::cout << "enter a" << std::endl;
        if (!(std::cin >> a))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "error enter" << std::endl;
            break;
        }

        std::cout << "enter b" << std::endl;
        if (!(std::cin >> b))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }

        for (int i = 0; i < 3; i++)
        {
            double value = calculate(a, b, fp1[i]);
            std::cout << std::setw(10) << fun_name[i] << "value = " << value << std::endl;
        }
    }

    double result = calculate(2.1, 4.2, fp);
    std::cout << "the resulr is: " << result << std::endl;
}

double calculate(double a, double b, double (*fp)(double x, double y)) { return fp(a, b); }

double add(double x, double y) { return x + y; }

double subtract(double x, double y) { return x - y; }

double multiply(double x, double y) { return x * y; }