#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "RPN.h"

int calculate(int a, int b, char operator){
	switch(operator){
		case '+' : return b + a;
		case '-' : return b - a;
		case '*' : return b * a;
		case '/' : return b / a;
		default : return -1;
	}
}

char* cat(char* string, char ch){
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
	printf("new=%s\n",new_string );
	return new_string;	
}

Stack giveStackOfOperands(String expr){
	int i,j;
	int* token;
	char* num;
	int length = strlen(expr);
	Stack s = createStack();

	for (i=0 ; i<length ; i++){

		if(isOperator(expr[i]))
			break;

		token = malloc(sizeof(int));
		num = calloc(1,sizeof(char)*10);

		if(expr[i] != ' ' && expr[i] != 0){
			printf("char=%c\n",expr[i] );
			num = cat(num,expr[i]);
			continue;
		}
		else{
			printf("Number=%s\n",num );
			*token = atoi(num);
			push(&s,token);
			num = calloc(1,sizeof(char)*5);
			printf("%s\n",num );
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
	for(i=0 ; i<length && operands.count>0 ; i++){
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
