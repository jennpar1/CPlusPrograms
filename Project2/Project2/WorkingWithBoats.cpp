//Jennifer Parnell
//CSC 231
// Project 2


/*
The purpose of this file is to demonstrate how to use objects.
*/

#include <iostream>		// Used for input and output.
#include <string>
#include <conio.h>		// Used for getch().

#include "Boat.h"		// Notice "" marks to identify our own header files.
#include "DoublyLinkedList.h"

using namespace std;

void pressAnyKey();

int main()
{
	// Declare, construct, and display list object.
	DoublyLinkedList boatList;
	boatList.displayList();
	Boat boat;
	pressAnyKey();

	// Display menu for user choice.
	int choice;
	bool keepGoing = true;
	while (keepGoing)
	{
		cout << endl
			<< "---------------------------------------------------------------------\n"
			<< " Select an option from the menu below\n"
			<< " by entering the number of the choice\n"
			<< "---------------------------------------------------------------------\n"
			<< "\t1\tEnter new boat\n"
			<< "\t2\tAdd boat to the front of the list\n"
			<< "\t3\tRemove the boat at the front of the list\n"
			<< "\t4\tAdd boat to the back of the list\n"
			<< "\t5\tRemove the boat at the back of the list\n"
			<< "\t6\tSearch for the list of boats by a year\n"
			<< "\t7\tDisplay all boats in list\n"
			<< "\t8\tEnd program\n"
			<< "---------------------------------------------------------------------\n\n"
			<< "Enter your choice : \n\n";

		// Get user choice and process.
		cin >> choice;
		switch (choice)
		{
			case 1: 
			{
				string make, model;
				int year;
				cout << "Enter make: " << endl;
				cin >> make;
				cout << "Enter model: " << endl;
				cin >> model;
				cout << "Enter year: " << endl;
				cin >> year;
				boat = { make, model, year };
			
			}
			case 2:
			{
				boatList.addFront(boat);
				break;
			}
			case 3:
			{
				boatList.removeFront();
			}
			case 4:
			{
				boatList.addBack(boat);
				break;
			}
			case 5:
			{
				boatList.removeBack();
				break;
			}
			case 6:
			{
				int searchYear;
				cout << "Enter the year to search for: \n";
				cin >> searchYear;
				boatList.searchList(searchYear);
				break;
			}
			case 7:	// Display book list.
			{
				boatList.displayList();
				pressAnyKey();
				break;
			}
			case 8: // Quit program.
			{
				keepGoing = false;		// Exit from menu loop and program.
				cout << "The program is now ending.\n";
				pressAnyKey();
				break;
			}
			default: // Catch all under construction items.
			{
				cout << "That option is currently not available\n";
				pressAnyKey();
				break;
			}
		}
	}

	// End program.	
	return 0;
}

// Press any key to continue.
void pressAnyKey()
{
	cout << "Press any key to continue" << endl << endl;
	_getch();					// Waits and gets next character entered.		
}
