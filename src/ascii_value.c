#include <stdio.h>
#include <conio.h>


void main()
{
	int escape_code;
	int ascii_code;
	int ans;
	
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
	
	
	system("pause");
}

