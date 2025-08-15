// assgn_st.cpp --> assigning structures
// Use a structure to assign values ​​to another structure
#include <iostream>

struct inflatable
{
    std::string name;
    float volume;
    double price;
};

int main()
{
    inflatable bouquet =
        {
            "sunflowers",
            0.20,
            12.49
        };

    inflatable choice;

    std::cout << "bouquet: " << bouquet.name << "for $";
    std::cout << bouquet.price << std::endl;

    choice = bouquet; // assign one structure to another
    std::cout << "choice: " << choice.name << "for $";
    std::cout << choice.price << std::endl;

    return 0;
}
