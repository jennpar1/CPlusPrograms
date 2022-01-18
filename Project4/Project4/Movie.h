//Jennifer Parnell
//CSC 231
//Project 4
//Using Hash Table

using namespace std;

// Preprocessing directives that prevents multiple definitions.
#ifndef Book_H
#define Book_H

// Good resource for class definition with strings to be used for 
// binary file: https://www.youtube.com/watch?v=P7XGOBoVzW4

class Movie
{
	// Data attributes.
	char title[80];
	char director[40];
	int year;
	int barCode;

	// Declaring friends.
	friend ostream &operator << (ostream& out, const Movie& theBook);
public:
	Movie();
	Movie(char *theTitle, char *theDirector, int theYear, int theBarCode);
	void print();

	// Get and set methods or member functions.	
	string getTitle() const;
	string getDirector() const;
	int getYear() const;
	int getBarCode() const;
	void setTitle(char *theTitle);
	void setDirector(char *theDirector);
	void setYear(int theYear);
	void setBarCode(int theBarCode);
};

#endif