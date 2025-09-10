// structfun.cpp -- functions with a structure argument

#include <iostream>
#include <cmath>

// polar coordinates
struct polar
{
    double distance; // distance from origin
    double angle;    // direction from origin
};

struct rect
{
    double x; // horizontal distance from origin
    double y; // vertical distance from origin
};
polar rect_to_polar(rect xypos);
void show_polar(polar pplace);

int main()
{
    rect rplace;
    polar pplace;

    std::cout << "Enter the x and y values: ";
    while (std::cin >> rplace.x >> rplace.y)
    {
        pplace = rect_to_polar(rplace);
        show_polar(pplace);

        std::cout << "Next two numbers (q to quit): ";
    }
    std::cout << "Done" << std::endl;\
    return 0;
}

// convert rectangular to polar coordinates
polar rect_to_polar(rect xy)
{
    polar answer;
    answer.distance = sqrt(xy.x * xy.x + xy.y * xy.y);
    answer.angle = atan2(xy.y, xy.x);

    return answer;

}

// show polar coordinates, converting angle to degrees
void show_polar(polar pplace)
{
    std::cout << "pplace.distance = " << pplace.distance << " pplace.angle = " << pplace.angle << std::endl;
}
