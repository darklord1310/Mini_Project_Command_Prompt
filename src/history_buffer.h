#ifndef history_buffer_H
#define history_buffer_H
#define LENGTH_OF_BUFFER 4



typedef enum {ERR_NO_MORE_PREVIOUS, ERR_NO_MORE_NEXT}ErrorCode;

typedef struct { char string[1024]; } String;

extern int temp_size;
extern char *read;
extern char *move_read_ptr;
extern int end_status;

typedef struct
{
	char *initial;	//initial is the pointer which will always point to the very first location of the buffer
	char *latest;	//latest is the pointer which will always point to the latest string added 
	char *end;		//end is the pointer which will always point to the last string
	int size;		//size is the size allocated for each element
	int length;		//length is the length of the history where the buffer could remember
	char *buffer;
	char *endofsize; //pointer which will always point to the last location of the buffer
	int loop;	
	
}HistoryBuffer;


HistoryBuffer *historyBufferNew(int length);
void historyBufferDel(HistoryBuffer *hb);
void historyBufferAdd(HistoryBuffer *hb, char stringtoadd[]);
char *historyBufferReadPrevious(HistoryBuffer *hb);
char *historyBufferReadNext(HistoryBuffer *hb);


#endif // history_buffer_H
