// tempover.cpp -- template overloading
#include <iostream>

// template A
template <typename T>
void ShowArray(T arr, int n);

// template B
template <typename T>
void ShowArray(T* arr, int n);

struct debts
{
    char name[50];
    double amount;
};

int main()
{
    int things[6] = {13, 31, 103, 301, 310, 130};
    struct debts mr_E[3] =
    {
        {"Ima Wolfe", 2400.0},
        {"Ura Foxe", 1300.0},
        {"Iby Stout", 1800.0}
    };
    double * pd[3]; 

    // set pointers to the amount members of the structures in mr_E
    for (int i = 0; i < 3; i++)
    {
        pd[i] = &mr_E[i].amount;
    }
    std::cout << "Listing Mr_E E's counts of things:\n";

    // things is an array of int
    ShowArray(things, 6);

    // pd is an array of pointers t odouble
    ShowArray(pd, 3);

    return 0;
}

template <typename T>
void ShowArray(T arr, int n)
{
    std::cout << "template A" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n";
}

template <typename T>
void ShowArray(T* arr, int n)
{
    std::cout << "template B" << std::endl;
}