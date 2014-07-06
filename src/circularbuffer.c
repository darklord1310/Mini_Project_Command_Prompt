#include "circularbuffer.h"
#include <malloc.h>	 // Need to include this function for the use of malloc
#include "CException.h"
#include <stdio.h>
#include <string.h>

void testing()
{
	CircularBuffer cb;	// This memory allocated will be destroyed after out of the function
	CircularBuffer *ptr2cb;
	
	ptr2cb = malloc(sizeof(CircularBuffer)); // Dynamic memory allocation, allocate the ptr2cb with 
											// the memory size of CircularBuffer structure
											
	free(ptr2cb);	// This will free the memory allocated (beware: data stored in it will loss)
					// if memory is not free, it will still be there forever
}



/*
 * Initialize the circularbuffer
 *
 *Input :
 *					length is the length of the buffer
 */
CircularBuffer *circularBufferNew(int length)
{
	CircularBuffer *circularBuffer;
	
	circularBuffer = malloc(sizeof(CircularBuffer));
	circularBuffer->buffer = malloc(sizeof(int)*length);
	circularBuffer->length = length;
	circularBuffer->size = 0;
	circularBuffer->head = circularBuffer->buffer;
	circularBuffer->tail = circularBuffer->buffer;
	return circularBuffer;
}


/*
 *	To free the buffer memory
 */
void circularBufferDel(CircularBuffer *circularBuffer)
{
	free(circularBuffer);

}


/*
 * Add a new value into the circular buffer
 *
 *Input :
 *					Pointer cb is the pointer which pointed to the CircularBuffer structure
 *					valueToAdd is the value to be added into the CircularBuffer
 * Error checking:
 *					will throw error when trying to add if the circular buffer is full
 */
void CircularBufferAdd(CircularBuffer *cb, char *valueToAdd)
{
	if( cb->size == cb->length)    // If size equals to length means buffer is full
		Throw(ERR_BUFFER_IS_FULL);
	else
	{
		if( cb->size == 0)				// if size=0 means the first value to be added, hence point to tail
		{								
			*(cb->tail) = *valueToAdd;
			cb->size++;
		}
		else
		{
			cb->buffer++;				//  if not the first value in the circularbuffer, then point head to it
			*(cb->buffer) = *valueToAdd;
			cb->head = cb->buffer;
			cb->size++;
		}
	}	
}



/*
 * Remove the tail in circular buffer 
 *
 *Input :
 *					Pointer cb is the pointer which pointed to the CircularBuffer structure
 *	
 *Return :
 *					The value that stored in the tail in circularBuffer
 *
 * Error checking:
 *					will throw error when trying to remove if the circular buffer is empty
 */
char circularBufferRemove(CircularBuffer *cb)
{
	char *removed_value;
	
	if( cb->size == 0)              // Check whether the circularbuffer is empty or not
		Throw(ERR_BUFFER_IS_EMPTY);
	else
	{
			*removed_value = *(cb->tail);  // put the value in the pointer to variable removed_value, then decrement the size and increase the address of tail
			cb->size--;
			cb->tail++;
	}
	return *removed_value;
}