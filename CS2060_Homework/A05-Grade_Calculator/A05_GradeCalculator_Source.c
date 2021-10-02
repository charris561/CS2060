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
#define STUDENTS 10
#define CATEGORIES 5
#define CLASS_ACTIVITY 0
#define ASSIGNMENT 1
#define PROJECT 2
#define MIDTERM 3
#define FINAL 4

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
void calcGrades(double finalGrades[], const int grades[][STUDENTS], size_t categories, size_t students);
void displayFinalGrades(double grades[], size_t numStudents);

int main(void) {

	//check to make sure all weighted parts are going to equal 100%
	double totalWeight = CLASS_ACTIVITY_WEIGHT + ASSIGNMENT_WEIGHT + PROJECT_WEIGHT + MIDTERM_WEIGHT + FINAL_WEIGHT;

	if (totalWeight == 1) {

		//allocate memory for grades matrix and finalGrades array
		int grades[CATEGORIES][STUDENTS];
		double finalGrades[STUDENTS];

		//initialize all elements to 0 using function
		initArray(grades, CATEGORIES, STUDENTS);

		//initialize final grades to 0
		for (size_t i = 0; i < STUDENTS; i++) {
			finalGrades[i] = 0;
		}

		//get user defined grades
		getGrades(grades, CATEGORIES, STUDENTS);

		//display grades
		displayGrades(grades, CATEGORIES, STUDENTS);

		//calculate final grades
		calcGrades(finalGrades, grades, CATEGORIES, STUDENTS);

		//display the final grades
		displayFinalGrades(finalGrades, STUDENTS);

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

		case CLASS_ACTIVITY:
			printf("Category %d: %s\n", (row + 1), "Class Activity");
			break;

		case ASSIGNMENT:
			printf("Category %d: %s\n", (row + 1), "Assignments");
			break;

		case PROJECT:
			printf("Category %d: %s\n", (row + 1), "Project");
			break;

		case MIDTERM:
			printf("Category %d: %s\n", (row + 1), "Midterm");
			break;

		case FINAL:
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

	}//end row for

}//end displayGrades

//getGrades prompts the user to enter the grades then stores them in the passed in array
void getGrades(int grades[][STUDENTS], size_t categories, size_t students) {

	puts("Please enter class grades: ");

	//iterate through rows
	for (size_t row = 0; row < categories; row++) {

		//display category name
		switch (row) {

		case CLASS_ACTIVITY:
			printf("Category %d: %s\n", (row + 1), "Class Activity");
			break;

		case ASSIGNMENT:
			printf("Category %d: %s\n", (row + 1), "Assignments");
			break;

		case PROJECT:
			printf("Category %d: %s\n", (row + 1), "Project");
			break;

		case MIDTERM:
			printf("Category %d: %s\n", (row + 1), "Midterm");
			break;

		case FINAL:
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

//function calcGrades calculates the final grades for the students based on their grades' weighted average
void calcGrades(double finalGrades[], const int grades[][STUDENTS], size_t categories, size_t students) {

	puts("\nCalculating Grades...\n");

	//initialize control variables
	int j = 0; //counter for finalGrades[]
	double weight = 0;
	double categoryGrade = 0;
	double finalGrade = 0;

	//iterate through all categories for student then go to next student
	for (size_t col = 0; col < students; col++) {

		for (size_t row = 0; row < categories; row++) {

			//switch the row to determine what category we are in and set weight appropriately
			switch (row) {

			case CLASS_ACTIVITY:
				weight = CLASS_ACTIVITY_WEIGHT;
				break;

			case ASSIGNMENT:
				weight = ASSIGNMENT_WEIGHT;
				break;

			case PROJECT:
				weight = PROJECT_WEIGHT;
				break;

			case MIDTERM:
				weight = MIDTERM_WEIGHT;
				break;

			case FINAL:
				weight = FINAL_WEIGHT;
				break;

			}//end switch

			//calculate the category grade
			categoryGrade = weight * grades[row][col];

			//add to final grade
			finalGrade += categoryGrade;

			//if last row (i.e. last category for student)
			if (row == FINAL) {

				//assign finalGrade to array, iterate counter, then reset variable
				finalGrades[j] = finalGrade;
				j++;
				finalGrade = 0;

			}//end if

			//reset control variables
			weight = 0;

		}//end row for

	}//end col for

}//end caldGrades

//function will display the final grades and the class average
void displayFinalGrades(double grades[], size_t numStudents) {

	puts("Student Final Grades: ");

	//initialize necessary variables
	double sum = 0;
	double average = 0;

	//iterate through array and print final grades/ calculate sum
	for (size_t student = 0; student < numStudents; student++) {

		printf("Student %d: %.1f\n", (student + 1), grades[student]);
 		sum += (double)grades[student];

	}//end for

	//calculate average
	average = sum / STUDENTS;

	//print average
	printf("\nClass Average: %.1f\n", average);

}//end displayFinalGrades