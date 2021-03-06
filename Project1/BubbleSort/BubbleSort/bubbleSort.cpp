/*
The purpose of this program is to gather data to determine the algorithmic complexity of
selection sort. We will use data sets of __, ***
*/

#include <iostream>		// Used for input and output.
#include <conio.h>		// Used for getch().
#include <cstdlib>		// Used for random number generation.
#include <time.h>       // Used to seed the random number generator.

using namespace std;

// Press any key to continue.
void pressAnyKey()
{
	cout << "Press any key to continue" << endl;
	_getch();					// Waits and gets next character entered.	
}

// Display values of array - each on their own line.
void displayArray(int array[], int length)
{
	int i = 0;
	while (i < length)
	{
		cout << array[i] << " ";
		i++;
	}
	cout << endl;
}

// Give a random value to each element of the array.
void randomizeArray(int array[], int length)
{
	srand((unsigned)time(NULL));			// Seed random number generator. 

	int i = 0;
	do
	{
		array[i] = rand() % 100000 + 1;		// A random number in the range of 1 to 100,000 is assigned.
		i++;
	} while (i < length);
}

// Sort array.
void bubbleSort(int array[], int length)
{
	for (int left = 0; left < length; ++left)
		for (int right = 0; right < length - left - 1; ++right)
			if (array[right] > array[right + 1])
			{
				int temp = array[right];
				array[right] = array[right + 1];
				array[right + 1] = temp;
			}
}


void timeSort(int array[], int length)
{
	clock_t startTime, endTime;
	// Randomize values in array.
	randomizeArray(array, length);
	
	// Time array sort.
	startTime = clock();			// Get starting time.
	bubbleSort(array, length);	// Sort array.
	endTime = clock();				// Get ending time.

	//displayArray(array, length);								// Display algorithm's running time as difference between starting and ending time. 
	cout << "Bubble sort time for an array of "
		<< length
		<< ": "
		<< ((float)endTime - (float)startTime) / CLOCKS_PER_SEC * 1000
		<< " milliseconds."	// On my machine, CLOCKS_PER_SEC is equal to 1000 and 
							// thus milliseconds is the correct unit.
		<< endl;
}

int main()
{
	const int BASE_LENGTH = 20000;		// The base length of our test arrays.
	
										// Test 1: Time and sort array.	
	int test1[BASE_LENGTH];
	timeSort(test1, BASE_LENGTH);

	// Test 2: Time and sort array.	
	int test2[2 * BASE_LENGTH];
	timeSort(test2, 2 * BASE_LENGTH);

	// Test 3: Time and sort array.	
	int test3[3 * BASE_LENGTH];
	timeSort(test3, 3 * BASE_LENGTH);

	// Test 4: Time and sort array.	
	int test4[4 * BASE_LENGTH];
	timeSort(test4, 4 * BASE_LENGTH);

	// End program.
	pressAnyKey();
	return 0;
}