#include <stdlib.h>
#include "queue.h"

Queue createQueue(){
	Queue q;
	q.list = calloc(1,sizeof(LinkedList));
	return q;
}

int enqueue(Queue q, void* data){
	Node* node = create_node(data);
	add_to_list(q.list,node);
	return q.list->count;
}

void* dequeue(Queue q){
	return deleteElementAt(q.list,0);
}