#include "command_prompt.h"
#include <stdio.h>
#include <Windows.h>
#include "circularbuffer.h"


/* Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a arrow up key
 *			0 if the input is not an arrow up key
 */
int key_test_arrowup(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == arrow_up)
		return 1;
	else	
		return 0;
}

/* Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a arrow down key
 *			0 if the input is not an arrow  down key
 */
int key_test_arrowdown(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == arrow_down)
		return 1;
	else	
		return 0;
}

/* Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a arrow left key
 *			0 if the input is not an arrow left key
 */
int key_test_arrowleft(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == arrow_left)
		return 1;
	else	
		return 0;
}

/* Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a arrow left key
 *			0 if the input is not an arrow left key
 */
int key_test_arrowright(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == arrow_right)
		return 1;
	else	
		return 0;
}

/* Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a delete key
 *			0 if the input is not a delete key
 */
int key_test_delete(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == key_delete)
		return 1;
	else	
		return 0;
}

/* Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a insert key
 *			0 if the input is not a insert key
 */
int key_test_insert(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == key_insert)
		return 1;
	else	
		return 0;
}

/* Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a home key
 *			0 if the input is not a home key
 */
int key_test_home(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == key_home)
		return 1;
	else	
		return 0;
}


/* Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a pageup key
 *			0 if the input is not a pageup key
 */
int key_test_pageup(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == key_pageup)
		return 1;
	else	
		return 0;
}


/* Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is a pagedown key
 *			0 if the input is not a pagedown key
 */
int key_test_pagedown(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == key_pagedown)
		return 1;
	else	
		return 0;
}



/* Input :
 *         escapecode is the variable which taking in the escape code for a given key
 *		   ascii_code is the variable which taking in the ascii code for a given key
 * Return:
 *			1 if the input is an end key
 *			0 if the input is not an end key
 */
int key_test_end(int escapecode, int ascii_code)
{
	if( (escapecode == 0 || escapecode == 224) && ascii_code == key_end)
		return 1;
	else	
		return 0;
}


void key_test_backspace(char *string)
{
	printf("%s",string);
	printf("\b");
}

