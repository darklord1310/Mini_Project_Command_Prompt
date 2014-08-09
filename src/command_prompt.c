#include "command_prompt.h"
#include "history_buffer.h"
#include <stdio.h>
#include <malloc.h>
#include "get_ch.h"
#include "putch.h"


char user_input[MAX_BUFFER_SIZE];
char latest_input[MAX_BUFFER_SIZE];
int	length_of_input = 0;



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




/*  To get a single key input
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




/*  Get a string input store it inside a buffer and display it on screen, stop when special key is entered 
 *  Return :
 *			 key code of the special key will be return
 * 			
 */
Keycode user_input_interface()
{
	int status, i;
	int key_code;
	
	while(1)
	{
		key_code = get_key_press();
		status = is_special_key(key_code);
		if (status != 0)		// status !=0 means special character input	
			return status;
			
		user_input[length_of_input] = key_code;
		put_character(user_input[length_of_input]);
		length_of_input++;
		user_input[length_of_input] = '\0';
		
		for( i=0 ; user_input[i] != '\0' ; i++)
		{
			latest_input[i] = user_input[i];
		}
		latest_input[i] = '\0';
	}
}




/* The real main command prompt which
 * will be use and seen by user
 */
void main_command_prompt()
{
	int keycode =  user_input_interface();
	check_special_keys(keycode);
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
		case (CODE_BACKSPACE):
				handle_BACKSPACE();
				break;
	}
}





/*This is the function exactly similar to check_special_keys, except
 *this is only for mocking purpose
 */
void mockspecialkeys(int key_code)
{
	switch ( key_code)
	{
		case (CODE_ARROWUP):
				mockARROWUP();
				break;
		
		case (CODE_ARROWDOWN):
				mockARROWDOWN();
				break;
		
		case (CODE_ARROWLEFT):
				mockARROWLEFT();
				break;
		
		case (CODE_ARROWRIGHT):
				mockARROWRIGHT();
				break;
		
		case (CODE_HOME1):
				mockHOME();
				break;
		
		case (CODE_HOME2):
				mockHOME();
				break;
				
		case (CODE_DELETE1):
				mockDEL();
				break;
				
		case (CODE_DELETE2):
				mockDEL();
				break;
		
		case (CODE_PAGEUP1):
				mockPAGEUP();
				break;
		
		case (CODE_PAGEUP2):
				mockPAGEUP();
				break;
		
		case (CODE_PAGEDOWN1):
				mockPAGEDOWN();
				break;
		
		case (CODE_PAGEDOWN2):
				mockPAGEDOWN();
				break;
		
		case (CODE_INSERT1):
				mockINSERT();
				break;
		
		case (CODE_INSERT2):
				mockINSERT();
				break;
				
		case (CODE_END1):
				mockEND();
				break;
		
		case (CODE_END2):
				mockEND();
				break;
				
		case (CODE_ENTER):
				mockENTER();
				break;
		
		case (CODE_ESCAPE):
				mockESCAPE();
				break;
		case (CODE_BACKSPACE):
				mockBACKSPACE();
				break;
	}
}



/*  To perform backspace
 * 			
 */
void handle_BACKSPACE()
{
	int j=0 , length=0;
	
	while ( user_input[j] != '\0')
	{
		length++;
		j++;
	}
	
	if ( length == 0);
	
	user_input[length-1] = '\0';
	length_of_input--;
}



// To initialize for the historybuffer
void initialize_historybuffer(int length_of_buffer)
{
	hb = historyBufferNew(length_of_buffer);
}



//copy the content of a given string to char array
void copystringtocharaary(char array[] , char *string)
{
	int i;
	
	for( i=0 ; string[i] != '\0' ; i++)
	{
		array[i] = string[i];
	}
	array[i] = '\0';
}


/* To perform enter
 *
 */
void handle_ENTER()
{
	historyBufferAdd(hb, user_input);
	length_of_input = 0;		// has to reinitialize length of input to 0 to get new input correctly
}


/* To perform arrow up
 *
 */
void handle_ARROWUP()
{

	char *temp = historyBufferReadPrevious(hb);
	copystringtocharaary(user_input, temp);
}



/* To perform arrow down
 *
 */
void handle_ARROWDOWN()
{
	char *temp;
	temp = historyBufferReadNext(hb);
	copystringtocharaary(user_input, temp);
}



void handle_ARROWRIGHT()
{
	
}


void handle_ARROWLEFT()
{


}



void handle_HOME()
{
}


void handle_DEL()
{

}

void handle_PAGEUP()
{
	int latest = hb->latestIndex;
	latest = readjustIndex(hb , latest-1);
	copystringtocharaary(user_input, hb->buffer[latest]);
}


void handle_PAGEDOWN()
{
	copystringtocharaary(user_input, hb->buffer[hb->startIndex]);
}


void handle_INSERT()
{


}

void handle_END()
{



}


void handle_ESCAPE()
{

}