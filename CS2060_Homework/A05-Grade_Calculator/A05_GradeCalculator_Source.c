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

//#Define constants
#define STUDENTS 2
#define CATEGORIES 5

//constants
const double CLASS_ACTIVITY_WEIGHT = 0.1;
const double ASSIGNMENT_WEIGHT = 0.3;
const double PROJECT_WEIGHT = 0.3;
const double MIDTERM_WEIGHT = 0.15;
const double FINAL_WEIGHT = 0.15;

//function prototypes
void initArray(int array[][STUDENTS], size_t categories, size_t students);
void displayGrades(const int grades[][STUDENTS], size_t categories, size_t students);
void getGrades(int grades[][STUDENTS], size_t categories, size_t students);

int main(void) {

	//check to make sure all weighted parts are going to equal 100%
	double totalWeight = CLASS_ACTIVITY_WEIGHT + ASSIGNMENT_WEIGHT + PROJECT_WEIGHT + MIDTERM_WEIGHT + FINAL_WEIGHT;

	if (totalWeight == 1) {

		//allocate memory for 2d array
		int grades[CATEGORIES][STUDENTS];

		//initialize all elements to 0 using function
		initArray(grades, CATEGORIES, STUDENTS);

		//get user defined grades
		getGrades(grades, CATEGORIES, STUDENTS);

		//display grades
		displayGrades(grades, CATEGORIES, STUDENTS);

	}//end totalWeight if stmt

	else {
		puts("Total weight of categories does not equal 100%!");
		puts("Exiting program.");
	}

	return EXIT_SUCCESS;

}//main

//function initArray initializes all elements of array to 0
void initArray(int array[][STUDENTS], size_t categories, size_t students) {

	//walk through each element and set to 0
	for (size_t row = 0; row < categories; row++) {

		for (size_t col = 0; col < students; col++) {

			array[row][col] = 0;

		}//end col for loop

	}//end row for loop

}//end initArray()

//funtion displayGrades displays passed in array of grades
void displayGrades(const int grades[][STUDENTS], size_t categories, size_t students) {

	puts("Class Grades: ");
	puts("Format: Student1, Student2, etc...");

	//iterate through categories
	for (size_t row = 0; row < categories; row++) {

		//display category name
		switch (row) {

		case 0:
			printf("Category %d: %s\n", (row + 1), "Class Activity");
			break;

		case 1:
			printf("Category %d: %s\n", (row + 1), "Assignments");
			break;

		case 2:
			printf("Category %d: %s\n", (row + 1), "Project");
			break;

		case 3:
			printf("Category %d: %s\n", (row + 1), "Midterm");
			break;
			
		case 4:
			printf("Category %d: %s\n", (row + 1), "Final");
			break;

		}//end switch

		//iterate through columns
		for (size_t col = 0; col < students; col++) {

			//if last last student, go to next line
			if (col == (students - 1)) {
				printf("%d", grades[row][col]);
				puts("");
			}

			else {
				//prints the grades
				printf("%d, ", grades[row][col]);
			}

		}//end col for

		//inserts a new line
		puts("");

	}//end row for

}//end displayGrades

//getGrades prompts the user to enter the grades then stores them in the passed in array
void getGrades(int grades[][STUDENTS], size_t categories, size_t students) {

	//iterate through rows
	for (size_t row = 0; row < categories; row++) {

		//display category name
		switch (row) {

		case 0:
			printf("Category %d: %s\n", (row + 1), "Class Activity");
			break;

		case 1:
			printf("Category %d: %s\n", (row + 1), "Assignments");
			break;

		case 2:
			printf("Category %d: %s\n", (row + 1), "Project");
			break;

		case 3:
			printf("Category %d: %s\n", (row + 1), "Midterm");
			break;

		case 4:
			printf("Category %d: %s\n", (row + 1), "Final");
			break;

		}//end switch

		//iterate through columns
		for (size_t col = 0; col < students; col++) {

			printf("Enter Grade for student[%d]: ", (col + 1));
			scanf("%d", &grades[row][col]);

		}//end col for

	}//end row for

	//enter a new line
	puts("");

}//end getGrades