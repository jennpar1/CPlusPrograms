//Jennifer Parnell
//CSC 231
//Project 3
//Using Binary Tree

#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>		// Used for file functions. 
#include "Word.h"
#include "BinaryTree.h"
#include "Node.h"

using namespace std;

void writeTextFile(Node * node);
void readTextFile();
void pressAnyKey();

BinaryTree wordlist;

int main()
{
	
	//Word word;
	/*wordlist->addNode(word);
	Word word2 = { "something", "testing"};
	wordlist->addNode(word2);
	Word word3 = { "victory", "testing" };
	wordlist->addNode(word3);*/

	readTextFile();
	wordlist.inOrder(wordlist.Root());
	wordlist.levelOrder(wordlist.Root());
	
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
			<< "\t1\tAdd word and meaning to list\n"
			<< "\t2\tEdit a word or meaning in list\n"
			<< "\t3\tFind and display word in list\n"
			<< "\t4\tView all words in list\n"
			<< "\t5\tShow flashcards\n"
			<< "\t6\tDelete a word\n"
			<< "\t7\tQuit the program\n"
			<< "---------------------------------------------------------------------\n\n"
			<< "Enter your choice : \n\n";

		// Get user choice and process.
		cin >> choice;
		switch (choice)
		{
		case 1: //Add word
		{
			string word;
			string meaning;
			cout << "Enter word: " << endl;
			cin >> word;
			cin.ignore();
			cout << "Enter meaning: " << endl;
			getline(cin, meaning);

			Word getData = { word, meaning };
			wordlist.addNode(getData);

			pressAnyKey();
			break;
		}
		case 2: //Edit word or meaning
		{
			string fword;
			cout << "Enter word to edit: " << endl;
			cin >> fword;
			wordlist.editNode(wordlist.Root(), fword);
			pressAnyKey();
			break;
		}
		case 3: //Find and display word
		{
			string word;
			cout << "Enter word to find: " << endl;
			cin >> word;
			wordlist.search(wordlist.Root(), word);
			pressAnyKey();
			break;	
		}
		case 4: //View all
		{
			wordlist.inOrder(wordlist.Root());
			pressAnyKey();
			break;
		}
		case 5:	//Show flashcards
		{
			bool keepGoing1 = true;
			while (keepGoing1)
			{
				cout << endl
					<< "---------------------------------------------------------------------\n"
					<< " Select an option from the menu below\n"
					<< " by entering the number of the choice\n"
					<< "---------------------------------------------------------------------\n"
					<< "\t1\tIn order traversal\n"
					<< "\t2\tPreOrder\n"
					<< "\t3\tPostOrder\n"
					<< "\t4\tRandom\n"
					<< "\t5\tReturn to other menu\n"
					<< "---------------------------------------------------------------------\n\n"
					<< "Enter your choice : \n\n";

				// Get user choice and process.
				cin >> choice;
				switch (choice)
				{
				case 1:
				{
					wordlist.flashcardsInOrder(wordlist.Root());
					pressAnyKey();
					break;
				}
				case 2:
				{
					wordlist.flashcardsPreOrder(wordlist.Root());
					pressAnyKey();
					break;
				}
				case 3:
				{
					wordlist.flashcardsPostOrder(wordlist.Root());
					pressAnyKey();
					break;
				}
				case 4:
				{
					wordlist.flashcardsRandom(wordlist.Root());
					pressAnyKey();
					break;
				}
				case 5:
				{
					keepGoing1 = false;
					pressAnyKey();
					break;
				}
				}
			}
		}
		case 6: //Delete a word
		{
			string fword;
			cout << "Enter word to delete. " << endl;
			cin >> fword;
			wordlist.deleteNode(wordlist.Root(), fword);
			pressAnyKey();
			break;
		}
		case 7: // Quit program.
		{
			keepGoing = false;		// Exit from menu loop and program.
			cout << "The program is now ending.\n";
			writeTextFile(wordlist.Root());
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


void pressAnyKey()
{
	cout << "Press any key to continue" << endl;
	_getch();
}

void writeTextFile(Node* node)
{
	// Step 1 - Open the "file" for output (writing) with constructor. 
	// The object here is a file handle which is used to write data from vector. ofstream is the output file stream
	ofstream wordTextFile("WordsFile.txt", ios::out);	//because opened at out file deletes previous. Could use ate= add to end
													// ios::out | ios::in | ios::ate allows you to write in, out and adding
													// Exit program if file was not created successfully. 

	if (!wordTextFile)
	{
		cerr << "File does not exist or could not be opened." << endl;
		exit(1);	// End program with errors.
	}


	// Step 2 - Write the data in the vector to the file.
	wordlist.writeTraversal(wordlist.Root(), wordTextFile);
	//int i = 0;
	//while (i < bookVector.size())
	//{
	//	// Write each element of array.
	//	wordTextFile << bookVector.at(i).getTitle() << '\t'
	//		<< bookVector.at(i).getAuthor() << '\t'
	//		<< bookVector.at(i).getYear();
	//	if (i < bookVector.size() - 1)
	//	{
	//		bookTextFile << endl;
	//	}
	//	// Display file writing work for demo purposes only.
	//	cout << "Written to file:\n   " << bookVector.at(i) << endl;
	//	i++;
	//}
	//cout << endl;

	// Step 3 - close file.
	wordTextFile.close();
}

//void writeTraversal(Node* node)
//{
//	ofstream wordTextFile;
//	if (node)
//	{
//		wordTextFile << node->key.print() << endl;
//		writeTraversal(node->left);
//		writeTraversal(node->right);
//
//	}
//}

void readTextFile()
{
	// Step 1 - Open the "file" for input (reading) with constructor. 
	// The object here is a file handle.  ifstream is the input file stream
	ifstream wordTextFile("WordsFile.txt", ios::in);
	// Exit program if file is not openable or found. 
	if (!wordTextFile)
	{
		cerr << "File could not be found or opened." << endl;
		exit(1);	// End program with errors.
	}

	string theWord, theMeaning;

	// Step 2 - read data, construct objects, and add to vector.
	while (!wordTextFile.eof())	//eof= end of file
	{
		// Get inputs from file.
		getline(wordTextFile, theWord, '\t');		// scans from the start of line to the first tab
		getline(wordTextFile, theMeaning, '\n');		// continues to scan and ends at the line
		//Word theWordMeaning(theWord, theMeaning);
		wordlist.addNode({ theWord, theMeaning });

	}
	cout << endl;
	
	// Step 3 - close file.
	wordTextFile.close();
}