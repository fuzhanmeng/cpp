// arfupt.cpp -- an array of function pointers
#include <iostream>

const double* f1(const double* ar, int n);
const double* f2(const double ar[], int n);
const double* f3(const double ar[], int n);

int main()
{
    double av[3] = {1112.3, 1542.6, 2227.9};

    // pointer to a function
    typedef const double* (*p_fun)(const double*, int);

    // p1 p2 -> is a function pointer
    p_fun p1 = f1;
    auto p2 = f2;

    std::cout << "using pointers to functions: " << std::endl;
    std::cout << "address value" << std::endl;
    std::cout << (*p1)(av, 3) << ": " << *(*p1)(av, 3) << std::endl;
    std::cout << p2(av, 3) << ": " << *p2(av, 3) << std::endl;

    std::cout << "=============pa===============" << std::endl;
    // pa -> an array of pointers
    p_fun pa[3] = {f1, f2, f3};
    auto pb = pa;
    std::cout << "using an array pf pointers to functions: " << std::endl;
    std::cout << "address value" << std::endl;

    for (int i = 0; i < 3; i++)
    {
        std::cout << pa[i](av, 3) << ": " << *pa[i](av, 3) << std::endl;
    }

    std::cout << "=============pb===============" << std::endl;
    std::cout << "using a pointer to a pointer to a function:" << std::endl;
    std::cout << "address value" << std::endl;

    for (int i = 0; i < 3; i++)
    {
        std::cout << pb[i](av, 3) << ": " << *pb[i](av, 3) << std::endl;
    }

    std::cout << "=============&pa===============" << std::endl;

    // pc pointer pa, pa is an array
    auto pc = &pa;
    // *pc
    std::cout << (*pc)[0](av, 3) << ": " << *(*pc)[0](av, 3) << std::endl;

    //  pd is a pointer
    p_fun(*pd)[3] = &pa;
    const double* pdb = (*pd)[1](av, 3);
    std::cout << pdb << ":  " << *pdb << std::endl;
    std::cout << *(*pd)[2](av, 3) << std::endl;
    std::cout << (*(*pd)[2])(av, 3) << ": " << *(*(*pd)[2])(av, 3) << std::endl;

    return 0;
}

const double* f1(const double* ar, int n) { return ar; }

const double* f2(const double ar[], int n) { return ar + 1; }

const double* f3(const double ar[], int n) { return ar + 2; }