#include "../linkedListADT/linkedlist.h"

typedef struct queue Queue;

struct queue {
	LinkedList* list;
};


Queue createQueue(void);
int enqueue(Queue,void*);
void* dequeue(Queue);