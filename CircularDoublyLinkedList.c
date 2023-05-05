/*
 * CircularDoublyLinkedList.c
 *
 *  Created on: Apr 2, 2010
 *      Author: Yama H
 */

#include <stdlib.h>
#include <string.h>

/*
 * E's are long doubles because they allocate the most space of all primitive
 * types, therefore ensuring enough space for any other type that could be
 * cast into it.
 */
typedef long double E;

/*
 * A CDLLNode (CircularDoublyLinkedListNode) consists of a piece of data of type E
 * (which is really usually some other type cast into an E, and can also be a
 * pointer) and pointers to the next and previous DLLNodes in the list (NULL
 * if the node is a handle or tail node.
 */
typedef struct
{
	E data;
	void* next;
	void* prev;
}CDLLNode;

/*
 * A CircularDoublyLinkedList is just a handle Node, a pointer to a tail node, and an int
 * representing the amount of elements in the list. The handle node is not a
 * pointer because it's value never changes unless the list is emptied.
 */
typedef struct
{
	CDLLNode* handle;
	int elements;
}CircularDoublyLinkedList;

/*
 * Initializes List and creates first node.
 */
void CircularDoublyLinkedList_initialize(CircularDoublyLinkedList* cdll, E data)
{
	if(cdll == NULL) return;
	(*cdll).elements = 1;
	(*cdll).handle = (CDLLNode*)malloc(sizeof(CDLLNode));
	(*(*cdll).handle).data = data;
	(*(*cdll).handle).prev = (*cdll).handle;
	(*(*cdll).handle).next = (*cdll).handle;
}
/*
 * Initializes an empty List.
 */
void CircularDoublyLinkedList_init(CircularDoublyLinkedList* cdll)
{
	if(cdll == NULL) return;
	(*cdll).elements = 0;
	(*(*cdll).handle).data = (E)0;
	(*(*cdll).handle).prev = NULL;
	(*(*cdll).handle).next = NULL;
}
/*
 * Adds an entry to the List.
 */
void CircularDoublyLinkedList_addEntry(CircularDoublyLinkedList* cdll, E data)
{
	if(cdll == NULL) return;
	if((*cdll).elements == 0)
		CircularDoublyLinkedList_initialize(cdll, data);
	else if((*cdll).elements == 1)
	{
		CDLLNode* tmpNode = malloc(sizeof(CDLLNode));
		(*tmpNode).data = data;
		(*tmpNode).next = (*cdll).handle;
		(*tmpNode).prev = (*cdll).handle;
		(*(*cdll).handle).next = tmpNode;
		(*(*cdll).handle).prev = tmpNode;
		(*cdll).elements++;
	}
	else
	{
		CDLLNode* tmpNode = malloc(sizeof(CDLLNode));
		(*tmpNode).data = data;
		(*tmpNode).next = (*cdll).handle;
		(*tmpNode).prev = (*(*cdll).handle).prev;
		(*(*cdll).handle).prev = tmpNode;
		(*(CDLLNode*)(*tmpNode).prev).next = tmpNode;
		(*cdll).elements++;
	}
	return;
}
/*
 * Removes whichever value is currently the handle from the list.
 * Nonzero if cdll is empty or null.
 */
int CircularDoublyLinkedList_removeEntry(CircularDoublyLinkedList* cdll)
{
	if(cdll == NULL)
		return 1;
	if((*cdll).elements == 0)
		return 1;
	if((*cdll).elements == 1)
	{
		free((*cdll).handle);
		CircularDoublyLinkedList_init(cdll);
		return 0;
	}
	(*(CDLLNode*)(*(*cdll).handle).next).prev = (*(*cdll).handle).prev;
	(*(CDLLNode*)(*(*cdll).handle).prev).next = (*(*cdll).handle).next;
	void* ptr = (*(*cdll).handle).next;
	free((*cdll).handle);
	(*cdll).handle = ptr;
	(*cdll).elements--;
	return 0;
}
/*
 * Retrieves the handle node. Returns 0 if cdll is null.
 */
CDLLNode* CircularDoublyLinkedList_getHandle(CircularDoublyLinkedList* cdll)
{
	if(cdll == NULL) return NULL;
	return (*cdll).handle;
}
/*
 * Retrives the node after the current node. Returns the parameter if the
 * current node is the last entry (the tail).
 */
CDLLNode CircularDoublyLinkedList_getNext(CDLLNode node)
{
	if(node.next == NULL)
	{
		return node;
	}
	return *((CDLLNode*)node.next);
}
/*
 * Retrieves the node before the current node. Returns the parameter if the
 * current node is the first entry (the handle).
 */
CDLLNode CircularDoublyLinkedList_getPrev(CDLLNode node)
{
	if(node.prev == NULL)
		return node;
	return *((CDLLNode*)node.prev);
}
/*
 * Retrieves the data from the node passed.
 */
E CircularDoublyLinkedList_getData(CDLLNode node)
{
	return node.data;
}
/*
 * Sets the data in a specified node in the list to a specified value, and
 * updates the node passed in. Nonzero on failure.
 */
int CircularDoublyLinkedList_setData(CircularDoublyLinkedList* cdll, CDLLNode* node, E data)
{
	if(cdll == NULL) return 1;
	if((*cdll).elements == 0 || ((*node).next == NULL &&
			(*node).prev == NULL && (*cdll).elements != 1))
		return 1;
	if((*node).next == NULL && (*node).prev == NULL &&
			(*cdll).elements == 1)
	{
		(*(*cdll).handle).data = data;
		*node = (*(*cdll).handle);
		return 0;
	}
	// we're assuming that the parameter is a pointer to a copy of the node,
	// so we do this, just to be safe.
	CDLLNode* ptr;
	if((*node).next == NULL)
	{
		ptr = (*(CDLLNode*)((CDLLNode*)(*node).prev)).next;
		(*ptr).data = data;
		*node = *ptr;
		return 0;
	}
	ptr = (*(CDLLNode*)((CDLLNode*)(*node).next)).prev;
	(*ptr).data = data;
	*node = *ptr;
	return 0;
}
/*
 * Returns 1 if node1 is identical to node2 and 0 if not.
 */
int CircularDoublyLinkedList_equals(CDLLNode node1, CDLLNode node2)
{
	if(node1.data == node2.data && node1.next == node2.next &&
			node1.prev == node2.prev)
		return 1;
	return 0;
}
/*
 * Returns the number of elements currently in the list.
 */
int CircularDoublyLinkedList_getElements(CircularDoublyLinkedList* cdll)
{
	if(cdll == NULL) return 0;
	return (*cdll).elements;
}
