#include "unity.h"
#include "command_prompt.h"
#include "circularbuffer.h"
#define length_of_buffer 250

void setUp(void)
{
}

void tearDown(void)
{
}

void test_string_given_abc_should_return_ab_after_backspace_is_entered(void)
{
	CircularBuffer *cb = circularBufferNew(length_of_buffer);
	CircularBufferAdd(cb,"abc");
	CircularBufferAdd(cb,"xyz");
	CircularBufferAdd(cb,"gg");
	printf("buffer = %c \n", *(cb->buffer--));
	printf("buffer = %c \n", *(cb->buffer--));
	printf("buffer = %c \n", *(cb->buffer--));
}
