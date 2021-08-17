#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;


int main(int argc, char const *argv[])
{


    //test data
    int testdata[40000];

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

     //write to file
    ofstream output("dataSetB_transform.csv");

    //write data to output file
    for (int n = 0; n < 40000; n++)
    {
        output << testdata[n] << endl;
    }
    output.close();
}