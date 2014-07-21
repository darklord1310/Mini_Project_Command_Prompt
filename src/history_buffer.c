#include "history_buffer.h"
#include <malloc.h>	 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <CException.h>


int temp_size;
char *read;
char *move_read_ptr;
int end_status = 0;	// 1 will indicate no more previous
					// Remark: end_status must be manually clear once handleENTER function is executed

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
		hb->loop = 1;
	}
	else if( hb->loop >= 1)
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
 *Error Checking:
 *					will gives error when no more previous string
 */
char *historyBufferReadPrevious(HistoryBuffer *hb)
{
	read = move_read_ptr;
	
	if (	(end_status == 1) || (hb->loop == 0 && temp_size == 0) ||  (hb->size ==0 )	)
	{
		Throw(ERR_NO_MORE_PREVIOUS);
	}
	else
	{
		if(hb->loop != 0 && read == hb->end)
		{
			end_status = 1;
			return read;
		}
		if(hb->loop != 0 && temp_size == 0)
		{
			move_read_ptr = hb->endofsize;
			read = move_read_ptr;
		}
		move_read_ptr-=sizeof(String);
		temp_size--;
	}
	return read;
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
	
	if (	(hb->loop == 0 && temp_size == hb->length) || (hb->size == 0)	)
	{		
		Throw(ERR_NO_MORE_NEXT);
	}
	else
	{
		read+=sizeof(String);
		temp_size++;
	}
	return read;
}


