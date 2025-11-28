/**
 * @file exercises4_main
 * @brief practice
 * @author fzm
 * @date 2025-11-28
 */
#include <iostream>

#include "exercises4.h" // 假设这里包含了 Stack 类的声明

void show_stack_status(const Stack& st, const std::string& name)
{
    std::cout << "--- " << name << " Status ---" << std::endl;
    std::cout << name << " is_empty: " << (st.isempty() ? "Yes" : "No") << std::endl;
    std::cout << name << " is_full:  " << (st.isfull() ? "Yes" : "No") << std::endl;
    std::cout << "----------------------" << std::endl;
}

void test_pop(Stack& st, const std::string& name)
{
    Item popped_item;
    if (st.pop(popped_item))
    {
        std::cout << name << ": successfully popped: " << popped_item << std::endl;
    }
    else
    {
        std::cout << name << ": POP failed (Stack is empty)." << std::endl;
    }
}

int main()
{
    // 1. 构造函数演示 (st1 默认大小 MAX=10, st2 指定大小 5)
    std::cout << "======== 1. CONSTRUCTORS ========" << std::endl;
    Stack st1;
    Stack st2(5); // 假设我们让 st2 小一点，方便演示 isfull

    show_stack_status(st1, "st1 (MAX size)");
    show_stack_status(st2, "st2 (Size 5)");

    // 2. push() 演示
    std::cout << "\n======== 2. PUSH DEMO (Using st2) ========" << std::endl;
    for (int i = 1; i <= 6; ++i)
    {
        Item item_to_push = i * 10;
        if (st2.push(item_to_push))
        {
            std::cout << "st2: Pushed " << item_to_push << ". ";
        }
        else
        {
            std::cout << "st2: PUSH FAILED for " << item_to_push << " (Stack is full).";
        }
        show_stack_status(st2, "");
    }

    // 3. pop() 演示
    std::cout << "\n======== 3. POP DEMO (st2) ========" << std::endl;
    test_pop(st2, "st2"); // 应该弹出 50
    test_pop(st2, "st2"); // 应该弹出 40
    test_pop(st2, "st2"); // 应该弹出 30

    show_stack_status(st2, "st2 after 3 pops");

    // 4. 赋值运算符 (st2 = st1) 演示
    std::cout << "\n======== 4. ASSIGNMENT OPERATOR (st1 -> st2) ========" << std::endl;

    // st1 压入一些数据，保证与 st2 内容不同
    st1.push(101);
    st1.push(102);
    st1.push(103);
    show_stack_status(st1, "st1 Before Assignment");

    // 执行赋值：st2 应该获得 st1 的内容 (101, 102, 103) 和 MAX size
    st2 = st1;

    std::cout << "--- After st2 = st1 ---" << std::endl;
    show_stack_status(st2, "st2 After Assignment");

    // 验证 st2 是否正确复制了 st1 的内容 (LIFO: 103, 102, 101)
    std::cout << "Verifying st2 content after assignment:" << std::endl;
    test_pop(st2, "st2"); // 应该弹出 103
    test_pop(st2, "st2"); // 应该弹出 102

    // 5. 复制构造函数 (Stack st3 = st2) 演示
    std::cout << "\n======== 5. COPY CONSTRUCTOR (st3 = st2) ========" << std::endl;

    // st2 当前剩余 101
    show_stack_status(st2, "st2 Before Copy");

    Stack st3 = st2; // 调用复制构造函数

    show_stack_status(st3, "st3 After Copy");

    // 验证 st3 的内容：弹出 st3 的元素 (应该弹出 101)
    std::cout << "Verifying st3 content after copy:" << std::endl;
    test_pop(st3, "st3"); // 应该弹出 101

    // 验证 st2 和 st3 是独立的：st2 应该仍然包含 101
    std::cout << "Verifying st2 independence:" << std::endl;
    test_pop(st2, "st2"); // 应该弹出 101

    // 6. 栈空 pop 演示
    std::cout << "\n======== 6. EMPTY POP DEMO ========" << std::endl;
    test_pop(st2, "st2"); // 栈空，应该失败

    return 0;
}