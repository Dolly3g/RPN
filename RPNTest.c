#include <stdio.h>
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

void test_calculate_takes_2_operands_and_an_operator_and_returns_result_of_operation(){
	assertEqual(calculate(2, 4,'+'),6);
	assertEqual(calculate(2, 4,'-'),2);
	assertEqual(calculate(2, 4,'/'),2);
	assertEqual(calculate(2, 4,'*'),8);
}

void test_createToken_creates_a_token_with_given_parameters(){
	Token* t = createToken(1,2,3);
	assertEqual(t->id,1);
	assertEqual(t->start,2);
	assertEqual(t->end,3);
}

void test_getOperatorFromToken_extracts_operator_from_the_token(){
	Token* t = createToken(2,4,4);
	String expr = "2 3 +";
	assertEqual(getOperatorFromToken(expr,t),'+');
}

void test_makeTokenList_gives_the_linked_list_of_tokens_in_the_given_string(){
	LinkedList *list;
	list = makeTokenList("2 3 +");
	assertEqual(list->count,5);
	assertEqual(((Token*)list->head->data)->id,1);
	assertEqual(((Token*)list->tail->data)->id,2);
}

void test_createValueFromSubstr_returns_the_value_from_given_token(){
	Token* t = createToken(2,2,2);
	String expr = "2 3 +";
	assertEqual(createValueFromSubstr(expr,t),3);
}

void test_createValueFromSubstr_returns_the_2digit_value_from_given_token(){
	Token* t = createToken(2,2,3);
	String expr = "2 33 +";
	assertEqual(createValueFromSubstr(expr,t),33);
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
	assert(evaluate("2 2 2 * 2 - 3 + +  == 7").status);
	assert(evaluate("2 2 2 2 2 * * 2 + + 2 - * == 20").status);
	assertEqual(evaluate("2 2 - 2 2 2 * 2 - - -").status,0);
	assertEqual(evaluate("2 2 - 2 2 2 * 2 - - -").error,0);
}

void test_evaluate_returns_error_for_too_few_operands_and_too_many_operators (){
	assertEqual(evaluate("2 +").error,1);
	assertEqual(evaluate("2 5 6+ - /").error,1);
	assertEqual(evaluate("2 5 6+ - / * ").error,1);
}

void test_evaluate_returns_error_for_too_many_operands_and_too_few_operators (){
	assertEqual(evaluate("2 1 6+").error,1);
	assertEqual(evaluate("2 1 * 6+-").error,1);
}
