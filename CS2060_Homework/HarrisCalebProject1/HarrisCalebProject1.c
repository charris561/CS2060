/*
* Program Description: This program will display the
* total number of hours cars were parked and the 
* total amount collected that day
* 
* Author: Caleb Harris
* Class: CS2060 - 001
* Assignment: Project 1
*/

//pre processor
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//function prototypes
int getValidInput();
double calculateCharge(int hoursParked);
void displayDetails(int carsParked, int totalHours, double totalCharge);

//define constants
const int MAX_HOURS = 24;
const int MIN_HOURS = 0;
const double MAX_CHARGE = 10;
const double MIN_CHARGE = 2;
const int EXIT_INPUT = -1;

//main function
int main() {
	
	//introduce the program
	puts("Welcome the the CS2060 Parking Charge Calculator");
	puts("----------");

	//initialize necessary variables
	int hoursParked = 0;
	int carsParked = 0;
	double charge = 0;

	//while not end of user inputs, get more inputs
	bool endOfInputs = false;
	while (!endOfInputs) {

		//get valid user input
		hoursParked = getValidInput();

		if (hoursParked != EXIT_INPUT) {

			//call calculateCharge to calcluate the user's charge
			charge = calculateCharge(hoursParked);

			//iterate the car number
			carsParked++;

			//print current charge, car, and hours parked
			printf("Car: %d\nHours Parked: %d\nCharge: %.2f\n\n", carsParked, hoursParked, charge);

		}//end if

		else {
			//exit input entered
			puts("Finished inputting");
			endOfInputs = true;
		}

	}//end while

	//call display details to display parking details

	//return 0 if successfully ran through main
	return 0;

}//end main

//function getValidInput gets a valid input from the user and returns it
int getValidInput() {

	//initialize variables to be used
	int userInput = 0;
	int hoursParked = 0;
	bool validEntry = false;

	do {

		//prompt user for input
		printf("%s", "Enter hours parked or -1 to quit: ");
		userInput = scanf("%d", &hoursParked);

		//clear input buffer
		while (getchar() != '\n');

		//validate user input
		//if not a number
		if (userInput == 0) {
			puts("You did not enter a number! Please enter a number.");
		}//end if

		//if not the right number range
		else if ((hoursParked < MIN_HOURS) || (hoursParked > MAX_HOURS)) {

			//check if exit number was entered
			if (hoursParked == EXIT_INPUT) {
				validEntry = true;
			}

			else {
				puts("Please enter hours from 0 - 24");
			}

		}//end if

		else if ((hoursParked >= MIN_HOURS) && (hoursParked <= MAX_CHARGE)) {

			//if hoursParked is valid mark validInput as true
			validEntry = true;

		}//endif

	} while (!validEntry);

	//return the valid input
	return hoursParked;

}//end validateInput

//function calculate charge takes in the current charge, and 
//hours parked and outputs the charge
double calculateCharge(int hoursParked) {

	//initialize charge
	double charge = 2;

	//find out what the charge is based on the hours parked
	if (hoursParked > 3) {
		charge += (0.5 * ((double)hoursParked - 3));

		if (charge > MAX_CHARGE) {
			charge = MAX_CHARGE;
		}
	}

	return charge;

}//end calculateCharge

//function displayDetails displays the cars parked, 
//total hours parked, and the total charge
void displayDetails(int carsParked, int totalHours, double totalCharge) {

	//write code to display details here

}//end display details