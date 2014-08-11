#include <stdio.h>



void consoleClearLine();
void printfBuffer(char buffer[]);
void printBufferTill(char buffer[], int cursor);


void main()
{

}



void printBufferTill(char buffer[], int cursor)
{
	int i;
	
	printf("\r");
	
	for(i=0; i<cursor;i++)
	{
		printf("%c", buffer[i]);
	}
	printf("%i", i);
}


void consoleClearLine()
{
	int i;
	
	printf("\r");
	for(i=0; i<79;i++)
	{
		printf(" ");
	}
	printf("\r");
}


void printfBuffer(char buffer[])
{
	printf("%s", buffer);
}

