#include <stdio.h>
typedef void TestFn(void);
typedef struct{
	char* name; 
	TestFn* fn;
} Test;

//code to be updated starts
TestFn setup,teardown,fixtureSetup,fixtureTearDown,test_createStack_creates_a_stack_with_a_top_and_count,test_push_puts_the_data_on_the_top_of_stack,test_pop_deletes_the_data_from_the_top_of_stack,test_creatStack_initalize_stack_top_filed_null_and_list_has_blank_list,test_push_puts_the_data_in_stack,test_pop_retuns_topmost_element_from_stack;
Test test[] = {"test_createStack_creates_a_stack_with_a_top_and_count",test_createStack_creates_a_stack_with_a_top_and_count,"test_push_puts_the_data_on_the_top_of_stack",test_push_puts_the_data_on_the_top_of_stack,"test_pop_deletes_the_data_from_the_top_of_stack",test_pop_deletes_the_data_from_the_top_of_stack,"test_creatStack_initalize_stack_top_filed_null_and_list_has_blank_list",test_creatStack_initalize_stack_top_filed_null_and_list_has_blank_list,"test_push_puts_the_data_in_stack",test_push_puts_the_data_in_stack,"test_pop_retuns_topmost_element_from_stack",test_pop_retuns_topmost_element_from_stack};
char testFileName[] = {"../StackADT/stackTest.c"};
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