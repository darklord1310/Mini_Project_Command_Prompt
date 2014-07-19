#include "history_buffer.h"
#include <malloc.h>	 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <CException.h>


int temp_size;

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
	historyBuffer->buffer = calloc(length, sizeof(String));
	historyBuffer->length = length;
	historyBuffer->size = 0;
	historyBuffer->initial = historyBuffer->buffer;
	historyBuffer->end = historyBuffer->buffer;
	historyBuffer->loop =0;
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
	if ( hb->size == 0)
	{
		strcpy(hb->buffer,stringtoadd);
		hb->latest = hb->buffer;
		hb->size++;
	}
	else if (hb->size == hb->length)
	{
		hb->endofsize = hb->buffer;
		hb->latest = hb->initial;
		strcpy(hb->latest,stringtoadd);
		hb->size = 1;
		hb->end+= sizeof(String);
		hb->loop++;
	}
	else if( hb->loop >= 1)
	{
		hb->latest = hb->end;
		strcpy(hb->latest,stringtoadd);
			
		if ( hb->size != 3)
		{
			hb->end+= sizeof(String);
		}
		else
		{
			hb->end = hb->initial;
		}
		hb->size++;
	}
	else
	{
		hb->buffer+= sizeof(String);
		strcpy(hb->buffer,stringtoadd);
		hb->latest = hb->buffer;
		hb->size++;
	}

	 hb->read = hb->latest;
	 temp_size = hb->size;
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
	char *temp;
	temp = hb->read;
	
		
	if ( hb->loop == 0 && temp_size == 0)
		Throw(ERR_NO_MORE_PREVIOUS);	
	else
	{
		hb->read-=sizeof(String);
		temp_size--;
	}
	return temp;
}

