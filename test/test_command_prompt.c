#include "unity.h"
#include "command_prompt.h"
#include "circularbuffer.h"
#include <stdio.h>
#include "mock_get_ch.h"
#include "mock_putch.h"
#define length_of_buffer 250

void setUp(void)
{
}

void tearDown(void)
{
}

// testing for arrow up
void test_read_arrowup_given_escape_code_224_ascii_code_arrow_up_should_return_1()
{
	int result;
	result = read_arrowup(224, arrow_up);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_arrowup_given_escape_code_0_ascii_code_arrow_up_should_return_1()
{
	int result;
	result = read_arrowup(0, arrow_up);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_arrowup_given_escape_code_224_ascii_code_99_should_return_0()
{
	int result;
	result = read_arrowup(224, 99);
	TEST_ASSERT_EQUAL(0, result);
}



// testing for arrow down
void test_read_arrowdown_given_escape_code_224_ascii_code_arrow_down_should_return_1()
{
	int result;
	result = read_arrowdown(224, arrow_down);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_arrowdown_given_escape_code_0_ascii_code_arrow_down_should_return_1()
{
	int result;
	result = read_arrowdown(0, arrow_down);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_arrowdown_given_escape_code_224_ascii_code_33_should_return_0()
{
	int result;
	result = read_arrowdown(224, 33);
	TEST_ASSERT_EQUAL(0, result);
}



// testing for arrow left
void test_read_arrowleft_given_escape_code_224_ascii_code_arrow_left_should_return_1()
{
	int result;
	result = read_arrowleft(224, arrow_left);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_arrowleft_given_escape_code_0_ascii_code_arrow_left_should_return_1()
{
	int result;
	result = read_arrowleft(0, arrow_left);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_arrowleft_given_escape_code_224_ascii_code_12_should_return_0()
{
	int result;
	result = read_arrowleft(224, 12);
	TEST_ASSERT_EQUAL(0, result);
}



// testing for arrow right
void test_read_arrowright_given_escape_code_224_ascii_code_arrow_right_should_return_1()
{
	int result;
	result = read_arrowright(224, arrow_right);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_arrowright_given_escape_code_0_ascii_code_arrow_right_should_return_1()
{
	int result;
	result = read_arrowright(0, arrow_right);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_arrowright_given_escape_code_224_ascii_code_9_should_return_0()
{
	int result;
	result = read_arrowright(224, 9);
	TEST_ASSERT_EQUAL(0, result);
}



// testing for delete key
void test_read_delete_given_escape_code_224_ascii_code_key_delete_should_return_1()
{
	int result;
	result = read_delete(224, key_delete);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_delete_given_escape_code_0_ascii_code_key_delete_should_return_1()
{
	int result;
	result = read_delete(0, key_delete);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_delete_given_escape_code_224_ascii_code_1_should_return_0()
{
	int result;
	result = read_delete(224, 1);
	TEST_ASSERT_EQUAL(0, result);
}




// testing for insert key
void test_read_insert_given_escape_code_224_ascii_code_key_insert_should_return_1()
{
	int result;
	result = read_insert(224, key_insert);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_insert_given_escape_code_0_ascii_code_key_insert_should_return_1()
{
	int result;
	result = read_insert(0, key_insert);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_insert_given_escape_code_224_ascii_code_0_should_return_0()
{
	int result;
	result = read_insert(224, 0);
	TEST_ASSERT_EQUAL(0, result);
}




// testing for home key
void test_read_home_given_escape_code_224_ascii_code_key_home_should_return_1()
{
	int result;
	result = read_home(224, key_home);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_home_given_escape_code_0_ascii_code_key_home_should_return_1()
{
	int result;
	result = read_home(0, key_home);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_home_given_escape_code_224_ascii_code_87_should_return_0()
{
	int result;
	result = read_home(224, 87);
	TEST_ASSERT_EQUAL(0, result);
}



// testing for pageup key
void test_read_pageup_given_escape_code_224_ascii_code_key_pageup_should_return_1()
{
	int result;
	result = read_pageup(224, key_pageup);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_pageup_given_escape_code_0_ascii_code_key_pageup_should_return_1()
{
	int result;
	result = read_pageup(0, key_pageup);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_pageup_given_escape_code_224_ascii_code_23_should_return_0()
{
	int result;
	result = read_pageup(224, 23);
	TEST_ASSERT_EQUAL(0, result);
}



// testing for pagedown key
void test_read_pagedown_given_escape_code_224_ascii_code_key_pagedown_should_return_1()
{
	int result;
	result = read_pagedown(224, key_pagedown);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_pagedown_given_escape_code_0_ascii_code_key_pagedown_should_return_1()
{
	int result;
	result = read_pagedown(0, key_pagedown);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_pagedown_given_escape_code_224_ascii_code_23_should_return_0()
{
	int result;
	result = read_pagedown(224, 23);
	TEST_ASSERT_EQUAL(0, result);
}

// testing for end key
void test_read_end_given_escape_code_224_ascii_code_key_end_should_return_1()
{
	int result;
	result = read_end(224, key_end);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_end_given_escape_code_0_ascii_code_key_end_should_return_1()
{
	int result;
	result = read_end(0, key_end);
	TEST_ASSERT_EQUAL(1, result);
}

void test_read_end_given_escape_code_224_ascii_code_19_should_return_0()
{
	int result;
	result = read_end(224, 19);
	TEST_ASSERT_EQUAL(0, result);
}



// testing for enter key
void test_read_enter_given_escape_code_and_ascii_code_both_are_key_enter_should_return_1()
{
	int result;
	result = read_enter(key_enter, key_enter);
	TEST_ASSERT_EQUAL(1, result);
}



// testing for backspace key
void test_read_backspace_given_escape_code_and_ascii_code_both_are_key_backspace_should_return_1()
{
	int result;
	result = read_backspace(key_backspace, key_backspace);
	TEST_ASSERT_EQUAL(1, result);
}


void test_getKeyAndStore()
{
	int key_return;
	char *buffer;
	buffer = malloc(sizeof(char)*1024);
		
	//mock
	get_character_ExpectAndReturn('a');
	put_character_Expect('a');
	get_character_ExpectAndReturn('b');
	put_character_Expect('b');
	get_character_ExpectAndReturn('c');
	put_character_Expect('c');
	get_character_ExpectAndReturn(escapecode2);
	get_character_ExpectAndReturn(arrow_up);
	
	//run
	key_return = get_key_and_store(buffer);
	TEST_ASSERT_EQUAL(0xE048 , key_return); 
}



// void test_string_given_abc_should_return_ab_after_backspace_is_entered(void)
// {
	// CircularBuffer *cb = circularBufferNew(length_of_buffer);
	// CircularBufferAdd(cb,"abc");
	// CircularBufferAdd(cb,"xyz");
	// CircularBufferAdd(cb,"gg");
	// printf("buffer = %c \n", *(cb->buffer--));
	// printf("buffer = %c \n", *(cb->buffer--));
	// printf("buffer = %c \n", *(cb->buffer--));
// }
