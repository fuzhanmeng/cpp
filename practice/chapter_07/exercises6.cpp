// 7.6编写一个程序，它使用下列函数:
// Fill_array() 将一个 double 数组的名称和长度作为参数。它提示用户输入 double
// 值，并将这些值存储到数组中。
// 当数组被填满或用户输入了非数字时，输入将停止，并返回实际输入了多少个数字;
// Show_array() 将一个 double 数组的名称和长度作为参数，并显示该数组的内容;
// Reverse-array() 将一个 double
// 数组的名称和长度作为参数，并将存储在数组中的值的顺序反转。

// 程序将使用这些函数来填充数组，然后显示数组;反转数组，然后显示数组;反转数组中除第一个和最后一个元素之外的所有元素，然后显示数组。

#include <algorithm>
#include <iostream>
#include <limits>

const int ArSize = 8;

int fill_array(double *ar, int len);
void show_array(double *arr, int len);
void reverse_array(double *ar, int len);

int main()
{
    double ar[ArSize];
    std::cout << "run fill_array" << std::endl;
    int total_number = fill_array(ar, ArSize);
    std::cout << "total number" << total_number << std::endl;
    show_array(ar, ArSize);
    reverse_array(ar, ArSize);
    show_array(ar, ArSize);
    return 0;
}

int fill_array(double *ar, int len)
{
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        std::cout << "enter number: " << count << std::endl;
        if (!(std::cin >> ar[i]))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "invaild input, please enter again" << std::endl;
            break;
        }
        else if (ar[i] < 0)
        {
            break;
        }
        count++;
    }

    return count;
}

void show_array(double *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        std::cout << arr[i] << std::endl;
    }
}

void reverse_array(double *ar, int len)
{
    std::cout << "run reverse_array" << std::endl;
    for (int i = 0; i < len / 2; i++)
    {
        std::swap(ar[i], ar[len - 1 - i]);
    }
}