//Jennifer Parnell
//CSC 231
// Project 2

#include <iostream>
#include<string>

using namespace std;

// Preprocessing directives that prevents multiple definitions.
#ifndef Boat_H
#define Boat_H

// Class declaration for Book class.
class Boat
{
	// Declaring friends (friends have access to private data and operations).
	friend ostream &operator << (ostream& out, const Boat& theBoat);

public:

	Boat();

	Boat(string theMake, string theModel, int theYear);

	// Get and set methods or member functions.
	// Sometimes also called accessor and mutator functions.
	string getMake() const;
	string getModel() const;
	int getYear() const;
	void setMake(string theMake);
	void setModel(string theModel);
	void setYear(int theYear);

	void print();

private:

	string make;
	string model;
	int year;

};

#endif
