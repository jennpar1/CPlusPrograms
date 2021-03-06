/*
Jennifer Parnell
CSC 231

The purpose of this program is to demonstrate binary search. We will create an array and fill it with random numbers and then search for
particular numbers in the array.

This program like most programs has a few bugs so be on the look out.
*/

#include <iostream>		// Used for input and output.
#include <conio.h>		// Used for getch().
#include <cstdlib>		// Used for random number generation.
#include <time.h>       // Used to seed the random number generator.

using namespace std;

// Forward declarations of functions.
void pressAnyKey();
void displayArray(int array[], int length);
void randomizeArray(int array[], int length);
int binarySearch(int array[], int arraySize, int target);
void searchAndDisplayItem(int array[], int arraySize, int target);
void selectionSort(int array[], int length);
int stepCount = 0;

// Global variables and constants.
const int LENGTH = 400;				// The length of our demonstration array.

									// Display values of array - each on their own line.
void displayArray(int array[], int length)
{
	int i = 0;
	while (i < length)
	{
		cout << i << "  " << array[i] << endl;
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
		array[i] = rand() % 100 + 1;		// A random number in the range of 1 to 100 is assigned.
		i++;
	} while (i < length);
}

int binarySearch(int array[], int arraySize, int target)
{
	int low = 0;
	int high = arraySize;
	stepCount +=3;			//2 for intializing the ints and 1 for while execution
	while (low + 1 < high)
	{
		// Choose the middle value of the array's search range. 
		int checkIndex = (low + high) / 2;	// Side note: Alternate code int checkIndex = ( (low + high) >> 1); // Shift binary decimal point - it's quicker.
		stepCount += 2;			//1 for previous statement and 1 for condition
		if (array[checkIndex] > target)	// Is the middle value higher or lower.
		{
			high = checkIndex;					// Cut search range in half by eliminating the greater than section.
			stepCount ++;			// for previous statement
		}
		else
		{
			low = checkIndex;					// Cut search range in half by eliminating the lower than section.
			stepCount++;			// 1 for previous statement
		}
		stepCount++;		//for while loop condition
	}
	// Does this save time to check for equality only at the end???
	stepCount++; // 1 for if statement
	if (array[low] == target)
	{
		return low;		// Return the index of the found target.
		stepCount++;	// 1 for previous statement
	}
	else
	{
		return -1;		// Indicate that the target was not found.
		stepCount++;	// 1 for previous statement
	}
}

void searchAndDisplayItem(int array[], int arraySize, int target)
{
	// Search for some selected values in our array and display results.
	int index = binarySearch(array, arraySize, target);
	if (index >= 0)
	{
		cout << "The value " << target << " was found at index " << index << ".\n";
	}
	else
	{
		cout << "The value " << target << " was not found in the array.\n";
	}
}

// Sort array.
void selectionSort(int array[], int length)
{
	int baseIndex, walker, minIndex, temp;
	// Loop: Traverse unsorted part of array, find minimum value, and swap minimum value into correct position. 
	for (baseIndex = 0; baseIndex < length - 1; baseIndex++)
	{
		// Set the initial minimum value as the first position in the unsorted part of the array.
		minIndex = baseIndex;
		// Loop: Check each index in unsorted part of array to find the minimum value.
		for (walker = baseIndex + 1; walker < length; walker++)
		{
			if (array[walker] < array[minIndex])	// Check for a new minimum.
			{
				minIndex = walker;
			}
		}
		if (minIndex != baseIndex)					// Swap to put minimum value in correct position.
		{
			temp = array[baseIndex];
			array[baseIndex] = array[minIndex];
			array[minIndex] = temp;
		}
	}
}

int main()
{
	cout << "BINARY SEARCH" << endl;
	pressAnyKey();
	
	int demo[LENGTH];					// Declare, initialize, and display array.
	displayArray(demo, LENGTH);
	pressAnyKey();						// Pause to take in the experience :-).
	
	randomizeArray(demo, LENGTH);		// Randomize values in array and display. 
	displayArray(demo, LENGTH);
	pressAnyKey();

	selectionSort(demo, LENGTH);
	displayArray(demo, LENGTH);
	pressAnyKey();
	
	// Search for some selected values in our array and display results.
	int index = binarySearch(demo, LENGTH, 37);
	if (index >= 0)
	{
		cout << "The value 37 was found at index " << index << ".\n";
	}
	else
	{
		cout << "The value 37 was not found in the array.\n";
	}

	// Use helper function for linear search.
	searchAndDisplayItem(demo, LENGTH, 43);
	searchAndDisplayItem(demo, LENGTH, 47);
	searchAndDisplayItem(demo, LENGTH, 53);

	cout << "The step count is: " << stepCount / 4 << endl;

	pressAnyKey();						// End main function and end program.
	return 0;
}

// Utility functions.
// Press any key to continue.
void pressAnyKey()
{
	cout << "Press any key to continue" << endl;
	_getch();					// Waits and gets next character entered.	
}

