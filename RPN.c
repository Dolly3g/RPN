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
	String operators = "+-*/^";
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

int popAndCalculate(String expr,Stack* operands,Token* token){
	int a,b;
	char operator;
	a = *(int*)pop(operands);
	b = *(int*)pop(operands);
	operator = expr[token->start];
	return calculate(a,b,operator);
}

Result processOperand(String expr,Token* token, Stack* operands, String output){
	int* data;
	data = malloc(sizeof(int));
	*data = createValueFromIndexes(expr,token);
	push(operands,data);
	return (Result){0,0};
}

Result processOperator(String expr,Token* token, Stack* operands, String output){
	Result result={0,0};
	int* res;
	if(operands->count <2){
		result.error =1;
		return result;
	}
	res = malloc(sizeof(int));
	*res = popAndCalculate(expr,operands,token);
	push(operands,res);
	result.status = *res;
	return result;	
}

Result processExtras(String expr, Token* token, Stack* operands, String output){
	return (Result){0,0};
}

Result processParenthesis(String expr, Token* token, Stack* operands, String output){
	return (Result){0,0};
}

Result evaluate(String expr){
	Stack operands = createStack();
	Functions callbacks = {processOperator,processOperand,0,processExtras};
	LinkedList* tokens = makeTokenList(expr,callbacks);
	Node* walker = tokens->head;
	Token *token;
	Result result;

	while(walker != 0){
		token = (Token*)walker->data;
		result = token->function(expr,token,&operands,"");
		if(result.error==1) return result;
		walker = walker->next;
	}

	operands.count > 1 && (result.error = -1);
	return result;
}

Token* createToken(int id,int start,int end,callback fn){
	Token* t;
	t = malloc(sizeof(Token));
	t->id = id;
	t->start = start;
	t->end = end;
	t->function = fn;
	return t;
}

void insertToken(Token* token,Node** node,LinkedList* list){
	node = malloc(sizeof(Node*));
	*node = create_node(token);
	add_to_list(list,*node);
}

int isParenthesis(char ch){
	return ch == '(' || ch == ')';
}

Token* getAppropriateToken(String expr, int* count, Functions callbacks){
	int start,i = *count;
	Token* token;

	if(isDigit(expr[i])) {
		for(start=i ; isDigit(expr[i+1]) ; i++){}
		token = createToken(1,start,i,callbacks.processOperand);
	}

	else if(isOperator(expr[i]))
		token = createToken(2,i,i,callbacks.processOperator);

	else if(isParenthesis(expr[i]))
		token = createToken(3,i,i,callbacks.processParenthesis);

	else
		token = createToken(4,i,i,callbacks.processExtras);

	*count = i;
	return token;
}

LinkedList* makeTokenList(String expr, Functions callbacks){
	int i, length=strlen(expr);
	LinkedList* list = calloc(1,sizeof(LinkedList));
	Node** node;
	Token* token;

	for(i=0 ; i<length ; i++){
		token = getAppropriateToken(expr,&i,callbacks);
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
		precedences[i].op == onTop && (p_onTop = precedences[i].precedence);
		precedences[i].op == operator && (p_op = precedences[i].precedence);
	}

	if(p_op < p_onTop)return -1;
	if(p_op > p_onTop)return 1;
	return 0;
}

int popAllAndDump(Stack* operators, String output, int count){
	while(operators->count != 0){
		output[count++] = *(char*)pop(operators);
		operators->count>=1 && (output[count++] = ' ');
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


String getStrigifiedDigit(String expr, Token* token){
	int i,count=0;
	String number = malloc(sizeof(char)*token->end - token->start);
	for(i = token->start ; i <= token->end ; i++){
		number[count++] = expr[i];
	}
	return number;
}

void dumpInOutput(String number, String output){
	int i,length= strlen(number),count=strlen(output);

	for(i=0 ; i<length ; i++){
		output[count++] = number[i];
	}
}

Result processInfixOperator(String expr, Token* token, Stack* operators, String output){
	int count = strlen(output);
	char* operator = malloc(sizeof(char));
	*operator = expr[token->start];

	if(operators->count > 0 && *(char*)operators->top->data == '('){
		push(operators,operator);
		return (Result){0,0};
	}

	while(operators->count > 0 && isPrecedenceHigher(*operator,operators) != 1){
		output[count++] = *(char*)pop(operators);
		output[count++] = ' ';
	}
	push(operators,operator);
	return (Result){0,0};
}

Result processInfixOperand(String expr, Token* token, Stack* operators, String output){
	String number = getStrigifiedDigit(expr,token);
	dumpInOutput(number,output);
	output[strlen(output)] = ' ';
	return (Result){0,0};
}

Result processInfixParenthesis(String expr, Token* token, Stack* operators, String output){
	char* operator = malloc(sizeof(char));
	*operator = expr[token->start];
	*operator == '(' && push(operators,operator);
	*operator == ')' && popAllTillOpeningParenthesis(operators,output,strlen(output));
	return (Result){0,0};
}

String infixToPostfix(String expr){
	int i,count=0;
	Stack operators = createStack();
	Functions callbacks = {processInfixOperator,processInfixOperand,processInfixParenthesis,processExtras};
	LinkedList* tokens = makeTokenList(expr,callbacks);
	String output = calloc(tokens->count,sizeof(char));
	Node* walker = tokens->head;
	Token* token;

	while(walker != NULL){
		token = (Token*)walker->data;
		token->function(expr,token,&operators,output);
		walker = walker->next;
	}
	popAllAndDump(&operators,output,strlen(output));
	return output;
}