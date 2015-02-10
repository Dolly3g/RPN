#include "stack.h"
#include "queue.h"

typedef char* String;
typedef struct token Token;
typedef struct result Result;
typedef struct op Operator;

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

struct op{
	char op;	
	int precedence;
};

int isOperator(char);
int isDigit(char);
Result evaluate(String);
int calculate(int,int,char);
Token* createToken(int,int,int);
LinkedList* makeTokenList(String);
int createValueFromIndexes(String,Token*);
char getOperatorFromToken(String,Token*);
char * infixToPostfix(char * expression);
int indexOfChar(String,char);
int isPrecedenceHigher(char,Stack*);
void performPushOrPop(Stack* , char*, String, int);