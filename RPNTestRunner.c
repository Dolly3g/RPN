#include <stdio.h>
typedef void TestFn(void);
typedef struct{
	char* name; 
	TestFn* fn;
} Test;

//code to be updated starts
TestFn setup,teardown,fixtureSetup,fixtureTearDown,test_isOperator_tells_whether_given_char_is_operator_or_not,test_isDigit_tells_whether_given_char_is_digit_or_not,test_calculate_takes_2_operands_and_an_operator_and_returns_result_of_operation,test_createToken_creates_a_token_with_given_parameters,test_getOperatorFromToken_extracts_operator_from_the_token,test_makeTokenList_gives_the_linked_list_of_tokens_in_the_given_string,test_createValueFromSubstr_returns_the_value_from_given_token,test_createValueFromSubstr_returns_the_2digit_value_from_given_token,test_evaluate_returns_the_result_of_postfix_operation,test_evaluate_returns_the_result_of_postfix_operation_for_multiple_operators,test_evaluate_works_fine_with_numbers_not_seperated_by_spaces,test_evaluate_returns_the_result_of_postfix_operation_for_multi_digit_operands,test_evaluate_returns_the_result_of_postfix_operation_when_numbers_are_between_opertaors,test_evaluate_returns_error_for_too_few_operands_and_too_many_operators,test_evaluate_returns_error_for_too_many_operands_and_too_few_operators;
Test test[] = {"test_isOperator_tells_whether_given_char_is_operator_or_not",test_isOperator_tells_whether_given_char_is_operator_or_not,"test_isDigit_tells_whether_given_char_is_digit_or_not",test_isDigit_tells_whether_given_char_is_digit_or_not,"test_calculate_takes_2_operands_and_an_operator_and_returns_result_of_operation",test_calculate_takes_2_operands_and_an_operator_and_returns_result_of_operation,"test_createToken_creates_a_token_with_given_parameters",test_createToken_creates_a_token_with_given_parameters,"test_getOperatorFromToken_extracts_operator_from_the_token",test_getOperatorFromToken_extracts_operator_from_the_token,"test_makeTokenList_gives_the_linked_list_of_tokens_in_the_given_string",test_makeTokenList_gives_the_linked_list_of_tokens_in_the_given_string,"test_createValueFromSubstr_returns_the_value_from_given_token",test_createValueFromSubstr_returns_the_value_from_given_token,"test_createValueFromSubstr_returns_the_2digit_value_from_given_token",test_createValueFromSubstr_returns_the_2digit_value_from_given_token,"test_evaluate_returns_the_result_of_postfix_operation",test_evaluate_returns_the_result_of_postfix_operation,"test_evaluate_returns_the_result_of_postfix_operation_for_multiple_operators",test_evaluate_returns_the_result_of_postfix_operation_for_multiple_operators,"test_evaluate_works_fine_with_numbers_not_seperated_by_spaces",test_evaluate_works_fine_with_numbers_not_seperated_by_spaces,"test_evaluate_returns_the_result_of_postfix_operation_for_multi_digit_operands",test_evaluate_returns_the_result_of_postfix_operation_for_multi_digit_operands,"test_evaluate_returns_the_result_of_postfix_operation_when_numbers_are_between_opertaors",test_evaluate_returns_the_result_of_postfix_operation_when_numbers_are_between_opertaors,"test_evaluate_returns_error_for_too_few_operands_and_too_many_operators",test_evaluate_returns_error_for_too_few_operands_and_too_many_operators,"test_evaluate_returns_error_for_too_many_operands_and_too_few_operators",test_evaluate_returns_error_for_too_many_operands_and_too_few_operators};
char testFileName[] = {"RPNTest.c"};
void _setup(){/*CALL_SETUP*/}
void _teardown(){/*CALL_TEARDOWN*/}
void fixtureSetup(){}
void fixtureTearDown(){}
//code to be updated ends

int testCount;
int passCount;
int currentTestFailed;

int assert_expr(int expr, const char* fileName, int lineNumber, const char* expression){
	if(expr) return 0;
	currentTestFailed = 1;
	printf("\t %s : failed at %s:%d\n",expression, fileName,lineNumber);
	return 1;
}
int assert_equal(int val1, int val2, const char* fileName, int lineNumber,const char* expr1,const char* expr2){
	if(val1 == val2) return 0;
	currentTestFailed = 1;
	printf("\t %d == %d: failed in assertEqual(%s,%s) at %s:%d\n",val1,val2,expr1,expr2, fileName,lineNumber);
	return 1;
}

void runTest(char* name, TestFn test){
	testCount++,currentTestFailed=0;
	printf("**  %s\n",name);
	_setup();
		test();
	_teardown();
	if(!currentTestFailed) passCount++;	
}
int main(int argc, char const *argv[]){		
	int i,total = sizeof(test)/sizeof(Test);	
	fixtureSetup();
	testCount=0,passCount=0;
	printf("**------ %s ------\n",testFileName);
	for (i = 0; i < total; ++i)
		runTest(test[i].name,test[i].fn);	
	printf("** Ran %d tests passed %d failed %d\n",testCount,passCount,testCount-passCount);
	fixtureTearDown();	
	return 0;
}