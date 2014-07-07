#include "command_prompt.h"
#include <stdio.h>
#include <Windows.h>
#include <malloc.h>
#include "circularbuffer.h"
#include "get_ch.h"
#include "putch.h"
#include <string.h>

/* Test to read for the arrow up key
 * Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a arrow up key
 *			0 if the input is not an arrow up key
 */
int read_arrowup(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == arrow_up)
		return 1;
	else	
		return 0;
}




/* Test to read for the arrow down key
 * Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a arrow down key
 *			0 if the input is not an arrow  down key
 */
int read_arrowdown(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == arrow_down)
		return 1;
	else	
		return 0;
}




/* Test to read for the arrow left key
 * Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a arrow left key
 *			0 if the input is not an arrow left key
 */
int read_arrowleft(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == arrow_left)
		return 1;
	else	
		return 0;
}



/* Test to read for the arrow right key 
 * Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a arrow left key
 *			0 if the input is not an arrow left key
 */
int read_arrowright(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == arrow_right)
		return 1;
	else	
		return 0;
}




/* Test to read for the DELETE key
 * Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a delete key
 *			0 if the input is not a delete key
 */
int read_delete(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == key_delete)
		return 1;
	else	
		return 0;
}




/* Test to read for the INSERT key
 * Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a insert key
 *			0 if the input is not a insert key
 */
int read_insert(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == key_insert)
		return 1;
	else	
		return 0;
}




/* Test to read for the HOME key
 * Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a home key
 *			0 if the input is not a home key
 */
int read_home(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == key_home)
		return 1;
	else	
		return 0;
}



/* Test to read for the pageup key
 * Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a pageup key
 *			0 if the input is not a pageup key
 */
int read_pageup(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == key_pageup)
		return 1;
	else	
		return 0;
}




/* Test to read for the pagedown key
 * Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a pagedown key
 *			0 if the input is not a pagedown key
 */
int read_pagedown(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == key_pagedown)
		return 1;
	else	
		return 0;
}



/* Test to read for the END key
 * Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is an end key
 *			0 if the input is not an end key
 */
int read_end(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == key_end)
		return 1;
	else	
		return 0;
}



/* Test to read for the ENTER key
 * Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is an enter key
 *			0 if the input is not an enter key
 */
int read_enter(int escapecode, int ascii_code)
{
	if( escapecode == key_enter  && ascii_code == key_enter)
		return 1;
	else	
		return 0;
}



/* Test to read for the BACKSPACE key
 * Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a backspace key
 *			0 if the input is not a backspace key
 */
int read_backspace(int escapecode, int ascii_code)
{
	if( escapecode == key_backspace  && ascii_code == key_backspace)
		return 1;
	else	
		return 0;
}




void check_for_special_key(int escapecode, int ascii_code)
{
	

	
}




/*  To get an string input and save it into buffer 
 *  Return :     
 * 			Keycode is the escape and ascii code for the special keys
 *			where upper byte is escape code and lower byte is ascii code
 */
Keycode get_key_and_store(char *temp_buffer)
{
	int   key_code , upper_byte , lower_byte;
		
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




/*  To perform backspace
 *  Input :     
 * 			string is a pointer that will point to a buffer of character
 *
 */
void backspace(char *string)
{
	int buffer_length;
	char *temp_string ;
	temp_string = malloc(sizeof(char)*1024);
	buffer_length = strlen(string);
	strncpy(temp_string, string, (buffer_length-1));
	temp_string[buffer_length-1] = '\0';
	string = temp_string;

	printf("%s \n",string);
	// printf("\b");
}

