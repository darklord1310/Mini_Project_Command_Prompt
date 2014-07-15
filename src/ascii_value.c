#include <stdio.h>
#include "get_ch.c"
#include "putch.c"
#include "command_prompt.h"



typedef int Keycode;


void handle_BACKSPACE();


void main()
{
	int key;
	
	do{
	key = user_input_interface();
	check_special_keys(key);
	}while(key!= CODE_ENTER);

	system("pause");
}



/*  To perform backspace
 * 			
 */
void handle_BACKSPACE()
{
	int i=0 , length=0;

	while ( buffer[i] != '\0')
	{
		length++;
		i++;
	}
	buffer[length-1] = '\0';
	system("CLS");
	printf("%s \n", buffer);	
}





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



void check_special_keys(int key_code)
{
	if ( key_code == CODE_BACKSPACE)
		handle_BACKSPACE();
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


