//  sumafile.cpp -- functions with an array argument
#include <iostream>
#include <fstream> // file I/O support
#include <cstdlib> // support for exit()

const int Size = 60;
int main()
{
    char filename[Size];
    std::ifstream inFile;
    std::ofstream outFile;

    std::cout << "Enter name of data file: ";
    std::cin.getline(filename, Size);
    inFile.open(filename); // associate inFile with a file

    if (!inFile.is_open()) //  failed to open file
    {
        std::cout << "Could not open the file " << filename << std::endl;
        std::cout << "program terminating.\n";
        exit(EXIT_FAILURE);
    }

    double value;
    double sum = 0.0;
    int count = 0;

    inFile >> value;      // get first value
    while (inFile.good()) // while input good and not at EOF
    {
        ++count;         // one more item read
        sum += value;    // calculate running total
        inFile >> value; // get next value
    }
    if (inFile.eof())
        std::cout << "end of file reached.\n";
    else if (inFile.fail())
        std::cout << "Input terminated by data mismatch.\n";
    else
        std::cout << "Input terminated for unknown reason.\n";

    if (0 == count)
    {
        std::cout << "No data processed.\n";
    }
    else
    {
        std::cout << "Items read: " << count << std::endl;
        std::cout << "Sum: " << sum << std::endl;
        std::cout << "Average: " << sum / count << std::endl;
    }
}