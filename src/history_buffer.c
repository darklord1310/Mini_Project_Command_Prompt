#include "history_buffer.h"
#include "command_prompt.h"
#include <malloc.h>	 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
	historyBuffer->loop    		= 0;
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
		
	hb->buffer[hb->latestIndex++] = strdup(stringtoadd);
	hb->latestIndex = readjustIndex(hb , hb->latestIndex);
	
	if( hb->latestIndex == hb->startIndex)
		hb->startIndex++;
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
	if ( index == hb->length && hb->loop == 0)
	{
		hb->startIndex = 1;
		hb->loop = 1;
		return 0;
	}
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
	hb->latestIndex--;
	hb->currentIndex = hb->latestIndex;
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


