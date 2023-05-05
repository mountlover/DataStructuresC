/*
 * DoublyLinkedList - A perfectly generic doubly-linked list
 *
 *  Created on: Feb 24, 2009
 *      Author: Yama H
 */

/*
 * Traverses the list from head to tail
 * Usage:
 * DLLNode* handle;
 * DLL_TRAVERSAL(list, handle)
 * {
 *      [this code gets executed list->size times]
 *      [and handle points to the current node]
 * }
 */
#define DLL_TRAVERSAL(DLL, DLLNODE)										\
	for(DLLNODE=DLL->head; DLLNODE != NULL; DLLNODE = DLLNODE->next)

/*
 * Traverses the list from tail to head
 * Usage:
 * DLLNode* handle;
 * DLL_REVERSE_TRAVERSAL(list, handle)
 * {
 *      [this code gets executed list->size times]
 *      [and handle points to the current node]
 * }
 */
#define DLL_REVERSE_TRAVERSAL(DLL, DLLNODE)								\
	for(DLLNODE=DLL->tail; DLLNODE != NULL; DLLNODE = DLLNODE->prev)

/*
 * Uses two DLLNode*s and traverses the list in both directions at once
 * Usage:
 * DLLNode* frontPtr, *rearPtr;
 * DLL_DOUBLE_TRAVERSAL(list, frontPtr, rearPtr)
 * {
 *      [this code gets executed (list->size+1)/2 times]
 *      [frontPtr advances up the list, and rearPtr traces down it]
 * }
 */
#define DLL_DOUBLE_TRAVERSAL(DLL, FRONTPTR, REARPTR)					\
	int _i;																\
	for(FRONTPTR = DLL->head, REARPTR = DLL->tail, _i = 0;				\
		_i < (DLL->size+1)/2; _i++,										\
		FRONTPTR = FRONTPTR->next, REARPTR = REARPTR->prev)

/*
 * E's are long doubles by default since they allocate the most space of all
 * primitive types, therefore ensuring enough space for any other primitive
 * or pointer that could be cast into it.
 * To redefine the generics, just call #define GENERICS [type] before
 * importing DoublyLinkedList.h
 */
#ifndef GENERICS
#define GENERICS long double
#endif
typedef GENERICS E;

/*
 * A DLLNode (DoublyLinkedListNode) consists of a piece of data of type E
 * (which is really usually some other type cast into an E, which can also be a
 * pointer) and pointers to the next and previous DLLNodes in the list (NULL
 * if the node is a head or tail node). There is also a pointer to the list
 * in which this node is contained.
 */
struct DLLNode;
struct DoublyLinkedList;
typedef struct DLLNode
{
	E data;
	struct DLLNode* next;
	struct DLLNode* prev;
	struct DoublyLinkedList* list;
}DLLNode;

/*
 * A DoublyLinkedList consists of a pointer to the head node, a pointer to
 * the tail node, a size_t representing the number of elements currently in
 * the list, a short int determining whether or not the list should be
 * automatically sorted, and a custom compare function pointer that can
 * be implemented for defining a way of comparing E values.
 * This is handy for when E's are pointers to structs or other elements
 * whose values cannot be compared using '<' '>' and '=='.
 * The compare method should return 0 if val1 == val2, >0 if val1 > val2,
 * and <0 if val1 < val2.
 * (note: automatic sorting disables random insertion)
 * (important note: Use the DoublyLinkedList_create() function to allocate
 * a DoublyLinkedList, as just calling malloc() on windows machines does
 * not guarantee that DoublyLinkedList's members are null or zero.)
 */
typedef struct DoublyLinkedList
{
	DLLNode* head;
	DLLNode* tail;
	size_t size;
	short int sorted;
	int (*compare)(E val1, E val2);
}DoublyLinkedList;

/*
 * Initializes a pre-allocated List and creates first node.
 */
void DoublyLinkedList_initialize(DoublyLinkedList* dll, E data, short int autoSort);
/*
 * Allocates an empty DoublyLinkedList
 */
DoublyLinkedList* DoublyLinkedList_create();
/*
 * Adds an entry to the tail end of the List.
 */
int DoublyLinkedList_pushTail(DoublyLinkedList* dll, E data);
/*
 * Adds an entry to the tail end of the List.
 */
int DoublyLinkedList_pushHead(DoublyLinkedList* dll, E data);
/*
 * Pops and returns the tail off the list
 */
E DoublyLinkedList_popTail(DoublyLinkedList* dll);
/*
 * Pops and returns the head off the list
 */
E DoublyLinkedList_popHead(DoublyLinkedList* dll);
/*
 * Removes an element from the list and deallocates it.
 * Nonzero on failure.
 */
int DoublyLinkedList_remove(DLLNode* element);
/*
 * Retrieves the head node.
 */
DLLNode DoublyLinkedList_getHead(DoublyLinkedList* dll);
/*
 * Retrieves the tail node. Returns allocated memory if dll is null.
 */
DLLNode DoublyLinkedList_getTail(DoublyLinkedList* dll);
/*
 * Retrives the node after the current node. Returns the parameter if the
 * current node is the last entry (the tail).
 */
DLLNode DoublyLinkedList_getNext(DLLNode node);
/*
 * Retrieves the node before the current node. Returns the parameter if the
 * current node is the first entry (the head).
 */
DLLNode DoublyLinkedList_getPrev(DLLNode node);
/*
 * Retrieves the data from the node passed.
 */
E DoublyLinkedList_getData(DLLNode node);
/*
 * Sets the data in a specified node in the list to a specified value, and
 * updates the node passed in. Nonzero on failure.
 */
int DoublyLinkedList_setData(DLLNode* node, E data);
/*
 * Creates a new node from data and inserts it after handle in dll.
 * Nonzero on failure.
 */
int DoublyLinkedList_insertAfter(DLLNode* handle, E data);
/*
 * Creates a new node from data and inserts it before handle in dll.
 * Nonzero on failure.
 */
int DoublyLinkedList_insertBefore(DLLNode* handle, E data);
/*
 * Returns the number of size currently in the list.
 */
size_t DoublyLinkedList_getSize(DoublyLinkedList* dll);
/*
 * Searches for an element in the list and returns a pointer to it's node.
 * Returns NULL if not found.
 * note: this function uses DoublyLinkedList.compare iff it's been implemented
 */
DLLNode* DoublyLinkedList_find(DoublyLinkedList* dll, E value);
/*
 * Empties and deallocates a DoublyLinkedList
 */
void DoublyLinkedList_free(DoublyLinkedList* dll);
/*
 * Inserts an element such that the list remains in ascending order.
 * Only works if the list was initialized with the autoSort flag as true,
 * although calling sortedInsert on an empty list will set this flag to true.
 * note: this function uses DoublyLinkedList.compare iff it's been implemented
 */
int DoublyLinkedList_sortedInsert(DoublyLinkedList* dll, E value);
