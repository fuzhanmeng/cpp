// nested.cpp -- nested loops and 2-D array

const int Cities = 5;
const int Years = 4;

#include <iostream>
int main()
{
    //  在现代 C++ 标准中，​​字符串常量（string literals）的类型是 const char[N]​​
    //  这是一个数组指针 里面的每个元素都是 const  char*类型
    const char *cities[Cities] = // 5座城市
        {
            "Gribble City", // 类型是 const char[13]
            "Gribbletown",  // 类型是 const char[12]
            "New Gribble",  // 类型是 const char[11]
            "San Gribble",  // 类型是 const char[11]
            "Gribble Vista" // 类型是 const char[13]
        };

    int maxtemps[Years][Cities] =
        {
            {96, 100, 87, 101, 105}, // values for maxtemps[0]
            {96, 98, 91, 107, 104},  // values for maxtemps[1]
            {97, 101, 93, 108, 107}, // values for maxtemps[2]
            {98, 103, 95, 109, 108}  // values for maxtemps[3]
        };

    std::cout << "Maximum temperatures for 2008 - 2001" << std::endl;

    for (int city = 0; city < Cities; city++)
    {
        std::cout << cities[city] << std::endl;
        for (int years = 0; years < Years; years++)
        {
            std::cout << maxtemps[years][city] << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << "=====================================" << std::endl;

    for (int year = 0; year < Years; year++)
    {
        for (int city = 0; city < Cities; city++)
        {
            std::cout << maxtemps[year][city] << "\t";
        }
        std::cout << std::endl;
    }
    

    return 0;
}