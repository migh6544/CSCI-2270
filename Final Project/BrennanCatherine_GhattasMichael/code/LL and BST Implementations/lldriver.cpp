#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "linkedlist.hpp"
using namespace std;
using namespace std::chrono;


int main(int argc, char const *argv[]) 
{
//LL class
MailTrackLL LL;


/* 4.1.1 */

//test data
int testdata[40000];

//time measurement for insert
float insert[400];

//time measurement for search
float search[400];


//read in 40000 test integers into testdata[]
ifstream test(argv[1]);
string temp;
int count = 0;
while(!test.eof())
{
    getline(test, temp, ',');
    testdata[count] = stof(temp);
    count++;
}
test.close();

//use for loop for whole set of repeating insert and search operations
for(int i=0; i < 400; i++)
{
/* 4.1.2 */

    // Get starting timepoint 
    auto start_insert = high_resolution_clock::now(); 

    //for loop to insert test data into ll in increments of 100 mails
    for (int j=100*i; j<(100*i + 100); j++)
    {
        //use linkedlist.cpp function to insert mail into ll at index j 
        LL.insertMail(testdata[j]);
    }

    // Get ending timepoint 
    auto stop_insert = high_resolution_clock::now(); 

    //calculate time duration of total operation
    auto duration_insert = duration_cast<nanoseconds>(stop_insert - start_insert);

    //calculate average time (in microseconds)
    float average_insert = (float)duration_insert.count()/ 100;
    insert[i]=average_insert;
    //cout << "inserttime for interation " << i << ": " << insert[i] << endl;




/* 4.1.3 */

    //array to hold random numbers
    int randoms[100];
    //number of random numbers increases by 100 with each iteration of the outer for loop 
    for (int k=0; k < 100; k++)
    {
        //generates a random number with range increasing by 100 with each iteration of the outmost for loop
        randoms[k]= rand() %100*(i+1);
    }


    // Get starting timepoint 
    auto start_search = high_resolution_clock::now(); 


    for (int m = 0; m < 100; m++)
    {
        LL.searchMail(testdata[randoms[m]]);
    }

    // Get ending timepoint 
    auto stop_search = high_resolution_clock::now(); 

    //calculate time duration of total operation
    auto duration_search = duration_cast<nanoseconds>(stop_search - start_search);

    //calculate average time (in microseconds)
    float average_search = (float)duration_search.count()/100;
    search[i]= average_search;
     //cout << "searchtime for interation " << i << ": " << search[i] << endl;
}

//write to file
ofstream output_LL("output_LL_B.csv");

//column labels 
output_LL << "Insert" << " , " << "Search" << endl;

//write data to output file
for (int n=0; n<400; n++)
{
    output_LL << insert[n] << " , " << search[n] << endl;

}
output_LL.close();
}