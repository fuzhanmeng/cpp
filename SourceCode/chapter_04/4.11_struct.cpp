#include <iostream>

struct inflatable
{
    char name[20];
    float volume;
    double price;
};

int main()
{
    inflatable guest =
        {
            "Glorious Gloria",
            1.88,
            29.99
        };

    inflatable pal =
        {
            "Audacious Arthur",
            3.12,
            32.99
        };

    std::cout << "Expand your guest list with: " << guest.name;
    std::cout << " and " << pal.name << std::endl;

    std::cout << "You can have both for $";
    std::cout << guest.price + pal.price << std::endl;

    std::cout << guest.volume + pal.volume << std::endl;

    struct example
    {
        std::string name;
        double volume;
        float price;
    };

    example e;
    e.name = "xiongda";
    e.volume = 1.11;
    e.price = 2.312;
    std::cout << e.name << std::endl
              << e.price << std::endl
              << e.volume << std::endl;

    return 0;
}