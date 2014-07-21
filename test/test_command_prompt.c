#include "unity.h"
#include "command_prompt.h"
#include "history_buffer.h"
#include <stdio.h>
#include <malloc.h>
#include "mock_get_ch.h"
#include "mock_putch.h"
#include "mock_mockspecial_keys.h"

void setUp(void)
{
}

void tearDown(void)
{
}


// when press 1 will return 49 because 49 is the ascii code for number 1
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


// b is not a special key so will return 0
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



//when special key is not pressed, it will jump out from getting input from user, hence buffer stop at the last input
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
	TEST_ASSERT_EQUAL_STRING("abc", temp_buffer);
	TEST_ASSERT_EQUAL( CODE_ENTER, key_return); 
}





void test_mockspecialkeys_given_arrowup_should_call_function_mockARROWUP()
{
	//mock
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_UP);
	mockARROWUP_Expect();


	//run	
	int key = user_input_interface();
	mockspecialkeys(key);
}


void test_mockspecialkeys_given_arrowdown_should_call_function_mockARROWDOWN()
{
	//mock
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_DOWN);
	mockARROWDOWN_Expect();


	//run	
	int key = user_input_interface();
	mockspecialkeys(key);
}


void test_mockspecialkeys_given_arrowright_should_call_function_mockARROWRIGHT()
{
	//mock
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_RIGHT);
	mockARROWRIGHT_Expect();


	//run	
	int key = user_input_interface();
	mockspecialkeys(key);
}


void test_mockspecialkeys_given_arrowleft_should_call_function_mockARROWLEFT()
{
	//mock
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_LEFT);
	mockARROWLEFT_Expect();


	//run	
	int key = user_input_interface();
	mockspecialkeys(key);
}





// to test the handle backspace function
void test_handle_BACKSPACE_given_abcdef_should_get_abcde()
{
	int key_return;  // the variable which will get the code which consists of escape and ascii code
	
	// mock
	get_character_ExpectAndReturn('a');
	put_character_Expect('a');
	get_character_ExpectAndReturn('b');
	put_character_Expect('b');
	get_character_ExpectAndReturn('c');
	put_character_Expect('c');
	get_character_ExpectAndReturn('d');
	put_character_Expect('d');
	get_character_ExpectAndReturn('e');
	put_character_Expect('e');
	get_character_ExpectAndReturn(KEY_ENTER); //it dont matter what key is pass into the function, it just use to get out from the function
	
	// run
	key_return = user_input_interface();
	TEST_ASSERT_EQUAL_STRING("abcde", temp_buffer);
	handle_BACKSPACE();
	TEST_ASSERT_EQUAL_STRING("abcd", temp_buffer);
}




// to test the handle backspace function
void test_handle_BACKSPACE_twice_given_abcde_should_get_abc()
{
	int key_return;  // the variable which will get the code which consists of escape and ascii code
	
	// mock
	get_character_ExpectAndReturn('a');
	put_character_Expect('a');
	get_character_ExpectAndReturn('b');
	put_character_Expect('b');
	get_character_ExpectAndReturn('c');
	put_character_Expect('c');
	get_character_ExpectAndReturn('d');
	put_character_Expect('d');
	get_character_ExpectAndReturn('e');
	put_character_Expect('e');
	get_character_ExpectAndReturn(KEY_ENTER);	//it dont matter what key is pass into the function, it just use to get out from the function
	
	// run
	key_return = user_input_interface();
	TEST_ASSERT_EQUAL_STRING("abcde", temp_buffer);
	handle_BACKSPACE();
	TEST_ASSERT_EQUAL_STRING("abcd", temp_buffer);
	handle_BACKSPACE();
	TEST_ASSERT_EQUAL_STRING("abc", temp_buffer);
}






