#ifndef command_prompt_H
#define command_prompt_H
#define arrow_up 	72		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define arrow_down  80		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define arrow_left 	75		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define arrow_right 77		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define key_delete  83		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224
#define key_insert  82		// will output 2 bytes instead of 1 byte when press, first byte is either 0 or 224

/*
\a (alert) Produces an audible or visible alert. The active
		   position shall not be changed.

\b (backspace) Moves the active position to the previous
			   position on the current line. If the active position is
			   at the initial position of a line, the behavior is
			   unspecified.

\f (form feed) Moves the active position to the initial
			   position at the start of the next logical page .

\n (new line) Moves the active position to the initial
			  position of the next line.

\r (carriage return) Moves the active position to the
					 initial position of the current line.

\t (horizontal tab) Moves the active position to the next
					horizontal tabulation position on the current line. If
					the active position is at or past the last defined
					horizontal tabulation position, the behavior is
					unspecified.

\v (vertical tab)   Moves the active position to the initial
					position of the next vertical tabulation position. If
					the active position is at or past the last defined
					vertical tabulation position, the behavior is
					unspecified.
*/

void key_test_backspace(char *string);


#endif // command_prompt_H
