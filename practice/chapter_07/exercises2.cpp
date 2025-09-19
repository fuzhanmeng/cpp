// 7.2
// 编写一个程序，要求用户输入最多10个高尔夫成绩，并将其存储在一个数组中。程序允许用户提早结束输入，并在一行上显示所有成绩，然后报告平均成绩。请使用3个数组处理函数来分别进行输入、显示和计算平均成绩

#include <iostream>

const int ArSize = 10;
int fill_array(double *ar, int x);
void show_array(double *ar, int x);
double average(double *ar, int x);

int main()
{
    double arr[ArSize];
    int n = fill_array(arr, ArSize);
    show_array(arr, n);
    double number = average(arr, n);
    std::cout << "the average is " << number << std::endl;
    return 0;
}

int fill_array(double *ar, int x)
{
    int count = 0;
    for (int i = 0; i < x; i++)
    {
        std::cout << "enter a number to fill the array:" << i << std::endl;
        if (!(std::cin >> ar[i]))
        {
            std::cin.clear();
            while (std::cin.get() != '\n');
            break;
        }
        else if (ar[i] < 0)
            break;
        count++;
    }
    std::cout << "the count is " << count << std::endl;
    return count;
}

void show_array(double *ar, int x)
{
    for (int i = 0; i < x; i++)
    {
        std::cout << "array[" << i << "]" << ar[i] << std::endl;
    }
}

double average(double *ar, int x)
{
    int ave = 0;
    int num = 0;
    for (int i = 0; i < x; i++)
    {
        num += ar[i];
    }
    ave = num / x;
    return ave;
}