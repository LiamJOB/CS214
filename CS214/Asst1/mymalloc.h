#ifndef _MYMALLOC_H_
#define _MYMALLOC_H_

#include <stdlib.h>

#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

 typedef struct memNode{

	int size;
	int isFree;

	struct memNode *next, *prev;
} memNode;

static const int memorySize = (5000/sizeof(struct memNode) + 1);

void *mymalloc(int size, char *file, int line);
void myfree(void *, char *file, int line);

#endif