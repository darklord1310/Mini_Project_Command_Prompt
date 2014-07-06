#include "command_prompt.h"
#include <stdio.h>
#include <Windows.h>
#include "circularbuffer.h"

void key_test_backspace(char *string)
{
	printf("%s",string);
	printf("\b");

}

