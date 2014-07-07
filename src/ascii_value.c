#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "get_ch.c"
#include "putch.c"
#define arrow_up 			  72		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define arrow_down  		  80		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define arrow_left 			  75		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define arrow_right 		  77		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define key_delete  		  83		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define key_insert 	 		  82		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define key_pageup  		  73		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define key_pagedown 		  81		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define key_home 			  71		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define key_end 			  79		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define key_enter			  13		// this is not a special key, only give 1 byte which is 13
#define key_backspace	 	   8		// this is not a special key, only give 1 byte which is 8
#define size_temp_buffer 	1024		// size of the temp_buffer is 1024 bytes
#define escapecode1			   0	
#define escapecode2			 224	

typedef int Keycode;


Keycode get_key_and_store(char *temp_buffer);
void backspace(char *string);


void main()
{
	int keycode;
	char *buffer;
	buffer = malloc(sizeof(char)*1024);
	
	
	keycode = get_key_and_store(buffer);
	
	if(keycode == 0x0808)
		backspace(buffer);
	

	printf("buffer is %s  \n", buffer); 
	system("pause");
	
}




Keycode get_key_and_store(char *temp_buffer)
{
	int   key_code , upper_byte , lower_byte;
		
	printf("Enter your expression : ");
	while(1)
	{
		key_code = get_character();
		if ( key_code == escapecode1 || key_code == escapecode2)
		{
			upper_byte = (key_code<<8);
			lower_byte = get_character();
			key_code = (upper_byte|lower_byte);
			return key_code;
		}
		else if( key_code == key_enter || key_code == key_backspace)
		{
			lower_byte = key_code;
			upper_byte = (key_code<<8);
			key_code = (upper_byte|lower_byte);
			return key_code;
		}
		*temp_buffer = key_code;
		put_character(*temp_buffer);
		temp_buffer++;
	}
}



void get_ascii_code()
{
	int escape_code;
	int ascii_code;
	int ans;
	int keycode;
	
	do
	{
	printf("Enter your key : ");
	escape_code = getch();
	printf("The Key correspond to the escape code is : %d \n", escape_code);
	if( escape_code == 0 || escape_code == 224)
		ascii_code = getch();
	else
		ascii_code = escape_code;
	printf("The Key correspond to the ascii code is : %d \n", ascii_code);
	
	printf("Check for another key? 1 for yes, 0 for no : ");
	scanf("%i", &ans);
	printf("\n");
	printf("\n");

	}while( ans != 0);
}


void backspace(char *string)
{
	int buffer_length;
	char *test_string;
	buffer_length = strlen(string);
	
	printf("length is %i", buffer_length);
	strncpy ( test_string, string, 2 );
	printf("buffer is %s  \n", string);
	// printf("\b");
}