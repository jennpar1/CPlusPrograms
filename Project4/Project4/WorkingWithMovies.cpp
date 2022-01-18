//Jennifer Parnell
//CSC 231
//Project 4
//Using Hash Table

#include <iostream>		// Used for input and output.
#include <fstream>		// Used for file input and output.
#include <cstring>
#include <conio.h>		// Used for getch().
#include <string>

#include "Movie.h"	

using namespace std;

// Hash table and hash file functions.
int initializeHashTable();
void writeBinary(int position, Movie theMovie);
void readBinary(int position, Movie& theMovie);	// Must pass by reference to keep read value.
void displayMovies();
void createMovies();
void addMovie(Movie theMovie);
int hashFunction(int key);
bool addable(int position);
int linearProbe(int position);
int quadraticProbe(int position);
void searchMovies(int key);
void removeMovie(int key);

// Miscellaneous functions.
void pressAnyKey();

// Hash table data.
const static int FILE_LENGTH = 37;	// Several collision/probing techniques work best if the length
									// of possible records is a prime number.
const static int REMOVED = -100;	// If this is to be placed in the key value, then it must be outside of valid range.
const static int EMPTY = -200;
const Movie placeHolderMovie("------------------------", "------------------------", 0, EMPTY);
const Movie removedMovie("XXXXXXXXXXXXXXXXXXXXXXXX", "XXXXXXXXXXXXXXXXXXXXXXXX", 0, REMOVED);
fstream hashFile;

int main()
{
	initializeHashTable();		// Initialize empty hash table with dummy records and display.	
	displayMovies();
	pressAnyKey();

	createMovies();				// Create the books used in this hash file demo.	
	displayMovies();
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
			<< "\t1\tAdd \n"
			<< "\t2\tSearch \n"
			<< "\t3\tRemove \n"
			<< "\t4\tDisplay \n"
			<< "\t5\tQuit the program \n"
			<< "---------------------------------------------------------------------\n\n"
			<< "Enter your choice : \n\n";

		// Get user choice and process.
		cin >> choice;
		switch (choice)
		{
		case 1: //Add movie
		{
			string title, director;
			int year, barCode;
			cout << "Enter title: " << endl;
			cin.ignore();
			getline(cin, title);
			cout << "Enter director: " << endl;
			getline(cin, director);
			cout << "Enter year: " << endl;
			cin >> year;
			cout << "Enter barCode: " << endl;
			cin >> barCode;
			char theTitle[80];
			strncpy_s(theTitle, title.c_str(), sizeof(title));
			char theDirector[40];
			strncpy_s(theDirector, director.c_str(), sizeof(director));
			addMovie(Movie(theTitle, theDirector, year, barCode));
			break;
		}
		case 2: //Search
		{
			int key = 0;
			cout << "Enter Bar Code number to search: " << endl;
			cin >> key;
			searchMovies(key);
			break;
		}
		case 3: //Remove
		{
			int key = 0;
			int number = 0;
			cout << "Enter Bar Code number to remove: " << endl;
			cin >> key;
			searchMovies(key);
			cout << "Enter Number of the movie to be remove: " << endl;
			cin >> number;
			removeMovie(number);
			break;
		}
		case 4: //Display
		{
			displayMovies();
			break;
		}
		case 5://Quit
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

	hashFile.close();
	return 0;
}

int initializeHashTable()
{
	// Open hash file.
	hashFile.open("MovieTable4.dat", ios::in | ios::out | ios::binary | ios::trunc);
	if (!hashFile)
	{
		cout << "Hash file error - file did not open successfully\n"
			<< "Program will end.\n";
		pressAnyKey();
		return 1;
	}
	// Initialize hash file (hash table) with empty values.	
	for (int position = 0; position < FILE_LENGTH; position++)
	{
		writeBinary(position, placeHolderMovie);
	}
	return 0;	// Successful completion of hash file intialization.
}

void writeBinary(int position, Movie theMovie)
{
	hashFile.seekp(position * sizeof(Movie));
	hashFile.write((char *)&theMovie, sizeof(Movie));
	hashFile.flush();

	hashFile.seekp(0 * sizeof(Movie));
}

void readBinary(int position, Movie& theMovie)
{
	hashFile.seekg(position * sizeof(Movie));
	hashFile.read((char *)&theMovie, sizeof(Movie));
}

void displayMovies()
{
	Movie tempMovie;	// Used to read object data in binary format from file.		
	cout << "Displaying hash table contents: \n";
	for (int position = 0; position < FILE_LENGTH; position++)
	{
		tempMovie = Movie("", "", 0, 0);
		readBinary(position, tempMovie);
		cout << "Display: " << position << ": " << tempMovie << endl;
	}
	cout << "End of hash table.\n";
}

// Create books for the bookshelf from the BBC's best books of the 21st Century.
void createMovies()
{
	addMovie(Movie("The Godfather", "Francis Ford Coppola", 1972, 123456789));
	addMovie(Movie("The Wizard of Oz", "Victor Fleming", 1939, 234567890));
	addMovie(Movie("The Shawshank Redemption", "Frank Darabont", 1994, 345678901));
	addMovie(Movie("Pulp Fiction", "Quentin Tarantino", 1994, 456789012));
	addMovie(Movie("Casablanca", "Michael Curtiz", 1942, 567890123));
	addMovie(Movie("E.T. The Extra-Terrestrial", "Steven Spielberg", 1982, 222233333));
	addMovie(Movie("Star Wars", "George Lucas", 1977, 678901234));
	addMovie(Movie("Back to the Future", "Robert Zemeckis", 1985, 789012345));
	addMovie(Movie("Raiders of the Lost Ark", "Steven Spielberg", 1081, 890123456));
	addMovie(Movie("Forrest Gump", "Robert Zemeckis", 1994, 901234567));
}

void addMovie(Movie theMovie)
{
	// Get hash value. It's best if the key is unique and if the keys' hash values are spread
	// evenly by the hash function.		
	int position = hashFunction(theMovie.getBarCode());
	if (!addable(position))
	{
		// Probe linearly as needed to get the correct final position.
		position = quadraticProbe(position);
	}
	// Add the book.
	writeBinary(position, theMovie);			// Insert into hash table.
	cout << "addMovie: theMovie: " << theMovie << endl;
}

int hashFunction(int key)
{
	int position = key % FILE_LENGTH;
	// cout for demo purposes only. 
	cout << "Hash value: " << position << endl;
	return position;
}

bool addable(int position)
{
	Movie movie;
	readBinary(position, movie);
	return (movie.getBarCode() == EMPTY);
}

int linearProbe(int position)
{
	do	// Increment position until an addable position is reached.
	{
		if (position < FILE_LENGTH - 1)
		{
			position++;
		}
		else	// If the end of the file is reached
		{		// restart in the first position.
			position = 0;
		}
	} while (!addable(position));
	return position;		// Return the appropriat position to add the book.
}

int quadraticProbe(int position)
{
	int counter = 0;
	do	// Increment position until an addable position is reached.
	{
		if (position < FILE_LENGTH)
		{
			position = (position + (counter * counter));

			while (position > FILE_LENGTH - 1)
			{
				position = (position - (FILE_LENGTH - 1));
			}
		}
		else if (position > FILE_LENGTH - 1)	// If the end of the file is reached
		{		// restart in the first position.
			position = 0;
		}
		counter++;
	} while (!addable(position));
	return position;
}

void searchMovies(int key)
{
	Movie tempMovie;	// Used to read object data in binary format from file.		
	cout << "Searching hash table contents: \n";
	for (int position = 0; position < FILE_LENGTH; position++)
	{
		tempMovie = Movie("", "", 0, 0);
		readBinary(position, tempMovie);

		if (key == tempMovie.getBarCode())
		{
			cout << "Display: " << position << ": " << tempMovie << endl;
		}
		
	}
	//cout << "End of hash table.\n";
}

void removeMovie(int key)
{
	Movie tempMovie;	// Used to read object data in binary format from file.		
	cout << "Remove content: \n";
	
	for (int position = 0; position < FILE_LENGTH; position++)
	{
		tempMovie = Movie("", "", 0, 0);
		readBinary(position, tempMovie);

		if (key == position)
		{
			tempMovie = removedMovie;
			writeBinary(position, tempMovie);
		}
	}
}

// Press any key to continue.
void pressAnyKey()
{
	cout << "Press any key to continue" << endl << endl;
	_getch();					// Waits and gets next character entered.		
}
