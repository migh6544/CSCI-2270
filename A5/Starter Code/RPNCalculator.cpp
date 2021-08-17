#include "RPNCalculator.hpp"

using namespace std;

RPNCalculator::RPNCalculator()
{
    stackHead = nullptr;
}

RPNCalculator::~RPNCalculator()
{
    while (!isEmpty())
    {
        pop();
    }
    stackHead = nullptr;
}

bool RPNCalculator::isEmpty()
{
    if (stackHead == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void RPNCalculator::push(float num)
{
    if (stackHead == nullptr)
    {
        stackHead = new Operand;
        stackHead->number = num;
        stackHead->next = nullptr;
    }
    else
    {
        Operand *temp = stackHead;
        stackHead = new Operand;
        stackHead->number = num;
        stackHead->next = temp;
    }
}

void RPNCalculator::pop()
{
    if (stackHead == nullptr)
    {
        cout << "Stack empty, cannot pop an item." << endl;
        return;
    }
    else
    {
        stackHead = stackHead->next;
    }
}

Operand* RPNCalculator::peek()
{
    if (stackHead == nullptr)
    {
        cout << "Stack empty, cannot peek." << endl;
        return nullptr;
    }
    else
    {
        return stackHead;
    }
}

bool RPNCalculator::compute(string symbol)
{
    if (isEmpty())
    {
        cout << "err: not enough operands" << endl;
        return false;
    }
    else if(stackHead->next == nullptr)
    {
        cout << "err: not enough operands" << endl;
        return false;
    }
    else
    {
        float sh = stackHead->number;
        float shn = stackHead->next->number;
        if (symbol == "+")
        {
            pop();
            pop();
            push(sh + shn);
            return true;
        }
        if (symbol == "*")
        {
            pop();
            pop();
            push(sh * shn);
            return true;
        }
        else
        {
            cout << "err: invalid operation" << endl;
            return false;
        }
    }
}