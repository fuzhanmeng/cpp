// strctptr.cpp -- functions with pointer to structure arguments
#include <iostream>
#include <cmath>

// structure templates
struct polar
{
    double distance;      // distance from origin
    double angle;         // direction from origin
};
struct rect
{
    double x;             // horizontal distance from origin
    double y;             // vertical distance from origin
};

// prototypes
void rect_to_polar(const rect * pxy, polar * pda);
void show_polar (const polar * pda);

int main()
{
    rect rplace;
    polar pplace;

    std::cout << "Enter the x and y values: ";
    while (std::cin >> rplace.x >> rplace.y)
    {
        rect_to_polar(&rplace, &pplace);
        show_polar(&pplace);
        std::cout << "Enter two numbers (enter q to quit)" << std::endl;
    }
    std::cout << "Done!" << std::endl;

    return 0;
}

void rect_to_polar(const rect* pxy, polar* pda)
{
    pda->distance = sqrt(pxy->x * pxy->x + pxy->y * pxy->y);
    pda->angle = atan2(pxy->y, pxy->x);
}

void show_polar(const polar* pda)
{
    std::cout << "distance =" << pda->distance << " angle = " << pda->angle << std::endl;
    
}
