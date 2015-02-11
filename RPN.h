#include "stack.h"
#include "queue.h"

typedef char* String;
typedef struct token Token;
typedef struct result Result;
typedef struct op Operator;
typedef struct functions Functions;
typedef Result(*callback)(String,Token*,Stack*,String);

struct token{
	int id;
	int start;
	int end;
	callback function;
};

struct result{
	int error;
	int status;	
};

struct op{
	char op;	
	int precedence;
};

struct functions {
	callback processOperator;	
	callback processOperand;	
	callback processParenthesis;
	callback processExtras;	
};

int isOperator(char);
int isDigit(char);
Result evaluate(String);
int calculate(int,int,char);
Token* createToken(int,int,int,callback);
LinkedList* makeTokenList(String,Functions);
int createValueFromIndexes(String,Token*);
char getOperatorFromToken(String,Token*);
char * infixToPostfix(char * expression);
int indexOfChar(String,char);
int isPrecedenceHigher(char,Stack*);
void performPushOrPop(Stack* , char*, String, int);