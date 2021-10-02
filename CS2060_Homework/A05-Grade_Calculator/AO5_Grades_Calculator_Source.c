/*
* Author: Caleb Harris
* Class: CS2060 - 001
* Assignment: A05 - Grades Calculator
* 
* Problem statement:
* This program will calculate the grades of the user based on 
* grading scheme on our canvas course. 
*/

//preprocessor
#include <stdlib.h>
#include <stdio.h>

//constants
#define int NUM_STUDENTS = 10;
const double CLASS_ACTIVITY_WEIGHT = 0.1;
const double ASSIGNMENT_WEIGHT = 0.3;
const double PROJECT_WEIGHT = 0.3;
const double MIDTERM_WEIGHT = 0.15;
const double FINAL_WEIGHT = 0.15;

int main(void) {

	//check to make sure all weighted parts are going to equal 100%
	double totalWeight = CLASS_ACTIVITY_WEIGHT +
		ASSIGNMENT_WEIGHT + 
		PROJECT_WEIGHT + 
		MIDTERM_WEIGHT + 
		FINAL_WEIGHT;
	if (totalWeight == 1) {

		//write main

	}//end totalWeight if stmt

	else {
		puts("Total weight of categories does not equal 100%!");
		puts("Exiting program.");
	}

	return EXIT_SUCCESS;

}//main