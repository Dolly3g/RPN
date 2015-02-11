#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RPN.h"
#include "expr_assert.h"

void test_isOperator_tells_whether_given_char_is_operator_or_not(){
	assertEqual(isOperator('+'),1);
	assertEqual(isOperator('a'),0);
}

void test_isDigit_tells_whether_given_char_is_digit_or_not(){
	assertEqual(isDigit('1'),1);
	assertEqual(isDigit(' '),0);	
}

void test_indexOfChar_gives_the_index_of_char_in_the_given_string(){
	assertEqual(indexOfChar("+*/!@",'*'),1);
	assertEqual(indexOfChar("012345",'5'),5);
}

void test_indexOfChar_gives_neg1_if_char_is_not_present_in_the_given_string(){
	assertEqual(indexOfChar("012345",'*'),-1);
}

void test_isPrecedenceHigher_tells_if_given_operator_has_more_precedence_than_that_on_stack_top(){
	Stack operators = createStack();
	char *op = malloc(sizeof(char));
	*op = '*';
	push(&operators,op);
	assertEqual(isPrecedenceHigher('^',&operators),1);
	assertEqual(isPrecedenceHigher('+',&operators),-1);
	assertEqual(isPrecedenceHigher('/',&operators),0);
}

void test_calculate_takes_2_operands_and_an_operator_and_returns_result_of_operation(){
	assertEqual(calculate(2, 4,'+'),6);
	assertEqual(calculate(2, 4,'-'),2);
	assertEqual(calculate(2, 4,'/'),2);
	assertEqual(calculate(2, 4,'*'),8);
}

Result fn(String str, Token* token, Stack* operands, String output){
	return (Result){0,0};
}

void test_createToken_creates_a_token_with_given_parameters(){
	Stack s = createStack();
	Token* t = createToken(1,2,3,&fn);
	assertEqual(t->id,1);
	assertEqual(t->start,2);
	assertEqual(t->end,3);
	assertEqual(t->function("",t,&s,"").status,0);
}

Result forOperator(String str, Token* token, Stack* operands, String output){
	return (Result){2,2};
}

Result forOperand(String str, Token* token, Stack* operands, String output){
	return (Result){1,1};
}

Result forExtras(String str, Token* token, Stack* operands, String output){
	return (Result){1,1};
}

void test_makeTokenList_gives_the_linked_list_of_tokens_in_the_given_string(){
	LinkedList *list;
	Token* t; Stack* s;
	Functions callbacks = {&forOperator,&forOperand,0,&forExtras};
	list = makeTokenList("2 3 +",callbacks);
	assertEqual(list->count,5);
	assertEqual(((Token*)list->head->data)->id,1);
	assertEqual(((Token*)list->head->data)->function("",t,s,"").status,1);
	assertEqual(((Token*)list->tail->data)->id,2);
	assertEqual(((Token*)list->tail->data)->function("",t,s,"").status,2);
}

void test_createValueFromIndexes_returns_the_value_from_given_token(){
	Token* t = createToken(2,2,2,fn);
	String expr = "2 3 +";
	assertEqual(createValueFromIndexes(expr,t),3);
}

void test_createValueFromIndexes_returns_the_2digit_value_from_given_token(){
	Token* t = createToken(2,2,3,fn);
	String expr = "2 33 +";
	assertEqual(createValueFromIndexes(expr,t),33);
}

void test_evaluate_returns_the_result_of_postfix_operation (){
	assertEqual(evaluate("2 4 +").status,6);
	assertEqual(evaluate("2 4 -").status,-2);
	assertEqual(evaluate("2 4 *").status,8);
	assertEqual(evaluate("4 2 /").status,2);
	assert(!evaluate("1 6+").error);
}
void test_evaluate_returns_the_result_of_postfix_operation_for_multiple_operators (){
	assertEqual(evaluate("2 4 6 + *").status,20);
	assertEqual(evaluate("5 4 6 5 + + -").status,-10);
	assertEqual(evaluate("5 4 6 5 8 2 + + + ++").status,30);
}

void test_evaluate_works_fine_with_numbers_not_seperated_by_spaces (){
	assertEqual(evaluate("5 4+").status,9);
}

void test_evaluate_returns_the_result_of_postfix_operation_for_multi_digit_operands (){
	assertEqual(evaluate("20 4 *").status,80);
	assertEqual(evaluate("20000 400 +").status,20400);
}

void test_evaluate_returns_the_result_of_postfix_operation_when_numbers_are_between_opertaors (){
	assertEqual(evaluate("2 4 * 2 +").status,10);
	assertEqual(evaluate("2 2 2 * 2 - 3 + +").status,7);
	assertEqual(evaluate("2 2 2 2 2 * * 2 + + 2 - *").status,20);
	assertEqual(evaluate("2 2 - 2 2 2 * 2 - - -").status,0);
	assertEqual(evaluate("2 2 - 2 2 2 * 2 - - -").error,0);
}

void test_evaluate_returns_error_for_too_few_operands (){
	assertEqual(evaluate("2 +").error,1);
	assertEqual(evaluate("2 5 6+ - /").error,1);
	assertEqual(evaluate("2 5 6+ - / * ").error,1);
}

void test_evaluate_returns_error_for_too_few_operators (){
	assertEqual(evaluate("2 1 6+").error,-1);
	assertEqual(evaluate("2 1 6 7 6 - + /").error,-1);
}

void test_infixToPostfix_returns_the_postfix_of_the_prefix_operation(){
	assertEqual(strcmp(infixToPostfix("2 + 3"),"2 3 +"),0);
}

void test_infixToPostfix_returns_the_postfix_of_the_infix_operation_for_big_expressions(){
	assertEqual(strcmp(infixToPostfix("2 + 3 * 9"),"2 3 9 * +"),0);
}

void test_infixToPostfix_returns_the_postfix_of_the_infix_operation_according_to_precedence(){
	assertEqual(strcmp(infixToPostfix("2 * 3 + 9"),"2 3 * 9 +"),0);
	assertEqual(strcmp(infixToPostfix("2 * 5 + 7"),"2 5 * 7 +"),0);
}

void test_infixToPostfix_returns_the_postfix_of_the_infix_operation_containing_brackets(){
	assertEqual(strcmp(infixToPostfix("3 + 4 * 2 / ( 1 - 5 ) 2 ^ 3"),"3 4 2 * 1 5 - 2 3 ^ / +" ),0);
}

void test_infixToPostfix_returns_the_postfix_of_the_infix_operation_for_multiple_digits(){
	assertEqual(strcmp(infixToPostfix("32 + 4 * 2 / ( 1 - 5 ) 2 ^ 3"),"32 4 2 * 1 5 - 2 3 ^ / +" ),0);
	assertEqual(strcmp(infixToPostfix("3291 + 4 * 2 / ( 1 - 5 ) 2 ^ 3"),"3291 4 2 * 1 5 - 2 3 ^ / +" ),0);
}