#include "../StackADT/stack.h"
typedef char* String;
typedef struct token Token;
typedef struct result Result;

struct token{
	int id;
	int start;
	int end;
	//int (*function)(Stack,char*);
};

struct result{
	int error;
	int status;	
};

int isOperator(char);
int isDigit(char);
Result evaluate(String);
int calculate(int,int,char);
Token* createToken(int,int,int);
LinkedList* makeTokenList(String);
int createValueFromSubstr(String,Token*);
char getOperatorFromToken(String,Token*);
char * infixToPostfix(char * expression);