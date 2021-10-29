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
void getWord(int randNum, char* output, char* words[], bool firstWord, bool lastWord);
void getSentence(char* output, char* articles[], char* nouns[], char* verbs[], char* prepositions[]);

int main(void) {

	//define all words necessary and output string
	char* articlePtr[5] = { "the", "a", "one", "some", "any" };
	char* nounPtr[5] = { "baby", "bunny", "dog", "town", "car" };
	char* verbPtr[5] = { "drove", "jumped", "ran", "walked", "skipped" };
	char* prepositionPtr[5] = { "to", "from", "over", "under", "on" };
	char output[MAX_SENT_LENGTH] = {""};

	//initialize file pointer and open file
	FILE* fptr;
	fptr = fopen("randomSentences.txt", "w");

	//check if file opened correctly
	if (fptr == NULL) { puts("File could not be read, exiting.");}

	else {

		//write sentences to file
		for (int i = 0; i < NUM_SENTENCES; i++) {

			//create sentence and store in output
			getSentence(output, articlePtr, nounPtr, verbPtr, prepositionPtr);
			printf("%s\n", output);

			//clears the output
			clrOutput(output);

		}//end writing sentences

	}//end if file opened correctly
	

	return EXIT_SUCCESS;

}//end main

//getRandNum gets a random number between 0 - 4
int getRandNum() {

	//initialize and seed the random number
	int randNum = 0;

	//make randNum 0 - 4
	randNum = (rand() % 4);

	return randNum;

}//end getRandNum

//gets a word from possible words and random number
void getWord(int randNum, char* output, char* words[], bool firstWord, bool lastWord) {

	//initialize necessary variables
	
	
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
void getSentence(char* output, char* articles[], char* nouns[], char* verbs[], char* prepositions[]) {

	getWord(getRandNum(), output, articles,true, false); //first word true, last word false
	getWord(getRandNum(), output, nouns, false, false);
	getWord(getRandNum(), output, verbs, false, false);
	getWord(getRandNum(), output, prepositions, false, false);
	getWord(getRandNum(), output, articles, false, false);
	getWord(getRandNum(), output, nouns,false, true); //first word false, last word true

}//end getSentence