#include <stdio.h>
#include <malloc.h>
#include "get_ch.c"
#include "putch.c"


void main()
{
	int escape_code;
	int ascii_code;
	int ans;
	int keycode;
	
	
	//get input
	do
	{
	printf("Enter your key : ");
	escape_code = getch();
	printf("The Key correspond to the escape code is : %d \n", escape_code);
	if( escape_code == 0 || escape_code == 224)
		ascii_code = getch();
	else
		ascii_code = escape_code;
	printf("The Key correspond to the ascii code is : %d \n", ascii_code);
	
	printf("Check for another key? 1 for yes, 0 for no : ");
	scanf("%i", &ans);
	printf("\n");
	printf("\n");
	printf("\n");
	}while( ans != 0);
	
	
	
	
	//getKeyAndStore
	char *temp_buffer , *initial_pos;
	int   key_code , i;
	temp_buffer = malloc(sizeof(char)*1024);	
	initial_pos = temp_buffer;
	
	key_code = get_character();
	*temp_buffer = key_code;
	put_character(*temp_buffer);
	key_code = get_character();
	*(++temp_buffer) = key_code;
	put_character(*temp_buffer);
	key_code = get_character();
	*(++temp_buffer) = key_code;
	put_character(*temp_buffer);
	printf("\n");
	
	for ( i =0 ; i <3 ;i++)
	{
		printf("%c", *initial_pos);
		initial_pos++;
	}

	
	system("pause");
}

