// stack.h -- class definition for the stack ADT

#ifndef STACK_H_
#define STACK_H_

typedef unsigned long Item;

class Stack
{
public:
    Stack();
    ~Stack() = default;

    bool isempty() const;
    bool isfull() const;

    // add item to stack, if stack is full return false
    bool push(const Item& item);

    // pop item from stack, if stack is empty return false
    bool pop(Item& item);

private:
    static const int MAX = 10;
    Item items[MAX];
    int top;
};

#endif