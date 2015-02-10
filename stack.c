#include <stdio.h>
#include "stack.h"

void printStack(Stack s){
	Node* walker = s.top;
	printf("-----------------Stack---------------\n");
	printf("Top=%p\n",s.top );
	printf("Count=%d\n",s.count );
	while(walker != 0){
		printf("Data = %c\n",*(char*)walker->data );
		walker = walker -> next;
	}
}

Stack createStack(void){
	Stack s={0,0};
	return s;
}

int push(Stack* s,void* data){
	Node* n = create_node(data);
	if(s->count != 0){
		n->next = s->top;
	}
	s->top = n;
	s->count++;
	return s->count;
}

void* pop(Stack* s){
	void* deleted_data;
	if(s->top == 0){
		return 0;
	}
	deleted_data= s->top->data;
	s->top = s->top->next;
	s->count--;
	return deleted_data;
}