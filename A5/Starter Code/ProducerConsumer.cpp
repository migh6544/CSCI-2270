#include "ProducerConsumer.hpp"
#include <iostream>

using namespace std;


ProducerConsumer::ProducerConsumer()
{
    queueFront = 0;
    queueEnd = 0;
}

bool ProducerConsumer::isEmpty()
{
    if (counter == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ProducerConsumer::isFull()
{
    if (counter == 20)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ProducerConsumer::enqueue(string item)
{
    if (isFull())
    {
        cout << "Queue full, cannot add new item" << endl;
    }
    else
    {
        queue[queueEnd] = item;
        queueEnd = (queueEnd + 1) % 20;
        counter++;
    }
}

void ProducerConsumer::dequeue()
{
    if (isEmpty())
    {
        cout << "Queue empty, cannot dequeue an item" << endl;
    }
    else
    {
        queue[queueFront] = "";
        queueFront = (queueFront + 1) % 20;
        counter--;
    }
}

string ProducerConsumer::peek()
{
    if (isEmpty())
    {
        cout << "Queue empty, cannot peek" << endl;
        return "";
        ;
    }
    else
    {
        return queue[queueFront];
    }
}

int ProducerConsumer::queueSize() //changed
{
    if (isEmpty())
    {
        return 0;
    }
    else
    {
        return counter;
    }
}