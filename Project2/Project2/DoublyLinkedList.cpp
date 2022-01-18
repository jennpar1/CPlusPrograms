//Jennifer Parnell
//CSC 231
// Project 2

#include "DoublyLinkedList.h"
#include "Boat.h"

// This class is based on the definition on page 118
// in our textbook.

// Constructors. Only default constructor is needed for new empty list. 
DoublyLinkedList::DoublyLinkedList()
	: head(NULL) { }


// Destructor deletes object and code removes garbage.
DoublyLinkedList::~DoublyLinkedList()
{
	while (!empty())
	{
		removeFront();
	}
}

// Is list empty?
bool DoublyLinkedList::empty() const
{
	return (head == NULL);
}

// Get front node.
const Boat& DoublyLinkedList::front() const
{
	return head->boat;
}



// Add node to front.
void DoublyLinkedList::addFront(const Boat& e)
{
	Node* temp = new Node;			// Create new node.
	temp->boat = e;					// Store data.
	temp->previous = NULL;
	temp->next = head;				// Current head is now next of our new node.
	if (head != NULL)				// If list is not empty ... 
	{
		head->previous = temp;		// Set new node's previous to head
	}
	else							// Otherwise if the list is empty ... 
	{
		tail = temp;
	}
	head = temp;					// Our new node is now the new head.
}

// Remove node from front.
void DoublyLinkedList::removeFront()
{
	if (!empty())
	{
		Node* temp = head;				// temp saves the current head.
		head = temp->next;				// Our new head is the old head's next. 
		delete temp;					// Delete the previous head.
	}
}

void DoublyLinkedList::addBack(const Boat& e)
{
	Node* temp = new Node;			// Create new node.
	temp->boat = e;					// Store data.
	temp->next = NULL;
	temp->previous = tail;				// Current head is now next of our new node.
	if (tail != NULL)				// If list is not empty ... 
	{
		tail->previous = temp;		// Set new node's previous to head
	}
	else							// Otherwise if the list is empty ... 
	{
		head = temp;
	}
	tail = temp;					// Our new node is now the new head.
}

void DoublyLinkedList::removeBack()
{
	if (!empty())
	{
		Node* temp = tail;				// temp saves the current head.
		tail = temp->previous;				// Our new head is the old head's next. 
		delete temp;					// Delete the previous head.
	}
}

void DoublyLinkedList::searchList (int searchYear)
{
	Node * temp = head;
	if (!empty())
	{
		
		if (temp->boat.getYear() == searchYear)
		{
			cout << searchYear << " is in the list.\n";
		}
		else
		{
			temp->next;
			searchList(searchYear);
		}
	}
	else
	{
		cout << searchYear << " was not found in the list." << endl;
	}
}

void DoublyLinkedList::displayList() const
{
	if (!empty())
	{
		cout << "The following boats are in this list:\n";
		Node* temp = head;
		while (temp)	// temp evaluates to true if it is not NULL.
		{
			cout << temp->boat << endl;
			temp = temp->next;	// Move to the next node, which if it's NULL
		}						// will cause the loop to terminate.	   
		cout << endl;
	}
	else
	{
		cout << "There are no boats in this list.\n";
	}
}