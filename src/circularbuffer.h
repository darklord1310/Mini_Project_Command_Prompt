#ifndef circularbuffer_H
#define circularbuffer_H

typedef enum {ERR_NO_ERROR, ERR_BUFFER_IS_FULL, ERR_BUFFER_IS_EMPTY}ErrorCode;

typedef struct
{
	char *head;
	char *tail;
	int size;
	int length;
	char *buffer;
	
}CircularBuffer;


CircularBuffer *circularBufferNew(int length);
void CircularBufferAdd(CircularBuffer *cb, char *valueToAdd);
void circularBufferDel(CircularBuffer *circularBuffer);
char circularBufferRemove(CircularBuffer *cb);

	
#endif // circularbuffer_H
