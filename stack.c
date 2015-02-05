#include "stack.h"

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