/**
 * @file exercises4
 * @brief practice
 * @author fzm
 * @date 2025-11-28
 */
#include "exercises4.h"

Stack::Stack(int n)
{
    items = new Item[n];
    top = 0;
    size = 0;
}

Stack::Stack(const Stack& st)
{
    size = st.size;
    top = st.top;
    items = new Item[size];
    for (int i = 0; i < top; i++)
    {
        items[i] = st.items[i];
    }
}

Stack& Stack::operator=(const Stack& st)
{
    if (this == &st)
    {
        return *this;
    }

    delete[] items;
    size = st.size;
    top = st.top;
    items = new Item[size];
    for (int i = 0; i < top; i++)
    {
        items[i] = st.items[i];
    }

    return *this;
}

Stack::~Stack() { delete[] items; }

bool Stack::isempty() const
{
    if (top == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Stack::isfull() const
{
    if (top == size)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Stack::push(const Item& item)
{
    if (isfull())
    {
        return false;
    }
    else
    {
        items[top] = item;
        top++;
        return true;
    }
}

bool Stack::pop(Item& item)
{
    if (isempty())
    {
        return false;
    }
    top--;
    item = items[top];
    return true;
}