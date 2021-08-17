#ifndef HASHQP_HPP
#define HASHQP_HPP

#include <string>

using namespace std;


// creating class HashTable to hold hash related data-members and member-functions
class HashTable
{
    int tableSize;
    int* table;
    int numOfcolision;

public:
    HashTable(int bsize);
    bool insertItem(int key);
    unsigned int hashFunction(int key);
    void printTable();
    int getNumOfCollision();
    void resetCollisions();
    int searchItem(int key);
};

#endif