// filefunc.cpp -- function with ostream& parameter
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>

void file_it(std::ostream& os, double fo, const double fe[], int n);
const int LIMIT = 5;

int main()
{
    std::ofstream fout;
    const char* fn = "ep-data.txt";
    fout.open(fn);
    if (!fout.is_open())
    {
        std::cout << "can't open " << fn << ". Bye.\n";
        exit(EXIT_FAILURE);
    }

    double objective;
    std::cout << "enter the focal length of your telescope objective in nm: ";
    std::cin >> objective;
    double eps[LIMIT];
    std::cout << "enter the focal lengths, in nm, of " << LIMIT << " eyepieces:\n";

    for (int i = 0; i < LIMIT; i++)
    {
        std::cout << "Eyepiece #" << i + 1 << ": ";
        std::cin >> eps[i];
    }

    file_it(fout, objective, eps, LIMIT);
    file_it(std::cout, objective, eps, LIMIT);

    std::cout << "Done\n";

    return 0;
}

void file_it(std::ostream& os, double fo, const double fe[], int n)
{
    // save intiial formatting state
    std::ios_base::fmtflags initial;
    initial = os.setf(std::ios_base::fixed, std::ios_base::floatfield);
    std::streamsize sz = os.precision(0);
    os << "Focal length of objective: " << fo << " mm\n";
    os.precision(1);
    os.width(12);
    os << "f.l eyepices";
    os.width(15);
    os << "magnification" << std::endl;

    for (int i = 0; i < n; i++)
    {
        os.width(12);
        os << fe[i];
        os.width(15);
        os << int(fo / fe[i] + 0.5) << std::endl;
    }

    // restore initial formatting state
    os.setf(initial, std::ios_base::floatfield);
    os.precision(sz);
}