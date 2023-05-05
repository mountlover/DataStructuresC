#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define GENERICS int
#include "DoublyLinkedList.h"
#include "CircularDoublyLinkedList.h"

/*
 * Tests all functions of DoublyLinkedList and CircularDoublyLinkedList
 */
int main()
{
	// Test all functions of DoublyLinkedList
	printf("Creating...\n");
	fflush(stdout);
	DoublyLinkedList* dll = DoublyLinkedList_create();
	printf("Initializing...\n");
	fflush(stdout);
	DoublyLinkedList_initialize(dll, (E)1, 0);
	printf("Inserting ones from head and tail...\n");
	fflush(stdout);
	int i;
	for(i=0; i<10; i++)
	{
		if(DoublyLinkedList_pushHead(dll, (E)1)) printf("error: pushHead");
		if(DoublyLinkedList_pushTail(dll, (E)1)) printf("error: pushTail");
		printf("%d, ", i);
		fflush(stdout);
	}
	printf("\nSize is %d, should be 21\nRemoving data...\n", dll->size);
	fflush(stdout);
	for(i=0; i<7; i++)
	{
		DoublyLinkedList_remove(DoublyLinkedList_find(dll, (E)1));
		DoublyLinkedList_popHead(dll);
		DoublyLinkedList_popTail(dll);
		printf("%d, ", i);
		fflush(stdout);
	}
	printf("\nSize is %d, should be 0\nInserting 1-10 in ascending order...\n", dll->size);
	printf("Inserting first new element...\n");
	fflush(stdout);
	DoublyLinkedList_pushHead(dll, (E)4);
	printf("Inserting 8 more elements...\n");
	fflush(stdout);
	DoublyLinkedList_pushTail(dll, (E)6);
	DoublyLinkedList_pushHead(dll, (E)3);
	DoublyLinkedList_pushTail(dll, (E)7);
	DoublyLinkedList_pushHead(dll, (E)2);
	DoublyLinkedList_pushTail(dll, (E)8);
	DoublyLinkedList_pushHead(dll, (E)1);
	DoublyLinkedList_pushTail(dll, (E)9);
	DoublyLinkedList_pushHead(dll, (E)17);
	DoublyLinkedList_pushTail(dll, (E)10);
	printf("Inserting 5 after 4...\n");
	fflush(stdout);
	DoublyLinkedList_insertAfter(DoublyLinkedList_find(dll, (E)4), (E)5);
	printf("Removing 17...\n");
	fflush(stdout);
	DoublyLinkedList_remove(DoublyLinkedList_find(dll, (E)17));
	DLLNode* handle;
	printf("Size is %d, should be 10\n", dll->size);
	printf("Forward Traversal\n");
	fflush(stdout);
	DLL_TRAVERSAL(dll, handle)
	{
		printf("%d\n", (int)handle->data);
	}
	printf("Backward Traversal\n");
	fflush(stdout);
	DLL_REVERSE_TRAVERSAL(dll, handle)
	{
		printf("%d\n", (int)handle->data);
	}
	printf("Freeing List...\n");
	fflush(stdout);
	DoublyLinkedList_free(dll);
	dll = DoublyLinkedList_create();
	srand(time(NULL));
	printf("Creating a sorted list of 10 random ints...\n");
	fflush(stdout);
	for(i=0; i<10; i++)
	{
		DoublyLinkedList_sortedInsert(dll, (E)rand());
	}
	DLL_TRAVERSAL(dll, handle)
	{
		printf("%d\n", (int)handle->data);
	}
	printf("Freeing List, again...\n");
	fflush(stdout);
	DoublyLinkedList_free(dll);
	printf("Done!\n");
	// Test all functions of CircularDoublyLinkedList
	CircularDoublyLinkedList* cdll = (CircularDoublyLinkedList*)malloc(sizeof(CircularDoublyLinkedList));
	CircularDoublyLinkedList_initialize(cdll, (E)1);
	int i = 2;
	while(i <= 11)
	{
		CircularDoublyLinkedList_addEntry(cdll, (E)i);
		i++;
	}
	CircularDoublyLinkedList_removeEntry(cdll);
	CDLLNode tmpnode = CircularDoublyLinkedList_getHandle(cdll);
	CircularDoublyLinkedList_setData(cdll, &tmpnode, (E)5);
	CDLLNode ptr = CircularDoublyLinkedList_getHandle(cdll);
	E tmp = -1;
	/*
	 * Forward loop demo
	 */
	for(i = 0; i < CircularDoublyLinkedList_getElements(cdll); i++)
	{
		if(CircularDoublyLinkedList_getData(ptr) == tmp)
		{
			printf("Null Pointer Exception\n");
			break;
		}
		tmp = CircularDoublyLinkedList_getData(ptr);
		printf("%d\n", (int)CircularDoublyLinkedList_getData(ptr));
		ptr = CircularDoublyLinkedList_getNext(ptr);

	}
	if(ptr.next != NULL || !CircularDoublyLinkedList_equals(CircularDoublyLinkedList_getHandle(cdll), ptr))
		printf("Premature loop termination.\n");
	printf("\n");
	tmp = -1;
	ptr = CircularDoublyLinkedList_getHandle(cdll);
	/*
	 * Backward loop demo
	 */
	for(i = 0; i < CircularDoublyLinkedList_getElements(cdll); i++)
	{
		if(CircularDoublyLinkedList_getData(ptr) == tmp)
		{
			printf("Null Pointer Exception\n");
			break;
		}
		tmp = CircularDoublyLinkedList_getData(ptr);
		printf("%d\n", (int)CircularDoublyLinkedList_getData(ptr));
		ptr = CircularDoublyLinkedList_getPrev(ptr);

	}
	if(ptr.prev != NULL || !CircularDoublyLinkedList_equals(CircularDoublyLinkedList_getHandle(cdll), ptr))
		printf("Premature loop termination.\n");
	printf("\n");
	printf("Head value: %d\n", (int)CircularDoublyLinkedList_getData(CircularDoublyLinkedList_getHandle(cdll)));
	printf("Tail value: %d\n", (int)CircularDoublyLinkedList_getData(CircularDoublyLinkedList_getHandle(cdll)));
	printf("No. of Elements: %d\n", CircularDoublyLinkedList_getElements(cdll));
	printf("Press ENTER to continue");
	gets((char*)&tmp);
	return 0;
}
