#ifndef history_buffer_H
#define history_buffer_H


typedef struct
{
	char *head;
	char *tail;
	int size;
	int length;
	char *buffer;
	
}CircularBuffer;


CircularBuffer *circularBufferNew(int length);
#endif // history_buffer_H
