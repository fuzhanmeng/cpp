// strc_ref.cpp -- using structure reference
#include <iostream>
#include <string>

struct free_throws
{
    std::string name;
    int made;
    int attempts;
    float percent;
};

void display(const free_throws& ft);
void set_pc(free_throws& ft);
free_throws& accumulate(free_throws& target, const free_throws& source);

int main()
{
    free_throws one = {"Ifelsa Branch", 13, 14};
    free_throws two = {"Andor Koott", 10, 16};
    free_throws three = {"Minnie", 7, 9};
    free_throws four = {"Whily", 5, 9};
    free_throws five = {"Long Long", 6, 14};
    free_throws team = {"Throwgoods", 0, 0};
    free_throws dup;

    set_pc(one);
    display(one);
    accumulate(team, one);
    display(team);

    // use return value as argument
    std::cout << "use return value as argument" << std::endl;
    display(accumulate(team, two));
    accumulate(accumulate(team, three), four);
    display(team);

    // use return value in assignment
    std::cout << "use return value as assignment" << std::endl;
    dup = accumulate(team, five);
    std::cout << "display team: \n";
    display(team);
    std::cout << "display dup after assignment: \n";
    display(dup);
    set_pc(four);

    // ill-advised assignment
    std::cout << "ill-advised assignment" << std::endl;
    accumulate(dup, five) = four;
    std::cout << "displaying dup after ill-advised assignment: \n";
    display(dup);
    return 0;
}

void display(const free_throws& ft)
{
    std::cout << "Name: " << ft.name << "\n";
    std::cout << "Made: " << ft.made << "\n";
    std::cout << "Attempts: " << ft.attempts << "\n";
    std::cout << "Percent: " << ft.percent << "\n";
}

void set_pc(free_throws& ft)
{
    if (ft.attempts != 0)
    {
        ft.percent = 100.0f * float(ft.made) / float(ft.attempts);
    }
    else
    {
        ft.percent = 0;
    }
}

free_throws& accumulate(free_throws& target, const free_throws& source)
{
    target.attempts += source.attempts;
    target.made += source.made;
    set_pc(target);
    return target;
}