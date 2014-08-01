#include "history_buffer.h"
#include <malloc.h>	 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <CException.h>


char *read;
char *move_read_ptr;


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
	read = NULL;		// initialize read pointer to NULL, if readprevious is not call first
						// then readnext will not return anything
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
		hb->loop = 1;
	}
	else if( hb->loop == 1)
	{
		hb->latest = hb->end;
		strcpy(hb->latest,stringtoadd);
			
		if ( hb->size != hb->length-1)
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
	 
	 move_read_ptr = hb->latest;
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
 *Error Checking:
 *					will gives error when no more previous string
 */
char *historyBufferReadPrevious(HistoryBuffer *hb)
{
	if (	((read == hb->end) && (move_read_ptr == hb->end))  ||  hb->size == 0   )
	{
		Throw(ERR_NO_MORE_PREVIOUS);
	}
	else
	{
		if(move_read_ptr == hb->end)
		{
			read = move_read_ptr;
			return read;
		}
		else if (hb->loop != 0 && move_read_ptr == hb->initial)
		{
			read = move_read_ptr;
			move_read_ptr = hb->endofsize;
			return read;
		}
		else
		{
			read = move_read_ptr;
			move_read_ptr-=sizeof(String);
			return read;
		}
	}
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
	
	if ( read == NULL)
	{		
		Throw(ERR_NO_MORE_NEXT);
	}
	else
	{
		if( read == hb->endofsize)
		{
			move_read_ptr = read;
			read = hb->initial;
			return read;
		}
		else if( read == hb->end)
		{
			read+=sizeof(String);
			return read;
		}
		else if( read == hb->latest)
		{
			move_read_ptr = read;
			read = NULL;
			Throw(ERR_NO_MORE_NEXT);
		}
		else
		{
			move_read_ptr = read;
			read+=sizeof(String);
			return read;
		}
	}
	
}


