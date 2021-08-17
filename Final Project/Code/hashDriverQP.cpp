#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "hashQP.hpp"

using namespace std;
using namespace std::chrono;

int main(int argc, char const *argv[])
{

    /* 4.1.1 */

    // creating an instance
    HashTable run = HashTable(40009);

    // initializing placeholder/counter for calculating number of collisions
    float numOfCol = 0;

    //test data
    int testdata[40000];

    //time measurement for insert
    float insert[400];

    //time measurement for search
    float search[400];

    //tracks average number of collisions per 100 insert operations
    float insert_collisions[400];

    //tracks average number of collisions per 100 insert operations
    float search_collisions[400];

    //read 40000 test integers into testdata[]
    ifstream test(argv[1]);
    string temp;
    int count = 0;
    while (!test.eof())
    {
        getline(test, temp, ',');
        testdata[count] = stof(temp);
        count++;
    }

    /* 4.1.2 */

    //use for loop for whole set of repeating insert and search operations
    for (int i = 0; i < 400; i++)
    {
        // Get starting timepoint
        auto start_insert = high_resolution_clock::now();
        //for loop to insert test data into ll in increments of 100 mails
        for (int j = 100 * i; j < ((100 * i) + 100); j++)
        {
            run.insertItem(testdata[j]);
        }

        // Get ending timepoint
        auto stop_insert = high_resolution_clock::now();

        //calculate time duration of total operation
        auto duration_insert = duration_cast<nanoseconds>(stop_insert - start_insert);

        //calculate average time (in microseconds)
        float average_insert = (float)duration_insert.count() / 100;
        insert[i] = average_insert;

        //calculate and store number of collisions per 100 insertions, then reset to 0
        numOfCol = run.getNumOfCollision();
        insert_collisions[i] = numOfCol;
        run.resetCollisions();
        numOfCol = 0;

        /* 4.1.3 */

        //array to hold random numbers
        int randoms[100];

        //number of random numbers increases by 100 with each iteration of the outer for loop
        for (int k = 0; k < 100; k++)
        {
            //generates a random number with range increasing by 100 with each iteration of the outmost for loop
            randoms[k] = rand() % 100 * (i + 1);
        }

        // Get starting timepoint
        auto start_search = high_resolution_clock::now();

        // run search function
        for (int m = 0; m < 100; m++)
        {
            run.searchItem(testdata[randoms[m]]);
        }

        // Get ending timepoint
        auto stop_search = high_resolution_clock::now();

        //calculate time duration of total operation
        auto duration_search = duration_cast<nanoseconds>(stop_search - start_search);

        //calculate average time (in microseconds)
        float average_search = (float)duration_search.count() / 100;

        search[i] = average_search;

        //calculate and store number of collisions per 100 searches, then reset to 0
        numOfCol = run.getNumOfCollision();
        search_collisions[i] = numOfCol;
        run.resetCollisions();
        numOfCol = 0;
    }

    //write to file
    ofstream output_HashLL("output_HashQP_B.csv");

    //column labels
    output_HashLL << "Insert_times" << "," << "Search_times" << "," << "num_insertCollisions" << "," << "num_searchCollisions" << endl;

    //write data to output file
    for (int n = 0; n < 400; n++)
    {
        output_HashLL << insert[n] << "," << search[n] << "," << insert_collisions[n] << "," << search_collisions[n] << endl;
    }
    output_HashLL.close();
}