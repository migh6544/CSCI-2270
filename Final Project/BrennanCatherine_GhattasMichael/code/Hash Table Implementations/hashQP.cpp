#include <iostream>
#include "hashQP.hpp"

using namespace std;


// HashTable class constructor
HashTable::HashTable(int bsize)
{
    tableSize = 40009;
    numOfcolision = 0;
    table = new int[tableSize];

    for (int i = 0; i < tableSize; i++)
    {
        table[i] = -1;
    }
}

// function evaluates if insertion was successfull
bool HashTable::insertItem(int key)
{
    int index = hashFunction(key);
    bool completed = false;
    if (table[index] != -1)
    {
        completed = false;
    }
    else
    {
        table[index] = key;
        completed = true;
    }
    return completed;
}

// hash function uses open addressing to find an available free index
unsigned int HashTable::hashFunction(int key)
{
    int index = -1;
    for (int i = 0; i < tableSize; i++)
    {
        index = (key + ((i)^2)) % tableSize;
        if (table[index] == -1)
        {
            return index;
        }
        numOfcolision++;
    }
    return index;
}

// function displays hash-table array content
void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        cout << i << " | " << table[i] << endl;
    }
    cout << endl;
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
    
// funtion evaluates of the value has been found in the array
int HashTable::searchItem(int key)
{
    int index = -1;
    for (int i = 0; i < tableSize; i++)
    {
        index = (key + (i) ^ 2) % tableSize;
        if (table[index] == key || table[index] == -1)
        {
            return index;
        }
        numOfcolision++;
    }
    return index;
}