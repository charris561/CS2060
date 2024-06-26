/*
* Author: Caleb Harris
* Class/Section: CS2060-01
* Title: Assignment 06 - Random Sentence Generator
* 
* Program Description: This program will generate defined number of 
* sentences with pre-defined words of different categories.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

//define constats
#define NUM_SENTENCES 20
#define MAX_SENT_LENGTH 50

//preprocessor
int getRandNum();
void getWord(int randNum, char* output, const char* words[], bool firstWord, bool lastWord);
void getSentence(char* output, const char* articles[], const char* nouns[], const char* verbs[], const char* prepositions[]);
void clrOut(char* output);

int main(void) {

	//define all words necessary and output string
	const char* articlePtr[5] = { "the", "a", "one", "some", "any" };
	const char* nounPtr[5] = { "baby", "bunny", "dog", "town", "car" };
	const char* verbPtr[5] = { "drove", "jumped", "ran", "walked", "skipped" };
	const char* prepositionPtr[5] = { "to", "from", "over", "under", "on" };
	char output[MAX_SENT_LENGTH] = {""};

	//initialize file pointer and open file
	FILE* fptr;
	fptr = fopen("randomSentences.txt", "w");

	//check if file opened correctly
	if (fptr == NULL) { puts("File could not be read, exiting.");}

	else {

		//seed rand()
		srand(time(0));

		//write sentences to file
		for (int i = 0; i < NUM_SENTENCES; i++) {

			//create sentence and store in output
			getSentence(output, articlePtr, nounPtr, verbPtr, prepositionPtr);
			fprintf(fptr, "%s\n", output);

			//clears the output
			clrOut(output);

		}//end writing sentences

		//close file
		fclose(fptr);

	}//end if file opened correctly
	

	return EXIT_SUCCESS;

}//end main

//getRandNum gets a random number between 0 - 4
int getRandNum() {

	//initialize
	int randNum = 0;

	//make randNum 0 - 4
	randNum = (rand() % 5);

	return randNum;

}//end getRandNum

//gets a word from possible words and random number
void getWord(int randNum, char* output, const char* words[], bool firstWord, bool lastWord) {

	//concatenate word with output
	strcat(output, words[randNum]);

	//if last, add period, if first capitalize then add space, else add space
	if (lastWord) {
		strcat(output, ".");
	}
	else if (firstWord) {
		output[0] = toupper(output[0]);
		strcat(output, " ");
	}
	else {
		strcat(output, " ");
	}

}//end getNoun

//get words in order of article, noun, verb, preposition, article, noun and store in output
void getSentence(char* output, const char* articles[], const char* nouns[], const char* verbs[], const char* prepositions[]) {

	getWord(getRandNum(), output, articles,true, false); //first word true, last word false
	getWord(getRandNum(), output, nouns, false, false);
	getWord(getRandNum(), output, verbs, false, false);
	getWord(getRandNum(), output, prepositions, false, false);
	getWord(getRandNum(), output, articles, false, false);
	getWord(getRandNum(), output, nouns,false, true); //first word false, last word true

}//end getSentence

//clears output string
void clrOut(char* output) {

	//assigns null character to each index
	for (size_t i = 0; i < MAX_SENT_LENGTH; i++) {
		output[i] = '\0';
	}

}//end clrOut