#include "unity.h"
#include "command_prompt.h"
#include "circularbuffer.h"
#include <stdio.h>
#include <malloc.h>
#include "mock_get_ch.h"
#include "mock_putch.h"
#define length_of_buffer 250

void setUp(void)
{
}

void tearDown(void)
{
}


void test_get_key_press_given_1_should_return_49()
{
	int return_value;  
		
	//mock
	get_character_ExpectAndReturn('1');
	
	//run
	return_value = get_key_press();
	TEST_ASSERT_EQUAL(49, return_value);
}




void test_is_special_key_given_escape_key_should_return_CODE_ESCAPE()
{
	int return_value;  		// to get the return from get_key_press function
	int status;				// to get the return from is_special_key function
		
	//mock
	get_character_ExpectAndReturn(KEY_ESCAPE);
	
	//run
	return_value = get_key_press();
	status = is_special_key(return_value);
	TEST_ASSERT_EQUAL( CODE_ESCAPE , status);
}



void test_is_special_key_given_arrow_up_should_return_CODE_ARROWUP()
{
	int return_value;  		// to get the return from get_key_press function
	int status;				// to get the return from is_special_key function
		
	//mock
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_UP);
	
	//run
	return_value = get_key_press();
	status = is_special_key(return_value);
	TEST_ASSERT_EQUAL( CODE_ARROWUP , status);
}


void test_is_special_key_given_b_should_return_0()
{
	int return_value;  		// to get the return from get_key_press function
	int status;				// to get the return from is_special_key function
		
	//mock
	get_character_ExpectAndReturn('b');
	
	//run
	return_value = get_key_press();
	status = is_special_key(return_value);
	TEST_ASSERT_EQUAL( 0 , status);
}

void test_user_input_interface_given_abc_and_enter_buffer_should_get_abc()
{
	int key_return;  // the variable which will get the code which consists of escape and ascii code
	
	// mock
	get_character_ExpectAndReturn('a');
	put_character_Expect('a');
	get_character_ExpectAndReturn('b');
	put_character_Expect('b');
	get_character_ExpectAndReturn('c');
	put_character_Expect('c');
	get_character_ExpectAndReturn(KEY_ENTER);
	
	// run
	key_return = user_input_interface();
	TEST_ASSERT_EQUAL_STRING("abc", buffer);
	TEST_ASSERT_EQUAL( CODE_ENTER, key_return); 
}



// void test_backspace_given_abcdef_should_get_abcde()
// {
	// char *buffer = "abcdef";
	// backspace(buffer);
// }



