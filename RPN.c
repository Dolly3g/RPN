#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "RPN.h"

void printStack(Stack s){
	Node* walker = s.top;
	printf("-----------------Stack---------------\n");
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

int isOperator(char ch){
	if(ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return 1;
	return 0;
}

int isDigit(char ch){
	if(ch >=48 && ch <=57)
		return 1;
	return 0;
}

int createValueFromSubstr(String expr,Token* t){
	int i,count=0;
	char* num = malloc( sizeof(char)* (t->end-t->start));
	for(i=t->start ; i<=t->end ; i++){
		num[count++] = expr[i];
	}
	return atoi(num);
}

char getOperatorFromToken(String expr, Token* t){
	return expr[t->start];
}

Result evaluate(String expr){
	Stack operands = createStack();
	LinkedList* tokens = makeTokenList(expr);
	Node* walker = tokens->head;
	Token *token;
	int a,b,*data,*res;
	char operator;
	Result result={0,0};

	while(walker != 0){
		token = (Token*)walker->data;
		if(token->id == 1){
			data = malloc(sizeof(int));
			*data = createValueFromSubstr(expr,token);
			push(&operands,data);
		}
		if(token->id == 2){
			if(operands.count <2){
				result.error =1;
				return result;
			}
			res = malloc(sizeof(int));
			a = *(int*)pop(&operands);
			b = *(int*)pop(&operands);
			operator = getOperatorFromToken(expr,token);
			*res = calculate(a,b,operator);
			push(&operands,res);
		}
		walker = walker->next;
	}

	operands.count > 1 && (result.error = 1);
	result.status=*res;
	return result;
}

Token* createToken(int id,int start,int end){
	Token* t;
	t = malloc(sizeof(Token));
	t->id = id;
	t->start = start;
	t->end = end;
	return t;
}

void insertToken(Token* token,Node** node,LinkedList* list){
	node = malloc(sizeof(Node*));
	*node = create_node(token);
	add_to_list(list,*node);
}

LinkedList* makeTokenList(String expr){
	int i,length,start;
	LinkedList* list = calloc(1,sizeof(LinkedList));
	Node** node;
	Token* token;

	for(i=0,length= strlen(expr) ; i<length ; i++){
		if(isOperator(expr[i])){
			token = createToken(2,i,i);
		}

		else if(isDigit(expr[i])){
			start = i;
			while(isDigit(expr[i+1])){
				i++;
			}
			token = createToken(1,start,i);
		}

		else
			token = createToken(3,i,i);

		insertToken(token,node,list);
	}

	return list;
}