/**
 * @file 12.12_bank.cpp
 * @brief using the Queue interface
 * @author fzm
 * @date 2025-11-26
 */

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "12.10_queue.h"

bool newcustomer(double x); // is there a new customer?

const int MIN_PER_HR = 60;

int main()
{
    // setting things up
    std::srand(std::time(0));

    std::cout << "case study: bank of heather automatic teller" << std::endl;
    std::cout << "enter maximum size if queue: ";

    int qs;
    std::cin >> qs;
    Queue line(qs);

    std::cout << "enter the number of simulation hours: ";
    int hours;
    std::cin >> hours;

    // simulation will run 1 cycle per minute
    long cyclelimit = MIN_PER_HR * hours;

    std::cout << "enter the average number of customer per hour: ";
    double perhour;
    std::cin >> perhour;
    double min_per_cust;
    min_per_cust = MIN_PER_HR / perhour;

    Item temp;          //  new customer data
    long turnaways = 0; //  turned away by full queue
    long customers = 0; //  joined the queue
    long served = 0;    //  served during the simulation
    long sum_line = 0;  //  cumulative line length
    int wait_time = 0;  //  time until autoteller is free
    long line_wait = 0; //  cumulative time in line

    // running the simulation
    for (int cycle = 0; cycle < cyclelimit; cycle++)
    {
        if (newcustomer(min_per_cust))
        {
            if (line.isfull())
            {
                turnaways++;
            }
            else
            {
                customers++;
                temp.set(cycle);
                line.enqueue(temp);
            }
        }

        if (wait_time <= 0 && !line.isempty())
        {
            line.dequeue(temp);
            wait_time = temp.ptime();
            line_wait += cycle - temp.when();
            served++;
        }

        if (wait_time > 0)
        {
            wait_time--;
        }
        sum_line += line.queuecount();
    }

    // reporting results
    if (customers > 0)
    {
        std::cout << "customers accepted: " << customers << std::endl;
        std::cout << "  customers served: " << served << std::endl;
        std::cout << "         turnaways: " << turnaways << std::endl;
        std::cout << "average queue size: ";
        std::cout.precision(2);
    }
    else
    {
        std::cout << "No customer!" << std::endl;
    }

    std::cout << "Done!" << std::endl;
}

//  x = average time, in minutes, between customers
//  return value is true if customer shows up this minute
bool newcustomer(double x) { return (std::rand() * x / RAND_MAX < 1); }
