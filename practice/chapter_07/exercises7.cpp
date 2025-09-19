// 7.修改程序清单7.7中的3个数组处理函数，使之使用两个指针参数来表示区间
// fill_array(
// )函数不返回实际读取了多少个数字，而是返回一个指针，该指针指向最后被填充的位置；
// 其他的函数可以将该指针作为第二个参数，以标识数据结尾

#include <iostream>
#include <limits>
const int len = 5;
double *fill_array(double *start, double *end);
void show_array(double *start, double *end);
void revalue(double *start, double *end, double r);
int main()
{
    double properties[len];
    std::cout << " " << std::endl;
    double *p = fill_array(properties, properties + len);
    std::cout << "p = " << p << " *p = " << *p << " *(p -1) = " << *(p - 1) << std::endl;

    show_array(properties, p);

    revalue(properties, p, 1.2);
    show_array(properties, p);
}

double *fill_array(double *start, double *end)
{
    double *ptr = nullptr;
    for (ptr = start; ptr != end; ptr++)
    {
        if (!(std::cin >> *ptr))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "enter error break" << std::endl;
            break;
        }
        if (*ptr < 0)
        {
            break;
        }
    }
    return ptr;
}

void show_array(double *start, double *end)
{
    double *ptr = nullptr;
    for (ptr = start; ptr != end; ptr++)
    {
        std::cout << "the number = " << *ptr << std::endl;
    }
}

void revalue(double *start, double *end, double r)
{
    double *ptr = nullptr;
    for (ptr = start; ptr != end; ptr++)
    {
        *ptr *= r;
    }
}