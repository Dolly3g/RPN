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

int isOperator(char ch){
	String operators = "+-*/^()";
	int i,length = strlen(operators);
	for(i=0 ; i<length ; i++){
		if(operators[i] == ch)
			return 1;
	}
	return 0;
}

int isDigit(char ch){
	if(ch >=48 && ch <=57)
		return 1;
	return 0;
}

int createValueFromIndexes(String expr,Token* t){
	int i,count=0;
	char* num = malloc( sizeof(char)* (t->end - t->start));
	for(i=t->start ; i<=t->end ; i++){
		num[count++] = expr[i];
	}
	return atoi(num);
}

void onOperand(String expr,Token* token, Stack* operands){
	int* data;
	data = malloc(sizeof(int));
	*data = createValueFromIndexes(expr,token);
	push(operands,data);
}

int onOperator(String expr,Stack* operands,Token* token){
	int a,b;
	char operator;
	a = *(int*)pop(operands);
	b = *(int*)pop(operands);
	operator = expr[token->start];
	return calculate(a,b,operator);
}

Result forOperator(Stack* operands, String expr,Token* token){
	Result result={0,0};
	int* res;
	if(operands->count <2){
		result.error =1;
		return result;
	}
	res = malloc(sizeof(int));
	*res = onOperator(expr,operands,token);
	push(operands,res);
	result.status = *res;
	return result;	
}

Result evaluate(String expr){
	Stack operands = createStack();
	LinkedList* tokens = makeTokenList(expr);
	Node* walker = tokens->head;
	Token *token;
	int a,b,*res;
	char operator;
	Result result;

	while(walker != 0){
		token = (Token*)walker->data;
		if(token->id == 1) onOperand(expr,token,&operands);
		if(token->id == 2) result = forOperator(&operands,expr,token);
		if(result.error==1) return result;
		walker = walker->next;
	}

	operands.count > 1 && (result.error = -1);
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
	int i, start, length=strlen(expr);
	LinkedList* list = calloc(1,sizeof(LinkedList));
	Node** node;
	Token* token;

	for(i=0 ; i<length ; i++){

		if(isOperator(expr[i])) token = createToken(2,i,i);

		else if(isDigit(expr[i])) {
			for(start=i ; isDigit(expr[i+1]) ; i++ ){}
			token = createToken(1,start,i);
		}

		else token = createToken(3,i,i);
		insertToken(token,node,list);
	}
	return list;
}

int indexOfChar (String str, char ch){
	int i, length = strlen(str);
	for(i=0 ; i<length ; i++){
		if(str[i] == ch)
			return i;
	}
	return -1;
}

int isPrecedenceHigher(char operator, Stack* operators){
	Operator precedences[] = {{'+',2},{'-',2},{'*',3},{'/',3},{'^',4},{'(',5}};
	char onTop = *(char*)operators->top->data;
	int i,length = 6;
	int p_onTop,p_op;

	for(i=0 ; i<length ; i++){
		if(precedences[i].op == onTop)
			p_onTop = precedences[i].precedence;
		if(precedences[i].op == operator)
			p_op = precedences[i].precedence;
	}
	if(p_op < p_onTop)return -1;
	if(p_op > p_onTop)return 1;
	return 0;
}

/*void performPushOrPop(Stack* operators, char* operator, String output,int count){
	if(operators->count == 0){
		push(operators,operator);
		return;
	}
	if(isPrecedenceHigher(*operator,operators)){
		push(operators,operator);
		return;
	}
	push(operators,operator);
}
*/
int popAllAndDump(Stack* operators, String output, int count){
	while(operators->count != 0){
		output[count++] = *(char*)pop(operators);
		if(operators->count>=1)
			output[count++] = ' ';

	}
	return count;
}

int popAllTillOpeningParenthesis(Stack *operators, String output, int count){
	while(*(char*)operators->top->data != '('){
		output[count++] = *(char*)pop(operators);
		output[count++] = ' ';
	}
	pop(operators);
	return count;
}

String infixToPostfix(String expr){
	int i,count=0,length = strlen(expr);
	Stack operators = createStack();
	char *operator;
	String output = malloc(sizeof(char)*length);

	for(i=0 ; i<length ; i++){
		if(isDigit(expr[i])){
			output[count++] = expr[i];
			output[count++] = ' ';
		}

		if(expr[i] ==  ')'){
			count = popAllTillOpeningParenthesis(&operators,output,count);
			continue;
		}

		if(isOperator(expr[i])){
			operator = malloc(sizeof(char));
			*operator = expr[i];

			if(operators.count == 0 || isPrecedenceHigher(*operator,&operators) == 1 || *(char*)operators.top->data == '('){
				push(&operators,operator);
				continue;
			}
			if(isPrecedenceHigher(*operator,&operators) == 0){
				output[count++] = *(char*)pop(&operators);
				output[count++] = ' ';
				push(&operators,operator);
			}
			if(isPrecedenceHigher(*operator,&operators) == -1) {
				count = popAllAndDump(&operators,output,count);
				output[count++] = ' ';
				push(&operators,operator);
			}
		}
	}
	popAllAndDump(&operators,output,count);
	return output;
}