#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "get_ch.h"
#include "putch.h"

#define ARROW_UP 			  72		// will output 2 bytes instead of 1 byte when press, first byte is  224
#define ARROW_DOWN  		  80		// will output 2 bytes instead of 1 byte when press, first byte is  224
#define ARROW_LEFT 			  75		// will output 2 bytes instead of 1 byte when press, first byte is  224
#define ARROW_RIGHT 		  77		// will output 2 bytes instead of 1 byte when press, first byte is  224
#define KEY_DELETE  		  83		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_INSERT 	 		  82		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_PAGEUP  		  73		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_PAGEDOWN 		  81		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_HOME 			  71		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_END 			  79		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define KEY_ENTER			  13		// this is not a special key, only give 1 byte which is 13
#define KEY_BACKSPACE	 	   8		// this is not a special key, only give 1 byte which is 8
#define KEY_ESCAPE			  27	
#define MAX_BUFFER_SIZE		1024		
#define ESCAPECODE1			   0	
#define ESCAPECODE2			 224	
#define NORMALCODE			 255
#define CODE_ARROWUP		 0xE048
#define CODE_ARROWDOWN		 0xE050
#define CODE_ARROWLEFT		 0xE04B
#define CODE_ARROWRIGHT		 0xE04D
#define CODE_DELETE1		 0xE053
#define CODE_DELETE2		 0x0053
#define CODE_INSERT1		 0xE052
#define CODE_INSERT2		 0x0052
#define CODE_PAGEUP1		 0xE049
#define CODE_PAGEUP2		 0x0049
#define CODE_PAGEDOWN1		 0xE051
#define CODE_PAGEDOWN2	     0x0051
#define CODE_HOME1 			 0xE047	
#define CODE_HOME2			 0x0047
#define CODE_END1 			 0xE04F
#define CODE_END2 			 0x004F		
#define CODE_ENTER			 0xFF0D		
#define CODE_BACKSPACE	 	 0xFF08		
#define CODE_ESCAPE			 0xFF1B

typedef int Keycode;

typedef struct
{
	char **buffer;
	int length;
	int currentIndex;
	int latestIndex;
	int startIndex;

}HistoryBuffer;


char user_input[MAX_BUFFER_SIZE];
char latest_input[MAX_BUFFER_SIZE];
int arrow_left_right_status=0;
int end_of_program=0;
int cursor=0;
int previous_status=0;
int next_status=0;
HistoryBuffer *hb;



int readjustIndex(HistoryBuffer *hb , int index); 
HistoryBuffer *historyBufferNew(int length);
void historyBufferDel(HistoryBuffer *hb);
void historyBufferAdd(HistoryBuffer *hb, char stringtoadd[]);
char *historyBufferReadPrevious(HistoryBuffer *hb);
char *historyBufferReadNext(HistoryBuffer *hb);
Keycode get_key_press();  				   // get key press 
Keycode is_special_key(int key_code);	   // check whether input is special key or not
Keycode user_input_interface();
void copystringtochararray(char array[] , char *string);
void mockspecialkeys(int key_code);
void check_special_keys(int key_code);
void handle_BACKSPACE();
void handle_ARROWUP();
void handle_ARROWDOWN();
void handle_ARROWLEFT();
void handle_ARROWRIGHT();
void handle_HOME();
void handle_DEL();
void handle_PAGEUP();
void handle_PAGEDOWN();
void handle_INSERT();
void handle_END();
void handle_ENTER();
int handle_ESCAPE();
void initialize_historybuffer(int length_of_buffer);
void main_command_prompt();
void readjustcursor();
void movecharactersahead(int x, int y);
void movecharactersbackward(int endofinput);
int get_end_of_input();
void consoleClearLine();
void printBuffer(char buffer[]);  
void printBufferTill(char buffer[], int length);




void main()
{
	int length;
	
	printf("Enter the desire history buffer length: ");
	scanf("%i", &length);
	
	initialize_historybuffer(length);
	
	while(end_of_program != 1)
	{
		int keycode =  user_input_interface();
		check_special_keys(keycode);
	}
}



int get_character()
{
	return getch();
}


void put_character(int character)
{
	putchar(character);
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
				 key_code != CODE_PAGEUP1 && key_code != CODE_PAGEUP2 && key_code != CODE_PAGEDOWN1 && key_code != CODE_PAGEDOWN2 &&
				 key_code != CODE_HOME1   && key_code != CODE_HOME2   && key_code != CODE_END1 		&& key_code != CODE_END2)
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
	int status,key_code;
	
	while(1)
	{
		key_code = get_key_press();
		status = is_special_key(key_code);
		if (status != 0)		// status !=0 means special character input	
		{
			if(status == CODE_ENTER);
			{
				if ( status == CODE_ARROWDOWN || status == CODE_ARROWUP);
				else
					copystringtochararray(latest_input, "");
			}
			return status;
		}
				
		user_input[cursor] = key_code;
		put_character(user_input[cursor]);
				
		if(arrow_left_right_status != 1)	//if arrow left and right is not press previously
		{
			cursor++;
			user_input[cursor] = '\0';
		}
		else
			arrow_left_right_status=0;
			
		copystringtochararray(latest_input,user_input);
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





//adjust the cursor to the end of the user input
void readjustcursor()
{
	int i;
	
	while ( user_input[i] != '\0')
	{
		i++;
	}
	
	cursor = i;
}



void consoleClearLine()
{
	int i;
	
	printf("\r");
	for(i=0; i<79;i++)
	{
		printf(" ");
	}
	printf("\r");
}




void printBuffer(char buffer[])
{
	printf("%s", buffer);
}




void printBufferTill(char buffer[], int length)
{
	int i;
	
	printf("\r");
	
	for(i=0; i<length;i++)
	{
		printf("%c", buffer[i]);
	}
}




void movecharactersahead(int x, int y)
{
	while(1)
	{
		user_input[cursor+x] = user_input[cursor+y];
		x++;
		y++;
		if(user_input[cursor+y] == '\0')
		{
			user_input[cursor+x] = '\0';
			break;
		}
	}
}




void movecharactersbackward(int endofinput)
{
	int y=0,x=1;
	
	while(1)
	{
		user_input[endofinput+x] = user_input[endofinput-y];
		if(user_input[endofinput-y] == user_input[cursor])
		{
			user_input[cursor] = get_key_press();
			cursor++;
			break;
		}
		x--;
		y++;
	}
}



//get the index of the end of the input
int get_end_of_input()
{
	int j=0,length=0;
	
	while ( user_input[j] != '\0')
	{
		length++;
		j++;
	}
	return length;
}



/*  To perform backspace
 * 			
 */
void handle_BACKSPACE()
{
	int j=0 , endofinput;
	
	if(user_input[cursor] == '\0')
	{
		endofinput = get_end_of_input();
		user_input[endofinput-1] = '\0';
		cursor--;
	
		if(cursor < 0)
			cursor=0;
	}
	else
	{
		if(cursor != 0)
		{
			movecharactersahead(-1, 0);
			cursor--;
			if(cursor < 0)
				cursor=0;
		}
	}
	
	copystringtochararray(latest_input , user_input);
	consoleClearLine();
	printBuffer(user_input);
}




// To initialize for the historybuffer
void initialize_historybuffer(int length_of_buffer)
{
	hb = historyBufferNew(length_of_buffer);
}




//copy the content of a given string to char array
void copystringtochararray(char array[] , char *string)
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
	consoleClearLine();
	copystringtochararray(user_input,"");
	printBuffer(user_input);
	cursor = 0;		// has to reinitialize length of input to 0 to get new input correctly
}




/* To perform arrow up
 *
 */
void handle_ARROWUP()
{

	char *temp = historyBufferReadPrevious(hb);
	copystringtochararray(user_input, temp);
	readjustcursor();
	consoleClearLine();
	printBuffer(user_input);
	
}




/* To perform arrow down
 *
 */
void handle_ARROWDOWN()
{
	char *temp = historyBufferReadNext(hb);
	copystringtochararray(user_input, temp);
	readjustcursor();
	consoleClearLine();
	printBuffer(user_input);
}




void handle_ARROWRIGHT()
{
	arrow_left_right_status=1;
	
	if( user_input[cursor] != '\0')
		cursor++;
		
	printBufferTill(user_input,cursor);
}



void handle_ARROWLEFT()
{
	arrow_left_right_status=1;
	
	if(cursor != 0)
		cursor--;
	
	printBufferTill(user_input,cursor);
}





void handle_HOME()
{
	cursor = 0;
	consoleClearLine();
	printBuffer(user_input);
	printf("\r");
}




void handle_DEL()
{
	if(user_input[cursor+1] == '\0')
		user_input[cursor] = '\0';
	else
		movecharactersahead(0, 1);
		
	copystringtochararray(latest_input , user_input);
	consoleClearLine();
	printBuffer(user_input);
}




void handle_PAGEDOWN()
{
	if( hb->buffer[hb->startIndex] == NULL)
		copystringtochararray(user_input, latest_input);
	else
	{
		hb->currentIndex = hb->latestIndex;
		hb->currentIndex = readjustIndex(hb , hb->currentIndex-1);
		copystringtochararray(user_input, hb->buffer[hb->currentIndex]);
	}
	consoleClearLine();
	printBuffer(user_input);
}





void handle_PAGEUP()
{
	if( hb->buffer[hb->startIndex] == NULL)
		copystringtochararray(user_input, latest_input);
	else
	{
		hb->currentIndex = hb->startIndex;
		copystringtochararray(user_input, hb->buffer[hb->currentIndex]);
	}
	consoleClearLine();
	printBuffer(user_input);
}




void handle_INSERT()
{
	int endofinput;
	
	endofinput = get_end_of_input();
	movecharactersbackward(endofinput);
	copystringtochararray(latest_input , user_input);
	
	consoleClearLine();
	printBuffer(user_input);
}



void handle_END()
{
	readjustcursor();
	printBufferTill(user_input,cursor);
}



int handle_ESCAPE()
{
	end_of_program = 1;
	return end_of_program;
}


/*
 * Initialize the historybuffer
 *
 *Input :
 *					length is the length of the buffer
 */
HistoryBuffer *historyBufferNew(int length)
{
	HistoryBuffer *historyBuffer;
	historyBuffer = malloc(sizeof(HistoryBuffer));
	historyBuffer->buffer = calloc(sizeof(char*), length);
	historyBuffer->length = length;
	historyBuffer->currentIndex = 0;
	historyBuffer->latestIndex	= 0;
	historyBuffer->startIndex	= 0;
	return historyBuffer;
}


/*
 *	To free the buffer memory
 */
void historyBufferDel(HistoryBuffer *hb)
{
	free(hb);
}



/*
 * Add a new value into the history buffer
 *
 *Input :
 *					Pointer hb is the pointer which pointed to the HistoryBuffer structure
 *					stringtoadd is the string to be added into the HistoryBuffer
 *
 */
void historyBufferAdd(HistoryBuffer *hb, char stringtoadd[])
{
	if ( hb->buffer[hb->latestIndex] != NULL)
		free(hb->buffer[hb->latestIndex]);
	
	if( hb->latestIndex == hb->startIndex)
	{
		if(hb->startIndex == hb->length-1)
			hb->startIndex = 0;
		else if( hb->buffer[hb->startIndex] == NULL);
		else
			hb->startIndex++;
	}
	
	hb->buffer[hb->latestIndex++] = strdup(stringtoadd);
	hb->latestIndex = readjustIndex(hb , hb->latestIndex);
	hb->currentIndex = hb->latestIndex;
}



/*
 * Re-adjust the index of the history buffer
 *
 *Input :
 *					Pointer hb is the pointer which pointed to the HistoryBuffer structure
 *					index is the variable of index that pass into the function
 *
 */
int readjustIndex(HistoryBuffer *hb , int index)
{
	if (index >= hb->length)
		return 0;
	else if( index < 0 )	
		return hb->length-1;
	else
		return index;
}



/*
 * Return the previous string in history buffer 
 *
 *Input :
 *					Pointer hb is the pointer which pointed to the HistoryBuffer structure
 *	
 *Return :
 *					The latest string that stored in the historyBuffer
 *
 */
char *historyBufferReadPrevious(HistoryBuffer *hb)
{
	int latest = hb->latestIndex;
	latest = readjustIndex(hb , latest-1);
	
	if (previous_status == 1)
		return hb->buffer[hb->startIndex];
	
	hb->currentIndex--;
		
	if( hb->currentIndex < 0	&&	hb->buffer[hb->startIndex] == NULL)
	{
		hb->currentIndex = 0;
		return latest_input;
	}
	
	hb->currentIndex = readjustIndex(hb , hb->currentIndex);
	
	if ( hb->currentIndex != latest)	// if the currentIndex is not pointed to latest, then reset the next status to 0
		next_status = 0;
	else	
		next_status = 1;
	
	if( hb->currentIndex == hb->startIndex)
		previous_status = 1;
	
	return hb->buffer[hb->currentIndex];	
}



/*
 * Return the next string in history buffer 
 *
 *Input :
 *					Pointer hb is the pointer which pointed to the HistoryBuffer structure
 *	
 *Return :
 *					The next string that stored in the historyBuffer
 *
 */
char *historyBufferReadNext(HistoryBuffer *hb)
{
	previous_status = 0;  //clear the status to 0 to indicate its not at the end of buffer anymore
	int latest = hb->latestIndex;
	
	if ( next_status == 1)
	{
		hb->currentIndex = hb->latestIndex;
		return latest_input;
	}
	
	if(hb->buffer[hb->startIndex] == NULL || hb->buffer[hb->currentIndex] == NULL)
		return latest_input;

	hb->currentIndex++;
	
	latest = readjustIndex(hb , latest-1);
	hb->currentIndex = readjustIndex(hb , hb->currentIndex);
	
	if (hb->currentIndex == latest)
		next_status = 1;
	
	return hb->buffer[hb->currentIndex];
}
