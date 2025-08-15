// equal.cpp -- equality vs assignment

#include <iostream>

int main ()
{
    int quizscores[10] = { 20, 20, 20, 20, 20, 19, 20, 18, 20, 20};
 
    std::cout << "doing it right :" << std::endl;

    int i;
    
    for (i = 0; quizscores[i] == 20; i++)
        std::cout << "quiz " << i << " is a 20" << std::endl;
 
    std::cout << "doing it dangerously wrong" << std::endl;

    //  quizscores[i] = 20 all is true
    for (i = 0; quizscores[i] = 20; i++)
    {
        std::cout << "quiz " << i << "is a 20" << std::endl;
    }
    
    return 0;
}