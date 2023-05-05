/*
 * CircularDoublyLinkedList.h
 *
 *  Created on: Apr 2, 2010
 *      Author: Yama H
 */

/*
 * E's are long doubles because they allocate the most space of all primitive
 * types, therefore ensuring enough space for any other type that could be
 * cast into it.
 */
typedef long double E;
/*
 * A CDLLNode (CircularDoublyLinkedListNode) consists of a piece of data of type E
 * (which is really usually some other type cast into an E, and can also be a
 * pointer) and pointers to the next and previous CDLLNodes in the list (NULL
 * if the node is a head or tail node.
 */
typedef struct
{
	E data;
	void* next;
	void* prev;
}CDLLNode;
/*
 * A CircularDoublyLinkedList is just a head Node, a pointer to a tail node, and an int
 * representing the amount of elements in the list. The head node is not a
 * pointer because it's value never changes unless the list is emptied.
 */
typedef struct
{
	CDLLNode head;	// the head isn't a pointer, but the tail is,
	CDLLNode* tail;	// because the head is static and the tail is dynamic
	int elements;
}CircularDoublyLinkedList;

/*
 * Initializes List and creates first node.
 */
void CircularDoublyLinkedList_initialize(CircularDoublyLinkedList* dll, E data);
/*
 * Initializes an empty List.
 */
void CircularDoublyLinkedList_init(CircularDoublyLinkedList* dll);
/*
 * Retrieves the data from the node passed.
 */
E CircularDoublyLinkedList_getData(CDLLNode node);
/*
 * Retrives the node after the current node. Returns the parameter if the
 * current node is the last entry (the tail).
 */
CDLLNode CircularDoublyLinkedList_getNext(CDLLNode node);
/*
 * Retrieves the node before the current node. Returns the parameter if the
 * current node is the first entry (the head).
 */
CDLLNode CircularDoublyLinkedList_getPrev(CDLLNode node);
/*
 * Sets the data in a specified node in the list to a specified value, and
 * updates the node passed in. Nonzero on failure.
 */
int CircularDoublyLinkedList_setData(CircularDoublyLinkedList* dll, CDLLNode* node, E data);
/*
 * Adds an entry to the List.
 */
void CircularDoublyLinkedList_addEntry(CircularDoublyLinkedList* dll, E data);
/*
 * Removes an entry from the list. Nonzero if list is empty.
 */
int CircularDoublyLinkedList_removeEntry(CircularDoublyLinkedList* dll);
/*
 * Retrieves the head node.
 */
CDLLNode CircularDoublyLinkedList_getHandle(CircularDoublyLinkedList* dll);
/*
 * Returns 1 if node1 is identical to node2 and 0 if not.
 */
int CircularDoublyLinkedList_equals(CDLLNode node1, CDLLNode node2);
/*
 * Returns the number of elements currently in the list.
 */
int CircularDoublyLinkedList_getElements(CircularDoublyLinkedList* dll);
