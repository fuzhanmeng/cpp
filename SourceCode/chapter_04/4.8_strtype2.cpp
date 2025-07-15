#include <iostream>
#include <string>

int main()
{
    std::string s1 = "penguin";
    std::string s2, s3;

    std::cout << "You can assign one string object to another: s2 = s1" << std::endl;
    s2 = s1;
    std::cout << "s1: " << s1 << ", s2: " << s2 << std::endl;

    std::cout << "You can assign a C-style string to a string object" << std::endl;
    std::cout << "s2 = \"buzzard\" " << std::endl;

    s2 = "buzzard";
    std::cout << "s2: " << s2 << std::endl;

    s3 = s1 + s2;
    std::cout << "s3: " << s3 << std::endl;
    std::cout << "You can append strings" << std::endl;

    s1 += s2;
    std::cout << "s1 += s2 yields s1 = " << s1 << std::endl;

    s2 += "for a day ";
    std::cout << "s2 += \" for a day \" yields s2 = " << s2 << std::endl;
    
    return 0;
}