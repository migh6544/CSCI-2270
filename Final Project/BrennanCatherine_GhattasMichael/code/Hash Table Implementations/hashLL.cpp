#include <iostream>
#include "hashLL.hpp"

using namespace std;


// Helper function to create new nodes
node *createNode(int key, node *next)
{
    node* temp = new node;
    temp->key = key;
    //shouldn't this be set to *next? 
    temp->next = nullptr;
    return temp;
}

// HashTable class constructor
HashTable::HashTable(int bsize)
{
    //bsize not used because we know our table size already
    tableSize = 40009;
    table = new node* [tableSize];
    numOfcolision = 0;
}

// function evaluates if insertion was successful
bool HashTable::insertItem(int key)
{
    int index = 0;
    node* head = nullptr;
    index = hashFunction(key);
    bool temp = false;

    // test if node is free
    if (table[index] == nullptr)
    {
        table[index] = createNode(key, nullptr);
        table[index]->key = key;
        temp = true;
    }
    // use hashing to find a free node (if available)
    else
    {
        head = createNode(key, nullptr);
        head->next = table[index];
        table[index] = head;
        temp = true;
        numOfcolision++;
    }
    return temp;
}

// hash function uses chainning to find index of available node
unsigned int HashTable::hashFunction(int key)
{
    int index = 0;
    index = key % tableSize;
    return index;
}

// function displays hash-table linked-list content
void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        cout << i << "|";
        node* temp = table[i];

        while (temp != nullptr)
        {
            cout << temp->key << " ";
            temp = temp->next;
        }
        cout << endl;
    }
}

// function provides the number of collisions took place during insertion
int HashTable::getNumOfCollision()
{
    return numOfcolision;
}

//resets number of collisions to zero
void HashTable::resetCollisions()
    {
        numOfcolision = 0;
    }


// funtion return a pointer to the location the value is at
node* HashTable::searchItem(int key)
{
    int index = hashFunction(key);
    node* temp = table[index];

    while (temp != nullptr)
    {
        if (temp->key == key)
        {
            return temp;
        }
        temp = temp->next;
        numOfcolision++;
    }
    return nullptr;
}