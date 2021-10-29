/*
* Author: Caleb Harris
* 
* Description: program is for testing and learnign file I/O
*/

#include <stdio.h>
#include <stdlib.h>


int main(void) {

	/*
	* Writing to file
	*/

	//create a file pointer
	FILE* testWriteFile;

	//open the file for writing
	testWriteFile = fopen("testWrite.txt", "w");

	//write to file
	fputs("Hello world!\n", testWriteFile);
	fputs("This is on a new line!\n", testWriteFile);

	//close the output file
	fclose(testWriteFile);


	/*
	* Reading from file
	*/

	//create file pointer
	FILE* testReadFile;

	//open the file for reading
	testReadFile = fopen("testWrite.txt", "r");

	//check to see if it opened
	if (testReadFile == NULL) { puts("File could not be opened"); }
	
	//read from file and display to console
	else {
		//while eof not read
		while (!feof(testReadFile)) {
			
		}
	}


	return EXIT_SUCCESS;

}