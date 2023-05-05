/*
 * DoublyLinkedList - A doubly linked list to contain values of type E which
 * are generic and can be specified explicitly by calling
 * #define GENERICS [type]
 * Important Note: Try to avoid allocating DoublyLinkedLists manually, and opt
 * to use the DoublyLinkedList_create() function. This side-steps issues with
 * Windows not zeroing out memory properly.
 * Author: Yama H
 * Version: 2.1
 * Revision: 5.15.2011
 */
#include <stdlib.h>
#include <assert.h>
#include "DoublyLinkedList.h"

/*
 * Initializes a pre-allocated List and creates first node.
 */
void DoublyLinkedList_initialize(DoublyLinkedList* dll, E data, short int autoSort)
{
	assert(dll != NULL);
	dll->size = 1;
	dll->head = (DLLNode*)malloc(sizeof(DLLNode));
	dll->head->data = data;
	dll->head->prev = NULL;
	dll->head->next = NULL;
	dll->head->list = dll;
	dll->sorted = autoSort;
	dll->tail = dll->head;
}
/*
 * Allocates an empty DoublyLinkedList
 */
DoublyLinkedList* DoublyLinkedList_create()
{
	DoublyLinkedList* dll = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
	dll->size = 0;
	dll->head = NULL;
	dll->tail = NULL;
	dll->compare = NULL;
	return dll;
}
/*
 * Adds an entry to the tail end of the List.
 * Nonzero on error.
 * note: this method is disabled when autoSort is enabled, in that case,
 * use DoublyLinkedList_sortedInsert() instead
 */
int DoublyLinkedList_pushTail(DoublyLinkedList* dll, E data)
{
	if(dll->size == 0)
	{
		DoublyLinkedList_initialize(dll, data, 0);
		return 0;
	}
	assert(!dll->sorted);
	return DoublyLinkedList_insertAfter(dll->tail, data);
}
/*
 * Adds an entry to the head end of the List.
 * Nonzero on error.
 * note: this method is disabled when autoSort is enabled, in that case,
 * use DoublyLinkedList_sortedInsert() instead
 */
int DoublyLinkedList_pushHead(DoublyLinkedList* dll, E data)
{
	if(dll->size == 0)
	{
		DoublyLinkedList_initialize(dll, data, 0);
		return 0;
	}
	assert(!dll->sorted);
	return DoublyLinkedList_insertBefore(dll->head, data);
}
/*
 * Pops and returns the tail off the list
 */
E DoublyLinkedList_popTail(DoublyLinkedList* dll)
{
	assert(dll != NULL);
	assert(dll->size > 0);
	E returnData = dll->tail->data;
	if(dll->size == 1)
	{
		dll->head = NULL;
		free(dll->tail);
		dll->tail = NULL;
		dll->size--;
		return returnData;
	}
	DLLNode* tmp = dll->tail->prev;
	free(dll->tail);
	tmp->next = NULL;
	if(tmp->prev != NULL) tmp->prev->next = tmp;
	dll->tail = tmp;
	dll->size--;
	return returnData;
}
/*
 * Pops and returns the head off the list
 */
E DoublyLinkedList_popHead(DoublyLinkedList* dll)
{
	assert(dll != NULL);
	assert(dll->size > 0);
	E returnData = dll->head->data;
	if(dll->size == 1)
	{
		dll->tail = NULL;
		free(dll->head);
		dll->head = NULL;
		dll->size--;
		return returnData;
	}
	DLLNode* tmp = dll->head->next;
	free(dll->head);
	tmp->prev = NULL;
	if(tmp->next != NULL) tmp->next->prev = tmp;
	dll->head = tmp;
	dll->size--;
	return returnData;
}
/*
 * Removes an element from the list and deallocates it.
 * Nonzero on failure.
 */
int DoublyLinkedList_remove(DLLNode* element)
{
	if(element == NULL) return 1;
	if(element->list->size <= 0) return 1;
	if(element == element->list->head)
	{
		DoublyLinkedList_popHead(element->list);
		return 0;
	}
	if(element == element->list->tail)
	{
		DoublyLinkedList_popTail(element->list);
		return 0;
	}
	element->next->prev = element->prev;
	element->prev->next = element->next;
	element->list->size--;
	free(element);
	return 0;
}
/*
 * Searches for an element in the list and returns a pointer to it's node.
 * Returns NULL if not found.
 */
DLLNode* DoublyLinkedList_find(DoublyLinkedList* dll, E value)
{
	DLLNode* frontPtr, *rearPtr;
	DLL_DOUBLE_TRAVERSAL(dll, frontPtr, rearPtr)
	{
		if(dll->compare)
		{
			if(!dll->compare(frontPtr->data, value)) return frontPtr;
			if(!dll->compare(rearPtr->data, value)) return rearPtr;
		}
		else
		{
			if(frontPtr->data == value) return frontPtr;
			if(rearPtr->data == value) return rearPtr;
		}
	}
	return NULL;
}
/*
 * Retrieves the head node.
 */
DLLNode DoublyLinkedList_getHead(DoublyLinkedList* dll)
{
	assert(dll != NULL);
	assert(dll->size > 0);
	return *(dll->head);
}
/*
 * Retrieves the tail node. Returns allocated memory if dll is null.
 */
DLLNode DoublyLinkedList_getTail(DoublyLinkedList* dll)
{
	assert(dll != NULL);
	assert(dll->size > 0);
	return *(dll->tail);
}
/*
 * Retrieves the node after the current node. Returns the parameter if the
 * current node is the last entry (the tail).
 */
DLLNode DoublyLinkedList_getNext(DLLNode node)
{
	if(node.next == NULL)
		return node;
	return *(node.next);
}
/*
 * Retrieves the node before the current node. Returns the parameter if the
 * current node is the first entry (the head).
 */
DLLNode DoublyLinkedList_getPrev(DLLNode node)
{
	if(node.prev == NULL)
		return node;
	return *(node.prev);
}
/*
 * Retrieves the data from the node passed.
 */
E DoublyLinkedList_getData(DLLNode node)
{
	return node.data;
}
/*
 * Sets the data in a specified node in the list to a specified value, and
 * updates the node passed in. Nonzero on failure.
 */
int DoublyLinkedList_setData(DLLNode* node, E data)
{
	if(node == NULL) return 0;
	node->data = data;
	return 1;
}
/*
 * Creates a new node from data and inserts it after handle
 * Nonzero on failure.
 * note: this method is disabled when autoSort is enabled, in that case,
 * use DoublyLinkedList_sortedInsert() instead
 */
int DoublyLinkedList_insertAfter(DLLNode* handle, E data)
{
	if(handle == NULL) return 1;
	if(handle->list->size == 0)
	{
		DoublyLinkedList_initialize(handle->list, data, 0);
		return 0;
	}
	assert(!handle->list->sorted);
	if(handle->next == NULL && handle == handle->list->tail)
	{
		handle->next = (DLLNode*)malloc(sizeof(DLLNode));
		handle->next->prev = handle;
		handle->next->next = NULL;
		handle->next->data = data;
		handle->next->list = handle->list;
		handle->list->tail = handle->next;
		handle->list->size++;
		return 0;
	}
	if(handle->next != NULL)
	{
		DLLNode* newNode = (DLLNode*)malloc(sizeof(DLLNode));
		newNode->data = data;
		newNode->prev = handle;
		newNode->next = handle->next;
		newNode->list = handle->list;
		handle->next->prev = newNode;
		handle->next = newNode;
		handle->list->size++;
		return 0;
	}
	return 1;
}
/*
 * Creates a new node from data and inserts it before handle
 * Nonzero on failure.
 * note: this method is disabled when autoSort is enabled, in that case,
 * use DoublyLinkedList_sortedInsert() instead
 */
int DoublyLinkedList_insertBefore(DLLNode* handle, E data)
{
	if(handle == NULL) return 1;
	if(handle->list->size == 0)
	{
		DoublyLinkedList_initialize(handle->list, data, 0);
		return 0;
	}
	assert(!handle->list->sorted);
	if(handle->prev == NULL && handle == handle->list->head)
	{
		handle->prev = (DLLNode*)malloc(sizeof(DLLNode));
		handle->prev->next = handle;
		handle->prev->prev = NULL;
		handle->prev->data = data;
		handle->prev->list = handle->list;
		handle->list->head = handle->prev;
		handle->list->size++;
		return 0;
	}
	if(handle->prev != NULL)
	{
		DLLNode* newNode = malloc(sizeof(DLLNode));
		newNode->data = data;
		newNode->next = handle;
		newNode->prev = handle->prev;
		newNode->list = handle->list;
		handle->prev->next = newNode;
		handle->prev = newNode;
		handle->list->size++;
		return 0;
	}
	return 1;
}
/*
 * Returns the number of size currently in the list.
 */
size_t DoublyLinkedList_getSize(DoublyLinkedList* dll)
{
	if(dll == NULL) return 0;
	return dll->size;
}
/*
 * Empties and deallocates a DoublyLinkedList
 */
void DoublyLinkedList_free(DoublyLinkedList* dll)
{
	DLLNode* tmp;
	while(dll->size > 0)
	{
		tmp = dll->head;
		DoublyLinkedList_popHead(dll);
		free(tmp);
	}
	free(dll);
}
/*
 * Inserts an element such that the list remains in ascending order.
 * Only works if the list was initialized with the autoSort flag as true,
 * although calling sortedInsert on an empty list will set this flag to true.
 * note: this function uses DoublyLinkedList.compare iff it's been implemented
 */
int DoublyLinkedList_sortedInsert(DoublyLinkedList* dll, E value)
{
	if(dll == NULL) return 1;
	if(dll->size == 0)
	{
		DoublyLinkedList_initialize(dll, value, 1);
		return 0;
	}
	assert(dll->sorted);
	DLLNode* frontPtr, *rearPtr;
	// Do this so the insert functions will work
	dll->sorted = 0;
	int returnVal = 1;
	DLL_DOUBLE_TRAVERSAL(dll, frontPtr, rearPtr)
	{
		if(dll->compare)
		{
			if(dll->compare(frontPtr->data, value) >= 0)
			{
				returnVal = DoublyLinkedList_insertBefore(frontPtr, value);
				break;
			}
			if(dll->compare(rearPtr->data, value) < 0)
			{
				returnVal = DoublyLinkedList_insertAfter(rearPtr, value);
				break;
			}
		}
		else
		{
			if(frontPtr->data >= value)
			{
				returnVal = DoublyLinkedList_insertBefore(frontPtr, value);
				break;
			}
			if(rearPtr->data < value)
			{
				returnVal = DoublyLinkedList_insertAfter(rearPtr, value);
				break;
			}
		}
	}
	dll->sorted = 1;
	return returnVal;
}
