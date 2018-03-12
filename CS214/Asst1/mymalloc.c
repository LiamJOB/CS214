#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "mymalloc.h"

static char block[5000];
static void *memoryPtr[5000/(sizeof(struct memNode) +1)] = {0};
static int init = 0;


//this will get the first free index that does not contain an entry
static int getFreeIndex(){
	int i;
	for(i = 0; i < memorySize; i++){
		if (memoryPtr[i] == 0){
			return i;
		}
		return 1;
	}
	return 0;
}

void * mymalloc(int size, char *file, int line){

	struct memNode *ptr;
	struct memNode *next;

	static struct memNode *root;

	//Display an error if the program tries to malloc 0 bytes of memory
	if (size == 0){
		printf("Error: Cannot malloc 0 bytes on line: %d in file: \"%s\" \n", __LINE__, __FILE__);
		return 0;
	}

	//function to first call myMalloc
	if(init == 0)
	{
		root = (struct memNode*) block;
		root->prev = root->next = 0;
		root->size = 5000 - sizeof(struct memNode);
		root->isFree = 1;
		init = 1;

		memoryPtr[getFreeIndex()] = block;
	}

	/*if myMalloc has already been called, start
	do/while loop: if the size trying to be malloced is too small or if the ptr is not free, resume
	else if: if the chunk being malloced is the right size but not enough memory to hold a new head node
	else: malloc enough space for data AND head node
	*/

	ptr = root;

	while(ptr != 0){
		if(ptr->size < size || !ptr->isFree){
			ptr = ptr->next;
		}
		else if(ptr->size < (size + sizeof(struct memNode))){
			ptr->isFree = 0;
			return (char*)ptr + sizeof(struct memNode);
		}
		else{
			next = (struct memNode*)((char*) ptr + sizeof(struct memNode) + size);
			next->prev = ptr;
			next->next = ptr->next;
			next->size = ptr->size - sizeof(struct memNode) - size;
			next->isFree = 1;
			memoryPtr[getFreeIndex()] = next;
			ptr->size = size;
			ptr->isFree = 0;
			ptr->next = next;
			return (char*)ptr + sizeof(struct memNode);
		}
	}

	//this printf only happens if the above fails i.e. there's not enough free memory to malloc
	printf("Error: Not enough free memory on line: %d in file: \"%s\" \n", __LINE__, __FILE__);
	return 0;
	
}

void myfree(void *ptr, char *file, int line){
	struct memNode *p;
	struct memNode *current;
	struct memNode *prev;
	struct memNode *next;
	int i;
	int valid = 0;

	//if the pointer is pointing to NULL, print an error
	if (p == NULL){
		printf("Error: NULL pointer on line: %d in file: \"%s\" \n", __LINE__, __FILE__);
		return;
	}

	//check for a valid memory pointer
	for(i = 0; i < memorySize; i++){
		if (p == memoryPtr[i] && !p->isFree){
			valid = 1;
			break;
		}
	}

	if(valid == 0)
	{
		printf("Error: Cannot free a pointer that was not malloced on line: %d in file: \"%s\"\n", __LINE__, __FILE__);
		return;
	}

	//check to make sure the pointer is not already freed
	if(current == ptr){
		if(current->isFree != 0){
			printf("Error: Pointer is already free on line: %d in file: \"%s\"\n", __LINE__, __FILE__);
		}

		//merge with previous nodes
		if((prev = p->prev) != 0 && prev->isFree){
				prev->size += sizeof(struct memNode) + p->size;
				memoryPtr[i] = 0;

		}

		else{
			p->isFree = 1;
			prev = ptr;
		}


	}
		
	//merge with nodes following the pointed node
	if((next = p->next) != 0 && next->isFree){
		prev->size += sizeof(struct memNode) + next->size;
		prev->next = next->next;

		for (i = 0; i<memorySize; i++){
			if(next==memoryPtr[i]){
				memoryPtr[i] = 0;
				break;
			}
		}
	}
	return;
}