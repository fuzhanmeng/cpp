/**
 * @file exercises1.cpp
 * @brief exercises1
 * @author fzm
 * @date 2025-11-28
 */


#include <cstring>
#include <iostream>

class Cow
{
public:
    Cow();
    Cow(const char* nm, const char* ho, double wt);
    Cow(const Cow& c);
    ~Cow();
    Cow& operator=(const Cow& c);
    void show() const;

private:
    char name[20];
    char* hobby;
    double weight;
};

Cow::Cow()
{
    name[0] = '\0';
    hobby = nullptr;
    weight = 0.0;
}

Cow::Cow(const char* nm, const char* ho, double wt)
{
    // copy name safely
    std::strncpy(name, nm, 19);
    name[19] = '\0';

    // copy hobby
    hobby = new char[std::strlen(ho) + 1];
    std::strcpy(hobby, ho);

    weight = wt;
}

// deep copy constructor
Cow::Cow(const Cow& c)
{
    std::strcpy(name, c.name);

    hobby = new char[std::strlen(c.hobby) + 1];
    std::strcpy(hobby, c.hobby);

    weight = c.weight;
}

Cow::~Cow() { delete[] hobby; }

Cow& Cow::operator=(const Cow& c)
{
    if (this == &c) return *this;

    delete[] hobby;

    hobby = new char[std::strlen(c.hobby) + 1];
    std::strcpy(hobby, c.hobby);

    std::strcpy(name, c.name);
    weight = c.weight;

    return *this;
}

void Cow::show() const
{
    std::cout << "name: " << name << std::endl;
    std::cout << "hobby: " << (hobby ? hobby : "(none)") << std::endl;
    std::cout << "weight: " << weight << std::endl;
}

int main()
{
    Cow cow1;
    Cow cow2("xiongda", "haha", 120);

    cow1.show();
    cow2.show();

    cow1 = cow2;
    cow1.show();
    cow2.show();

    return 0;
}
