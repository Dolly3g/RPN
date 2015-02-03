#include <stdio.h>
#include "RPN.h"
#include "expr_assert.h"

void test_includes_gives_1_if_given_char_is_present_in_string(){
	assertEqual(isOperator('+'),1);
}

void test_includes_gives_0_if_given_char_is_present_in_string(){
	assertEqual(isOperator('a'),0);
}

void test_creates_a_stack_of_operands_in_the_givenString (){
	char str[] = "2 4 +";
	Stack s = giveStackOfOperands(str);
	assertEqual(*(int*)s.top->data,4);
	assertEqual(*(int*)s.top->next->data,2 );
}

void test_creates_a_stack_of_operands_in_the_givenString_for_2_digit_operands (){
	char str[] = "20 4 +";
	Stack s = giveStackOfOperands(str);
	assertEqual(*(int*)s.top->data,4);
	assertEqual(*(int*)s.top->next->data,20);
}
void test_evaluate_returns_the_result_of_postfix_operation (){
	assertEqual(evaluate("2 4 +"),6);
	assertEqual(evaluate("2 4 -"),-2);
	assertEqual(evaluate("2 4 *"),8);
	assertEqual(evaluate("4 2 /"),2);
}

void test_evaluate_returns_the_result_of_postfix_operation_for_multiple_operators (){
	assertEqual(evaluate("2 4 6 + *"),20);
	assertEqual(evaluate("5 4 6 5 + + -"),-10);
	assertEqual(evaluate("5 4 6 5 8 2 + + + ++"),30);
}

void test_evaluate_works_fine_with_numbers_not_seperated_by_spaces (){
	assertEqual(evaluate("5 4+"),9);
}

void test_evaluate_returns_the_result_of_postfix_operation_for_multi_digit_operands (){
	assertEqual(evaluate("20 4 *"),80);
	assertEqual(evaluate("20000 400 +"),20400);
}

/*void test_evaluate_returns_the_result_of_postfix_operation_when_numbers_are_between_opertaors (){
	assertEqual(evaluate("20 4 * 20 +"),100);
}*/
