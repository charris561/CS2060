
// Practice working with strings and writing to a file
// #1 implement code that will write to a file and test it
// #2 initialize variables and seed random number generator
// #3 create random number and test it
// #4 Use strncpy to copy the random suit chosen into the suit array
// #5 capitalize the first letter

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define LENGTH 10
#define NUMBER 20

int main(void)
{ 
	// #1 create file pointer
	FILE* fptr;
	
	// #2 create an array of pointers called suitPtr
	// to hold the strings for the suits hearts diamonds clubs and spades 
	char* suitPtr[4] = {"hearts", "diamonds", "clubs", "spades"};

	//#2initialize a character array called suit of length 10
	char suit[10] = {' '};
	
	// #2initalize an integer randNum to hold a random number 
	int randNum = 0;

	// #2 seed the random number
	srand(time(0));
	
	//#1 create a file randomSuit.txt. 
	//#1 Exit program if unable to create file 
	fptr = fopen("randomSuit.txt", "w");

	if (fptr == NULL) { puts("File could not be read, exiting"); }
	  
	// else  do the following
	else {
		//loop 20 times to randomly choose a suit
		for (int i = 0; i < 20; i++) {
			//#3 assign the randNum to a random number between 0 and 3
			randNum = (rand() % 3);

			//#4 use strncopy to copy the random suit into the suit array
			strncpy(suit, suitPtr[randNum], sizeof(suit));

			//#5 capitalize first letter of the string in suit array 
			suit[0] = toupper(suit[0]);

			//write suit to the file using fputs
			fprintf(fptr, suit, "%s");

			// write newline to the file using fputs 
			fputs("\n", fptr);

		}

		// #1 close the file
		fclose(fptr);
	}
	
} 



