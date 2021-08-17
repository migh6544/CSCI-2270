//Collaboration between Catherine Brennan and Michael Ghattas
#ifndef HASHLL_HPP
#define HASHLL_HPP

#include <string>

using namespace std;


// creating struct for nodes
struct node
{
    // 
    int key;
    struct node* next;
};

// creating class HashTable to hold hash related data-members and member-functions
class HashTable
{
private:
    int tableSize;
    node* *table;
    int numOfcolision;

public:
    HashTable(int bsize);
    bool insertItem(int key);
    unsigned int hashFunction(int key);
    void printTable();
    int getNumOfCollision();
    void resetCollisions();
    node* searchItem(int key);
};

#endif
