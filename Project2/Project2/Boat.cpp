//Jennifer Parnell
//CSC 231
// Project 2

#include "Boat.h"

Boat::Boat()
{
	setMake("");
	setModel("");
	setYear(0);

}

Boat::Boat(string theMake, string theModel, int theYear)
{
	setMake(theMake);
	setModel(theModel);
	setYear(theYear);
}

string Boat::getMake() const
{
	return make;
}

string Boat::getModel() const
{
	return model;
}

int Boat::getYear() const
{
	return year;
}

void Boat::setMake(string theMake)
{
	make = theMake;
}
void Boat::setModel(string theModel)
{
	model = theModel;
}
void Boat::setYear(int theYear)
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

void Boat::print()
{
	cout <<  "Make: " << make << " Model: " << model << " Year: " << year;
}

ostream &operator << (ostream& out, const Boat& theBoat)
{
	out << "The boat is: " << theBoat.year << " " <<theBoat.make << " " << theBoat.model;
	return out;
}
