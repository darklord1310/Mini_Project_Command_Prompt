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
	length_of_input = 0;	// the length of input must be zero at first
	next_status = 0;
	previous_status = 0;
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



//when special key is pressed, it will jump out from getting input from user, hence buffer stop at the last input
void test_user_input_interface_given_abc_and_enter_key_buffer_should_get_abc()
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
	TEST_ASSERT_EQUAL_STRING("abc", user_input);
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
void test_handle_BACKSPACE_given_abcde_should_get_abcd()
{

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
	get_character_ExpectAndReturn(KEY_BACKSPACE); 
	
	// run
	main_command_prompt();
	TEST_ASSERT_EQUAL_STRING("abcd", user_input);
}




// to test the handle backspace function for twice
void test_handle_BACKSPACE_twice_given_abcde_should_get_abc()
{
	
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
	get_character_ExpectAndReturn(KEY_BACKSPACE);	
	get_character_ExpectAndReturn(KEY_BACKSPACE);
	// get_character_ExpectAndReturn('d');
	// put_character_Expect('d');	
	// get_character_ExpectAndReturn(KEY_ENTER);

	// run
	main_command_prompt();
	main_command_prompt();
	// main_command_prompt();
	TEST_ASSERT_EQUAL_STRING("abc", user_input);

}



// to test the handle backspace function when empty input and try to backspace will throw error
// void test_handle_BACKSPACE_thrice_given_ab_should_throw_error()
// {
	// CEXCEPTION_T error;
		
	// mock
	// get_character_ExpectAndReturn('a');
	// put_character_Expect('a');
	// get_character_ExpectAndReturn('b');
	// put_character_Expect('b');
	// get_character_ExpectAndReturn(KEY_BACKSPACE);	
	// get_character_ExpectAndReturn(KEY_BACKSPACE);
	// get_character_ExpectAndReturn(KEY_BACKSPACE);		
	
	// run
	// Try
	// {
		// main_command_prompt();
		// main_command_prompt();
		// main_command_prompt();
		// TEST_FAIL_MESSAGE("Expected error to be generated");
		
	// }Catch(error){
		
		// TEST_ASSERT_EQUAL(ERR_EMPTY_USER_INPUT,error);
		// printf("Error generated : ERR_EMPTY_USER_INPUT");
	// }
// }



void test_initialize_historybuffer_given_length_of_buffer_is_5_should_allocate_length_of_5_to_the_buffer()
{
	initialize_historybuffer(5);
	TEST_ASSERT_EQUAL(5, hb->length);
}



//when user type string of abc and press enter, abc should go into buffer
void test_given_abc_when_handle_ENTER_is_called_should_go_into_buffer()
{
	initialize_historybuffer(3);			//initialize history buffer
	
	//mock
	get_character_ExpectAndReturn('a');
	put_character_Expect('a');
	get_character_ExpectAndReturn('b');
	put_character_Expect('b');
	get_character_ExpectAndReturn('c');
	put_character_Expect('c');
	get_character_ExpectAndReturn(KEY_ENTER);

	//run
	main_command_prompt();
	TEST_ASSERT_EQUAL_STRING("abc", hb->buffer[0]);
}



/* Given strings of abc  1+2  3-4  and each of it is insert into history buffer
 * when enter is press
 * Expect : latest = abc
 * 			end    = abc
 */
void test_given_abc_1plus2_3minus4_when_handle_ENTER_is_called_should_go_into_buffer_respectively()
{
	initialize_historybuffer(3);			//initialize history buffer
	
	//mock
	get_character_ExpectAndReturn('a');
	put_character_Expect('a');
	get_character_ExpectAndReturn('b');
	put_character_Expect('b');
	get_character_ExpectAndReturn('c');
	put_character_Expect('c');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('1');
	put_character_Expect('1');
	get_character_ExpectAndReturn('+');
	put_character_Expect('+');
	get_character_ExpectAndReturn('2');
	put_character_Expect('2');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('3');
	put_character_Expect('3');
	get_character_ExpectAndReturn('-');
	put_character_Expect('-');
	get_character_ExpectAndReturn('4');
	put_character_Expect('4');
	get_character_ExpectAndReturn(KEY_ENTER);

	//run
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	TEST_ASSERT_EQUAL_STRING("abc", hb->buffer[0]);
	TEST_ASSERT_EQUAL_STRING("1+2", hb->buffer[1]);
	TEST_ASSERT_EQUAL_STRING("3-4", hb->buffer[2]);
	TEST_ASSERT_EQUAL_STRING("abc", hb->buffer[0]);
	TEST_ASSERT_EQUAL_STRING("abc", hb->buffer[0]);
}	



/* Given strings of abc  def  ghi  are already inside history buffer
 * Now arrow up key is pressed.
 * Expect:
 *			ghi		return and stored into user_input
 * 			
 */
void test_given_abc_def_ghi_are_inside_history_buffer_when_arrow_up_is_pressed_ghi_should_return_to_user_input()
{
	initialize_historybuffer(3);			//initialize history buffer
	
	//mock
	get_character_ExpectAndReturn('a');
	put_character_Expect('a');
	get_character_ExpectAndReturn('b');
	put_character_Expect('b');
	get_character_ExpectAndReturn('c');
	put_character_Expect('c');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('d');
	put_character_Expect('d');
	get_character_ExpectAndReturn('e');
	put_character_Expect('e');
	get_character_ExpectAndReturn('f');
	put_character_Expect('f');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('g');
	put_character_Expect('g');
	get_character_ExpectAndReturn('h');
	put_character_Expect('h');
	get_character_ExpectAndReturn('i');
	put_character_Expect('i');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_UP);

	//run
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	TEST_ASSERT_EQUAL_STRING("ghi", user_input);
}




/* Given strings of abc  def  ghi  are already inside history buffer
 * Now arrow up key is pressed twice
 * Expect:
 *			def	return and stored into user_input
 * 			
 */
void test_given_abc_def_ghi_are_inside_history_buffer_when_arrow_up_is_pressed_twice_def_should_return_to_user_input()
{
	initialize_historybuffer(3);			//initialize history buffer
		
	//mock
	get_character_ExpectAndReturn('a');
	put_character_Expect('a');
	get_character_ExpectAndReturn('b');
	put_character_Expect('b');
	get_character_ExpectAndReturn('c');
	put_character_Expect('c');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('d');
	put_character_Expect('d');
	get_character_ExpectAndReturn('e');
	put_character_Expect('e');
	get_character_ExpectAndReturn('f');
	put_character_Expect('f');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('g');
	put_character_Expect('g');
	get_character_ExpectAndReturn('h');
	put_character_Expect('h');
	get_character_ExpectAndReturn('i');
	put_character_Expect('i');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_UP);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_UP);

	//run
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	TEST_ASSERT_EQUAL_STRING("def", user_input);
}




/* Given strings of abc  def  ghi  are already inside history buffer
 * Now arrow up key is pressed four times
 * Expect:
 *			abc is returned
 * 			
 */
void test_given_abc_def_ghi_are_inside_history_buffer_when_arrow_up_is_pressed_four_times_should_throw_error()
{
	initialize_historybuffer(3);			//initialize history buffer
		
	//mock
	get_character_ExpectAndReturn('a');
	put_character_Expect('a');
	get_character_ExpectAndReturn('b');
	put_character_Expect('b');
	get_character_ExpectAndReturn('c');
	put_character_Expect('c');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('d');
	put_character_Expect('d');
	get_character_ExpectAndReturn('e');
	put_character_Expect('e');
	get_character_ExpectAndReturn('f');
	put_character_Expect('f');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('g');
	put_character_Expect('g');
	get_character_ExpectAndReturn('h');
	put_character_Expect('h');
	get_character_ExpectAndReturn('i');
	put_character_Expect('i');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_UP);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_UP);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_UP);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_UP);

	//run
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	TEST_ASSERT_EQUAL_STRING("ghi", user_input);
	main_command_prompt();
	TEST_ASSERT_EQUAL_STRING("def", user_input);
	main_command_prompt();
	TEST_ASSERT_EQUAL_STRING("abc", user_input);
	main_command_prompt();
	TEST_ASSERT_EQUAL_STRING("abc", user_input);
}



/* Given strings of abc  def  ghi  are already inside history buffer
 * Now arrow up key is pressed twice
 * Then arrow down is pressed once
 * Expect:
 *			ghi return and store in user_input
 * 			
 */
void test_given_abc_def_ghi_are_inside_history_buffer_when_arrow_up_is_pressed_twice_arrow_down_press_once_ghi_should_store_in_user_input()
{
	initialize_historybuffer(3);			//initialize history buffer
		
	//mock
	get_character_ExpectAndReturn('a');
	put_character_Expect('a');
	get_character_ExpectAndReturn('b');
	put_character_Expect('b');
	get_character_ExpectAndReturn('c');
	put_character_Expect('c');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('d');
	put_character_Expect('d');
	get_character_ExpectAndReturn('e');
	put_character_Expect('e');
	get_character_ExpectAndReturn('f');
	put_character_Expect('f');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('g');
	put_character_Expect('g');
	get_character_ExpectAndReturn('h');
	put_character_Expect('h');
	get_character_ExpectAndReturn('i');
	put_character_Expect('i');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_UP);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_UP);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_DOWN);

	//run
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	TEST_ASSERT_EQUAL_STRING("ghi", user_input);
}




/* Given strings of abc  def  ghi  are already inside history buffer
 * Type ggwp but no enter first
 * Now arrow up key is pressed once
 * Then arrow down is pressed once
 * Expect:
 *			user_input to be ggwp
 * 			
 */
void test_handle_ARROWUP_and_handle_ARROWUP()
{
	initialize_historybuffer(3);			//initialize history buffer
		
	//mock
	get_character_ExpectAndReturn('a');
	put_character_Expect('a');
	get_character_ExpectAndReturn('b');
	put_character_Expect('b');
	get_character_ExpectAndReturn('c');
	put_character_Expect('c');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('d');
	put_character_Expect('d');
	get_character_ExpectAndReturn('e');
	put_character_Expect('e');
	get_character_ExpectAndReturn('f');
	put_character_Expect('f');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('g');
	put_character_Expect('g');
	get_character_ExpectAndReturn('h');
	put_character_Expect('h');
	get_character_ExpectAndReturn('i');
	put_character_Expect('i');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('g');
	put_character_Expect('g');
	get_character_ExpectAndReturn('g');
	put_character_Expect('g');
	get_character_ExpectAndReturn('w');
	put_character_Expect('w');
	get_character_ExpectAndReturn('p');
	put_character_Expect('p');
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_UP);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_DOWN);

	
	//run
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	TEST_ASSERT_EQUAL_STRING("ggwp", user_input);
}




void test_handle_PAGEUP_given_123_456_789_000_when_pagedown_is_pressed_should_get_123()
{
	initialize_historybuffer(5);			//initialize history buffer
		
	//mock
	get_character_ExpectAndReturn('1');
	put_character_Expect('1');
	get_character_ExpectAndReturn('2');
	put_character_Expect('2');
	get_character_ExpectAndReturn('3');
	put_character_Expect('3');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('4');
	put_character_Expect('4');
	get_character_ExpectAndReturn('5');
	put_character_Expect('5');
	get_character_ExpectAndReturn('6');
	put_character_Expect('6');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('7');
	put_character_Expect('7');
	get_character_ExpectAndReturn('8');
	put_character_Expect('8');
	get_character_ExpectAndReturn('9');
	put_character_Expect('9');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('0');
	put_character_Expect('0');
	get_character_ExpectAndReturn('0');
	put_character_Expect('0');
	get_character_ExpectAndReturn('0');
	put_character_Expect('0');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(KEY_PAGEDOWN);

	//run
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	TEST_ASSERT_EQUAL_STRING("123", user_input);
}




void test_handle_PAGEUP_given_123_456_789_000_when_pageup_is_pressed_should_get_000()
{
	initialize_historybuffer(5);			//initialize history buffer
		
	//mock
	get_character_ExpectAndReturn('1');
	put_character_Expect('1');
	get_character_ExpectAndReturn('2');
	put_character_Expect('2');
	get_character_ExpectAndReturn('3');
	put_character_Expect('3');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('4');
	put_character_Expect('4');
	get_character_ExpectAndReturn('5');
	put_character_Expect('5');
	get_character_ExpectAndReturn('6');
	put_character_Expect('6');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('7');
	put_character_Expect('7');
	get_character_ExpectAndReturn('8');
	put_character_Expect('8');
	get_character_ExpectAndReturn('9');
	put_character_Expect('9');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn('0');
	put_character_Expect('0');
	get_character_ExpectAndReturn('0');
	put_character_Expect('0');
	get_character_ExpectAndReturn('0');
	put_character_Expect('0');
	get_character_ExpectAndReturn(KEY_ENTER);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(KEY_PAGEUP);

	//run
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	TEST_ASSERT_EQUAL_STRING("000", user_input);
}




void test_handle_arrow_left_given_123_call_once_should_point_at_2()
{
	initialize_historybuffer(5);			//initialize history buffer
		
	//mock
	get_character_ExpectAndReturn('1');
	put_character_Expect('1');
	get_character_ExpectAndReturn('2');
	put_character_Expect('2');
	get_character_ExpectAndReturn('3');
	put_character_Expect('3');
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_LEFT);

	//run
	main_command_prompt();
	TEST_ASSERT_EQUAL(2 , cursor);
	TEST_ASSERT_EQUAL('3', user_input[cursor]);
}




void test_handle_arrow_left_given_123_call_twice_should_point_at_1()
{
	initialize_historybuffer(5);			//initialize history buffer
		
	//mock
	get_character_ExpectAndReturn('1');
	put_character_Expect('1');
	get_character_ExpectAndReturn('2');
	put_character_Expect('2');
	get_character_ExpectAndReturn('3');
	put_character_Expect('3');
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_LEFT);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_LEFT);

	//run
	main_command_prompt();
	main_command_prompt();
	TEST_ASSERT_EQUAL(1 , cursor);
	TEST_ASSERT_EQUAL('2', user_input[cursor]);
}



// boundary test for handle_ARROWLEFT
void test_handle_arrow_left_given_123_call_thrice_should_point_at_0()
{
	initialize_historybuffer(5);			//initialize history buffer
		
	//mock
	get_character_ExpectAndReturn('1');
	put_character_Expect('1');
	get_character_ExpectAndReturn('2');
	put_character_Expect('2');
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_LEFT);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_LEFT);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_LEFT);
	
	//run
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	TEST_ASSERT_EQUAL(0 , cursor);
	TEST_ASSERT_EQUAL('1', user_input[cursor]);
}



void test_handle_arrow_right_given_string_of_123_cursor_pointed_at_1_call_once_should_point_at_2()
{
	initialize_historybuffer(3);			//initialize history buffer
		
	//mock
	get_character_ExpectAndReturn('1');
	put_character_Expect('1');
	get_character_ExpectAndReturn('2');
	put_character_Expect('2');
	get_character_ExpectAndReturn('3');
	put_character_Expect('3');
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_LEFT);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_LEFT);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_LEFT);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_RIGHT);

	//run
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	main_command_prompt();
	TEST_ASSERT_EQUAL(1 , cursor);
	TEST_ASSERT_EQUAL('2', user_input[cursor]);
}



void test_handle_arrow_right_given_string_of_123_cursor_pointed_at_3_call_once_should_point_at_next_input()
{
	initialize_historybuffer(3);			//initialize history buffer
		
	//mock
	get_character_ExpectAndReturn('1');
	put_character_Expect('1');
	get_character_ExpectAndReturn('2');
	put_character_Expect('2');
	get_character_ExpectAndReturn('3');
	put_character_Expect('3');
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_LEFT);
	get_character_ExpectAndReturn(ESCAPECODE2);
	get_character_ExpectAndReturn(ARROW_RIGHT);

	//run
	main_command_prompt();
	main_command_prompt();
	TEST_ASSERT_EQUAL(3 , cursor);
	TEST_ASSERT_EQUAL('\0', user_input[cursor]);
}
