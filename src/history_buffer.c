#include "history_buffer.h"
#include "command_prompt.h"
#include <malloc.h>	 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char user_input[MAX_BUFFER_SIZE];

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
	if ( index == hb->length)
		return 0;
	else if( index < 0 )	// if currentIndex is -1
	{
		if( hb->buffer[hb->startIndex] != NULL )	// if historybuffer not empty
			return 0;	// will stay at the first buffer
		else
			return -100;	// -100 is the sentinel value where if the historybuffer is empty
	}
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
	if ( hb->currentIndex == 0	&& hb->currentIndex != hb->startIndex)
		hb->currentIndex = hb->length-1;
	else if ( hb->currentIndex == hb->startIndex && hb->startIndex != 0);
	else
		hb->currentIndex--;

	hb->currentIndex = readjustIndex(hb , hb->currentIndex);
	
	if ( hb->currentIndex == -100)
		return user_input;
	else
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
 *Error Checking:
 *					will gives error when no more next string
 */
char *historyBufferReadNext(HistoryBuffer *hb)
{
	
}


