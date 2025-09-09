// arrfun3.cpp -- array functions and const

#include <iostream>
const int Max = 5;
int fill_array(double *arr, int limit);
void show_array(const double *arr, int n);
void revalue(double r, double *arr, int n);

int main()
{
    double properties[Max];

    int size = fill_array(properties, Max);
    show_array(properties, size);

    if (size > 0)
    {
        std::cout << "Enter revaluation factor: ";
        double factor;
        while (!(std::cin >> factor))
        {
            std::cin.clear();
            while (std::cin.get() != '\n')
            {
                continue;
            }
            std::cout << "Bad input, Please enter a number: ";
        }
        revalue(factor, properties, size);
        show_array(properties, size);
    }
}

int fill_array(double *arr, int limit)
{
    double temp;
    int i = 0;
    for (i = 0; i < limit; i++)
    {
        std::cout << "Enter value #" << (i + 1) << " : ";
        std::cin >> temp;
        if (!std::cin)
        {
            std::cin.clear();
            // clear the input buffer (until newline character)
            while (std::cin.get() != '\n')
            {
                continue;
            }
            std::cout << "Bad input, Please enter a number: " << std::endl;
            break;
        }
        else if (0 > temp)
        {
            break;
        }
        arr[i] = temp;
    }
    return i;
}

void show_array(const double *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << "Property #" << (i + 1) << ": $" << std::endl;
        std::cout << "properties[i] = " << arr[i] << std::endl;
    }
}

void revalue(double r, double *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] *= r;
    }
}
