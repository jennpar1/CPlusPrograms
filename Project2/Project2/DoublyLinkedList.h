

#include "Node.h"

// This class is based on the definition on page 118
// in our textbook.

class DoublyLinkedList
{
public:
	DoublyLinkedList();				// Empty list constructor.
	~DoublyLinkedList();			// Destructor.
	bool empty() const;				// Is list empty?
	const Boat& front() const;		// Get front element in list.
	void addFront(const Boat& e);	// Add to front of list.
	void removeFront();				// Remove front item list.
	void addBack(const Boat& e);
	void removeBack();
	void searchList(int searchYear);
	void displayList() const;		// Display list of books.
private:
	Node* head;						// Pointer to the head of list
	Node* tail;
};

