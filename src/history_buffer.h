#ifndef history_buffer_H
#define history_buffer_H
#define LENGTH_OF_BUFFER 4



typedef enum {ERR_NO_MORE_PREVIOUS, ERR_NO_MORE_NEXT}ErrorCode;

typedef struct { char string[1024]; } String;

extern int temp_size;


typedef struct
{
	char *initial;	//initial is the pointer which will always point to the very first location of the buffer
	char *latest;	//latest is the pointer which will always point to the latest string added 
	char *end;		//end is the pointer which will always point to the end of the buffer
	int size;		//size is the size allocated for each element
	int length;		//length is the length of the history where the buffer could remember
	char *buffer;
	char *read;
	char *endofsize;
	int loop;	
	
}HistoryBuffer;


HistoryBuffer *historyBufferNew(int length);
void historyBufferDel(HistoryBuffer *hb);
void historyBufferAdd(HistoryBuffer *hb, char stringtoadd[]);
char *historyBufferReadPrevious(HistoryBuffer *hb);


#endif // history_buffer_H
