// twoswap.cpp -- specialization overrides a template

#include <ios>
#include <iostream>
template <typename T>
void Swap(T& a, T& b);

struct job
{
    char name[40];
    double salary;
    int floor;
};

// explicit specialization
template <>
void Swap<job>(job& j1, job& j2);

void show(job& j);

int main()
{
    std::cout.precision(2);
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);

    int i = 10;
    int j = 20;

    std::cout << "i = " << i << ", j = " << j << std::endl;
    std::cout << "using compiler-generated int swapper: \n";
    Swap(i, j);
    std::cout << "now i = " << i << ", j = " << j << std::endl;

    job sue = {"Susan Yaffee", 73000.60, 7};
    job sidney = {"Sidney Taffee", 78060.72, 9};
    std::cout << "Before job swapping: \n";
    show(sue);
    show(sidney);
    Swap(sue, sidney);

    std::cout << "after job swapping: \n";
    show(sue);
    show(sidney);

    return 0;
}

template <typename T>
void Swap(T& a, T& b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

template <>
void Swap<job>(job& j1, job& j2)
{
    double t1;
    int t2;

    t1 = j1.salary;
    j1.salary = j2.salary;
    j2.salary = t1;

    t2 = j1.floor;
    j1.floor = j2.floor;
    j2.floor = t2;
}

void show(job& j) { std::cout << j.name << ": $" << j.salary << " on floor " << j.floor << std::endl; }
