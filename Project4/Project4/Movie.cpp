//Jennifer Parnell
//CSC 231
//Project 4
//Using Hash Table

#include <iostream>		// Used for input and output.
#include <fstream>		// Used for file input and output.

#include "Movie.h"		// Notice "" marks to identify our own header files.

using namespace std;

///////////////////////
// Constructors.
Movie::Movie()
{
	setTitle("");
	setDirector("");
	setYear(0);
	setBarCode(0);
}

Movie::Movie(char *theTitle, char *theDirector, int theYear, int theBarCode)
{
	setTitle(theTitle);
	setDirector(theDirector);
	setYear(theYear);
	setBarCode(theBarCode);
}

///////////////////////
// Get and set methods.

string Movie::getTitle() const
{
	return title;
}

string Movie::getDirector() const
{
	return director;
}

int Movie::getYear() const
{
	return year;
}

int Movie::getBarCode() const
{
	return barCode;
}

void Movie::setTitle(char *theTitle)
{
	strcpy_s(title, theTitle);		// strcpy has been deprecated. _s functions are more secure variants.
}

void Movie::setDirector(char *theDirector)
{
	strcpy_s(director, theDirector);
}

void Movie::setYear(int theYear)
{
	if (theYear < 0)
	{
		year = 0;
	}
	else
	{
		year = theYear;
	}
}

void Movie::setBarCode(int theBarCode)
{
	// ISBN's must be 9 digit positive numbers or negative numbered flag conditions.
	if ((theBarCode < 100000000) && (theBarCode > 0))
	{
		barCode = 0;
	}
	else
	{
		barCode = theBarCode;
	}
}

///////////////////////
// Utility functions.

void Movie::print()
{
	cout << title << " published in " << year << " by " << director << " (Bar Code: " << barCode << ")" << endl;
}

ostream &operator << (ostream& out, const Movie& theMovie)
{
	out << theMovie.title << " by " << theMovie.director << " released in " << theMovie.year;
	return out;
}