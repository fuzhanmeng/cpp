/**
 * @file 12.11_queue.cpp
 * @brief Queue and Customer methods
 * @author fzm
 * @date 2025-11-26
 */

#include "12.10_queue.h"
#include <cstdlib>

Queue::Queue(int qs) :qsize(qs)
{
    front = rear = nullptr;
    items = 0;
}

Queue::~Queue()
{

}

bool Queue::isempty() const
{
    return items == 0;
}

bool Queue::isfull() const
{
    return items == qsize;
}

int Queue::queuecount() const
{
    return items;
}

bool Queue::enqueue(const Item& item)
{
    if (isfull())
    {
        return false;
    }

    Node* add = new Node;
    add->item = item;
    add->next = nullptr;
    items++;

    if (front == nullptr)
    {
        front = add;
        rear = add;
    }
    else
    {
        rear->next = add;
        rear = add;
    }

    return true;
}

bool Queue::dequeue(Item& item)
{
    if (isempty())
    {
        return false;
    }

    Node* temp = front;
    item = front->item;
    front = front->next;
    delete temp;
    items--;
    if (items == 0)
    {
        front = nullptr;
        rear = nullptr;
    }

    return true;
}

// customer method
void Customer::set(long when)
{
    processtime = std::rand() % 3 + 1;
    arrive = when;
}