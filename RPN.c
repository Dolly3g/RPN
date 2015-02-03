#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "RPN.h"

void printStack(Stack s){
	Node* walker = s.top;
	printf("-----------------------------Stack-----------------------\n");
	printf("Top=%p\n",s.top );
	printf("Count=%d\n",s.count );
	while(walker != 0){
		printf("Data = %d\n",*(int*)walker->data );
		walker = walker -> next;
	}
}

int calculate(int a, int b, char operator){
	switch(operator){
		case '+' : return b + a;
		case '-' : return b - a;
		case '*' : return b * a;
		case '/' : return b / a;
		default : return -1;
	}
}

char* concat(char* string, char ch){
	int i,size = sizeof(char)*(strlen(string)+2);
	char *new_string = malloc(size);
	
	for (i=0 ; i<size; ++i)	{
		if(string[i] == 0){
			new_string[i] = ch;
			break;
		}
		new_string[i] = string[i];
	}

	new_string[i+1] = 0;
	return new_string;	
}

Stack giveStackOfOperands(String expr){
	int i,j;
	int* token;
	char* num;
	int length = strlen(expr);
	Stack s = createStack();
	num = calloc(1,sizeof(char)*10);

	for (i=0 ; i<length ; i++){

		if(isOperator(expr[i])){
			if(num[0] != 0){
				token = malloc(sizeof(int));
				*token = atoi(num);
				push(&s,token);
				num = calloc(1,sizeof(char)*10);
			}
			break;
		}

		token = malloc(sizeof(int));
		
		if(expr[i] != ' ' && expr[i] != 0){
			num = concat(num,expr[i]);
			continue;
		}
		else{
			*token = atoi(num);
			push(&s,token);
			num = calloc(1,sizeof(char)*10);
		}		
	}
	return s;
}

int isOperator(char ch){
	if(ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return 1;
	return 0;
}

int evaluate(String expr){
	Stack operands = giveStackOfOperands(expr);
	int a,b,*result;
	int i,length = strlen(expr);
	for(i=0 ; i<length && operands.count>=2 ; i++){
		if(!isOperator(expr[i]))
			continue;
		a = *(int*)pop(&operands);
		b = *(int*)pop(&operands);
		result = malloc(sizeof(int));
		*result = calculate(a,b,expr[i]);
		push(&operands,result);
	}
	return *result;
}
