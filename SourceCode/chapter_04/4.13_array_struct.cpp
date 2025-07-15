#// arrstruc.cpp -- an array of structures
#include <iostream>

struct inflatable
{
    char name[20];
    float volume;
    double price;
};

int main()
{
    inflatable guests[5] =
    {
        {"xiongda", 0.1, 11.111},
        {"xionger", 0.2, 22.222},
        {"guangtouqiang", 0.32, 2.35},
        {"zhuzhuxia", 33.298, 342.55},
        {"ling", 77.432, 32387.001}
    };
    std::cout << "The gursts " << guests[0].name << " and " << guests[1].name
              << "\nhave a combined volume of "
              << guests[0].volume + guests[1].volume << " cubic feet.\n";

    return 0;
}