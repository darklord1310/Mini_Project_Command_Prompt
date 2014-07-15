#include "command_prompt.h"
#include <stdio.h>
#include <malloc.h>
#include "get_ch.h"
#include "putch.h"




/*  To check for the input is special key or not
 *	Input  :
 *			 key_code is the ascii code of the input
 *  Return :
 *			 modified key_code of the input will be return
 * 			 modified key_code will be in 2 bytes format
 */
Keycode is_special_key(int key_code)
{
	int upper_byte , lower_byte;
	
	if ( key_code == ESCAPECODE1 || key_code == ESCAPECODE2)
		{
			upper_byte = (key_code<<8);
			lower_byte = get_character();
			key_code = (upper_byte|lower_byte);
			if ( key_code != CODE_ARROWUP && key_code != CODE_ARROWDOWN && key_code != CODE_ARROWLEFT && key_code != CODE_ARROWRIGHT && 
				 key_code != CODE_DELETE1 && key_code != CODE_DELETE2 && key_code != CODE_INSERT1 && key_code != CODE_INSERT2 && 
				 key_code != CODE_PAGEUP1 && key_code != CODE_PAGEUP2 && key_code != CODE_PAGEDOWN1 && key_code != CODE_PAGEDOWN2)
				return 0;
			else	
				return key_code;
		}
	else if( key_code == KEY_ENTER || key_code == KEY_BACKSPACE || key_code == KEY_ESCAPE)
		{
			upper_byte = (NORMALCODE<<8);
			lower_byte = key_code;
			key_code = (upper_byte|lower_byte);
			return key_code;
		}
	else
		return 0;
}


/*  To get a single input
 *  Return :
 *			 ascii code of the input will be return
 * 			
 */
Keycode get_key_press()
{
	int	  key_code;  
		
	key_code = get_character();
	return key_code;
}




/*  Get an string input store inside a buffer and display it on screen, stop when special key is entered 
 *  Return :
 *			 key code of the input will be return
 * 			
 */
Keycode user_input_interface()
{
	int status;
	int key_code;
	int i=0;
	
	while(1)
	{
		key_code = get_key_press();
		status = is_special_key(key_code);
		if (status != 0)		// status !=0 means special character input
			break;
		buffer[i] = key_code;
		put_character(buffer[i]);
		i++;
	}
}



void check_special_keys(int key_code)
{
	switch ( key_code)
	{
		case (CODE_ARROWUP):
				handle_ARROWUP();
				break;
		
		case (CODE_ARROWDOWN):
				handle_ARROWDOWN();
				break;
		
		case (CODE_ARROWLEFT):
				handle_ARROWLEFT();
				break;
		
		case (CODE_ARROWRIGHT):
				handle_ARROWRIGHT();
				break;
		
		case (CODE_HOME1):
				handle_HOME();
				break;
		
		case (CODE_HOME2):
				handle_HOME();
				break;
				
		case (CODE_DELETE1):
				handle_DEL();
				break;
				
		case (CODE_DELETE2):
				handle_DEL();
				break;
		
		case (CODE_PAGEUP1):
				handle_PAGEUP();
				break;
		
		case (CODE_PAGEUP2):
				handle_PAGEUP();
				break;
		
		case (CODE_PAGEDOWN1):
				handle_PAGEDOWN();
				break;
		
		case (CODE_PAGEDOWN2):
				handle_PAGEDOWN();
				break;
		
		case (CODE_INSERT1):
				handle_INSERT();
				break;
		
		case (CODE_INSERT2):
				handle_INSERT();
				break;
				
		case (CODE_END1):
				handle_END();
				break;
		
		case (CODE_END2):
				handle_END();
				break;
				
		case (CODE_ENTER):
				handle_ENTER();
				break;
		
		case (CODE_ESCAPE):
				handle_ESCAPE();
				break;
	}
	
}
	




