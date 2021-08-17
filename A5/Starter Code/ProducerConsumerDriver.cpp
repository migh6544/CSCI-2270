/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}
// Use getline for reading
int main(int argc, char const *argv[])
{
	int input = 0;
	ProducerConsumer test;
	bool run = true;
	while (run == true)
	{
		string inPut = "";
		menu();
		getline(cin, inPut);
		input = stoi(inPut);
		switch (input)
		{
			case 1:
				cout << "Enter the number of items to be produced:" << endl;
				getline(cin, inPut);
				input = stoi(inPut);
				for (int i = 0; i < input; i++)
				{
					cout << "Item" << (i + 1) << ":" << endl;
					getline(cin, inPut);
					test.enqueue(inPut);
				}
				break;

			case 2:
				cout << "Enter the number of items to be consumed:" << endl;
				getline(cin, inPut);
				input = stoi(inPut);
				if (input > test.queueSize())
				{
					int temp = test.queueSize();
					for (int i = 0; i < temp; i++)
					{
						cout << "Consumed: " << test.peek() << endl;
						test.dequeue();
					}
					cout << "No more items to consume from queue" << endl;
				}
				else
				{
					for (int i = 0; i < input; i++)
					{
						cout << "Consumed: " << test.peek() << endl;
						test.dequeue();
					}
				}

				break;

			case 3:
				cout << "Number of items in the queue:" << test.queueSize() << endl;
				run = false;
				break;

			default:
				break;
		}
	}
}
