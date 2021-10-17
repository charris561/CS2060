/*
* Author: Caleb Harris
* Class: CS2060 - 001
* Project: T-Shirt Fundraiser V.01
*
* Problem statement:
* This program will sell T-shirts to the user based on a percentage of sales that 
* goes to an organization that is set every day by an administrator until 
* the administrator closes sales for the day; then gives the administrator a 
* summary of the total sales and funds raised for an organization. 
*/

//preprocessor
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

//constants
const unsigned int MAX_PIN_ATTEMPTS = 3;
const unsigned int VALID_PIN = 81405;
const double MIN_PRICE = 10;
const double MAX_PRICE = 50;
const int ZIP_MIN = 10000;
const int ZIP_MAX = 99999;
#define ADMIN_SIZE 'q'

//function prototypes
//core functions
bool getPin();
double getPrice();
char getUserDecision();
int getPercent();
char selectSize();
char getColor();
double getPayment(double cost);
void printReceipt(char size, char color, double cost, double payment, double totalDonations, int percentDonated);
double calcDonation(int percent, double payment);

//supporting functions
bool validScanf(int scanfReturnVal);
void clrBuff();
void printSize(char sizeChoice);
void printSale(double price, int percent, bool startSequence);


int main(void) {

	double payment = 25;
	char size = 'x';
	char color = 'b';
	double cost = 25;
	double totalDonations = 30;
	int percentdonated = 25;

	printReceipt(size, color, cost, payment, totalDonations, percentdonated);
	

	return EXIT_SUCCESS;

}//end main


/*
* Core functions:
*/

//getPin() function gets pin from user and see's if its correct
bool getPin() {

	bool validEntry = false; //flag to see if pin is valid
	int invalidCount = 0; //counts the number of invalid attempts
	int userEntry = 0; //to store scanf return
	int pin = 0; //stores user inputted pin

	//prompt user and get their input for pin while its not valid and 
	//they haven't reached max attempts
	do {

		printf("%s", "Please enter admin pin number: ");
		userEntry = scanf("%d", &pin);

		//clear input buffer
		clrBuff();

		//is pin correct?
		if (validScanf(userEntry)){
			if (pin == VALID_PIN) { validEntry = true; }
		}

		if (!validEntry) { 
			puts("Invalid Pin.");
			invalidCount++; 
		}

		if (invalidCount == MAX_PIN_ATTEMPTS) { puts("Max invalid pin attempts reached!\n"); }

	} while (!validEntry && invalidCount < MAX_PIN_ATTEMPTS);

	return validEntry;

}//getPin()

//getPrice() funciton returns the value the user enters as the price of the shirt
double getPrice() {

	bool validInput = false; //flag to see if correct price entered
	bool correctPrice = false; //flag to see if correct price was entered
	int userEntry = 0; //stores scanf return value
	double price = 0; //stores the user defined price
	char userChoice = ' '; //stores character user chooses (y or n)

	//get correct price
	do {

		//get valid user input
		do {

			printf("%s", "Please enter a price for the T-shirts: ");
			userEntry = scanf("%lf", &price);
			clrBuff();

			//if validScanf return value and price is within range
			if (validScanf(userEntry) && (price <= MAX_PRICE && price >= MIN_PRICE)) { validInput = true; }
			else { puts("Invalid Price"); }

		} while (!validInput);

		//confirm price is correct
		printf("Is $%.2f the correct price? ", price);
		userChoice = getUserDecision();

		if (userChoice == 'y') { correctPrice = true; }

	} while (!correctPrice);

	//display price
	printf("Price set at: $%.2f\n", price);

	return price;

}//end getPrice

//get y or n function returns a yes or no value from user
char getUserDecision() {

	bool validInput = false; //flag used to tell if the input was valid
	char userChoice = ' '; //used to hold the user's decision
	int userEntry = 0; //used to hold scanf return value

	//get user choice for y or n
	do {

		printf("%s", "(Y)es or (N)o? ");
		userEntry = scanf("%c", &userChoice);
		clrBuff();
		userChoice = tolower(userChoice);
		
		//if valid scanf return and userchoice is a y or n
		if (validScanf(userEntry) && (userChoice == 'y' || userChoice == 'n')) { validInput = true; }
		else { puts("Invalid Entry"); }

	} while (!validInput);

	return userChoice;

}//end getUserDecision()

//get percent function returns the percentage being donated for fundraiser
int getPercent() {

	bool validInput = false; //flag used to see if user input is valid
	bool correctPercent = false; //flag to see if the correct percent entered
	int percent = -1; //percent to be donated to organization
	unsigned int userEntry = 0; //used to store scanf return
	char userChoice = ' '; //used to store y or n for user choice

	//get percentage and return it
	do {

		//get valid user input
		do {

			printf("%s", "Please enter percentage to be donated: ");
			userEntry = scanf("%d", &percent);
			clrBuff();

			//if validScanf return value and price is within range
			if (validScanf(userEntry) && (percent <= 100 && percent >= 0)) { validInput = true; }
			else { 
				puts("Invalid Percentage"); 
				validInput = false;
			}

		} while (!validInput);

		//confirm price is correct
		printf("Is %d%c the correct percentage? ", percent, '%');
		userChoice = getUserDecision();

		if (userChoice == 'y') { correctPercent = true; }
		else { percent = -1; }

	} while (!correctPercent);

	printf("Percentage set to %d%c\n", percent, '%');

	return percent;

}//end getPercent()

//selectSize function gets the user's selected size
char selectSize() {

	bool validInput = false; //flag used to tell if the input was valid
	char userChoice = ' '; //used to hold the user's selected size
	char correctInput = ' '; //used to store y or n
	int userEntry = 0; //used to store scanf return value

	//get user choice for their size
	do {

		printf("%s", "Please select your size (S)mall, (M)edium, (L)arge, (X)tra Large: ");
		userEntry = scanf("%c", &userChoice);
		clrBuff();
		userChoice = tolower(userChoice);

		//if valid scanf return and userchoice is a y or n
		if (validScanf(userEntry)) { 
			switch (userChoice) {

			case 's':
			case 'm':
			case 'l':
			case 'x':
			case ADMIN_SIZE:{
				validInput = true; 
				break;
			}

			default: puts("Invalid Size");

			}//end switch

		}//if scanf valid
		else { puts("Invalid Size"); }

		//if valid, print the size and see if its the one the customer wants
		if (validInput) {

			printf("%s", "You selected: ");
			printSize(userChoice);

			//check to see if it is the size the user wants
			puts("Is this the correct size?");
			correctInput = getUserDecision();

			if (correctInput == 'n') { validInput = false; }

		}//if valid, print size


	} while (!validInput);

	//print size selected
	printf("%s", "Size set to: ");
	printSize(userChoice);

	return userChoice;

}//selectSize()

//getColor() function gets the user selected color
char getColor() {

	bool validInput = false; //flag used to tell if the input was valid
	char userChoice = ' '; //used to hold the user's decision
	int userEntry = 0; //used to hold scanf return value

	//get user choice for color desired
	do {

		printf("%s", "Please select your color (B)lack or (W)hite: ");
		userEntry = scanf("%c", &userChoice);
		clrBuff();
		userChoice = tolower(userChoice);

		//if valid scanf return and userchoice is a y or n
		if (validScanf(userEntry) && (userChoice == 'b' || userChoice == 'w')) { validInput = true; }
		else { puts("Invalid Entry"); }

		//check to see if this is the color the user wanted
		if (userChoice == 'b') {
			printf("%s", "You selected black, is this correct? ");
			if (getUserDecision() == 'n') { validInput = false; }
		}
		else if (userChoice == 'w') {
			printf("%s", "You selected white, is this correct? ");
			if (getUserDecision() == 'n') { validInput = false; }
		}

	} while (!validInput);

	//print final color selection
	if (userChoice == 'b') {
		puts("Color set to black.");
	}
	else if (userChoice == 'w') {
		puts("Color set to white.");
	}

	return userChoice;

}//end getColor

//getPayment() function gets the user payment **will likely have credit card feature added in future
double getPayment(double cost) {

	unsigned int zipcode = 0; //stores user's zip code
	unsigned int userEntry = 0; //stores scanf return value
	double payment = 0; //stores user payment
	bool validInput = false; //flag to see if input was valid

	//get zip code
	do {

		//prompt for zip code
		printf("%s", "Please enter your zip code: ");
		userEntry = scanf("%u", &zipcode);
		clrBuff();

		//allows zip codes min <= zipcode <= max
		if (validScanf(userEntry) && (zipcode <= ZIP_MAX && zipcode >= ZIP_MIN)) { validInput = true; }
		else { puts("Invalid Entry"); }

	} while (!validInput);

	//print zip entered
	printf("Zip Code set to: %u\n", zipcode);

	//get payment
	payment = cost;
	printf("You paid: $%.2f\n", payment);

	return payment;

}//end getPayment()

//printReceipt will print the receipt for the sale
void printReceipt(char size, char color, double cost, double payment, double totalDonations, int percentDonated) {

	int receiptNum = 0;

	//generate receipt number between 1000 and 9999 (4 digits)
	srand(time(0));
	receiptNum = 1000 + rand() % 9999;


	//print receipt
	puts("\n-----------------------------------------------------------------");
	printf("Receipt for order #%d\n", receiptNum);
	puts("-----------------------------------------------------------------");

	//print size
	printf("%s", "Size: ");
	printSize(size);

	//print color
	printf("%s", "Color: ");
	if (color == 'b') {
		puts("Black");
	}
	else if (color == 'w') {
		puts("White");
	}

	//print cost
	printf("Cost: $%.2f\n", cost);

	//print percentage to fundraiser
	printf("Percent donated: %d%c\n", percentDonated, '%');

	//print total amount donated 
	printf("Current amount raised: $%.2f\n", totalDonations);

	puts("\nThank you for donation! Have a great day!");
	puts("-----------------------------------------------------------------\n");

}//end printReceipt

//calcDonations returns the donated amount based on user payment and percent to donate
double calcDonation(int percent, double payment) {

	double donation = 0; //stores the amount of user's payment that will be donated

	//calculate donation
	donation = payment * ((double)percent / 100);

	return donation;

}//end calcDonation


/*
* Assisting Functions:
*/

//validScanf() function validates user input based on valid value passed in
bool validScanf(int scanfReturnVal) {

	bool valid = false;

	//check to see if integer was entered
	if (scanfReturnVal == 0) { valid = false; }

	else { valid = true; }

	return valid;

}//end getInput

//clearBuffer() clears the input buffer
void clrBuff() {
	while ((getchar()) != '\n');
}//end clrBuff()

//print size takes in the user input and prints the size
void printSize(char sizeChoice) {

	switch (sizeChoice) {

	case 's': {
		puts("Small");
		break;
	}
	case 'm': {
		puts("Medium");
		break;
	}
	case 'l': {
		puts("Large");
		break;
	}
	case 'x': {
		puts("Extra Large");
		break;
	}
	case ADMIN_SIZE: {
		puts("Admin Code");
	}

	}

}//printSize()

//print sale details prints the details of the t-shirt sale
void printSale(double price, int percent, bool startSequence) {

	if (startSequence) {
		puts("\n-----------------------------------------------------------------");
		puts("T-shirt sale program setup complete with the following setup:");
		printf("Price: %.2f\nPercent to donate: %d%c\n",
			price, percent, '%');
		puts("-----------------------------------------------------------------\n");
	}

	else {
		puts("\n-----------------------------------------------------------------");
		puts("Welcome to CS2060 T-Shirt Fundraiser! Here are the details for today's sale:");
		printf("Price: %.2f\nPercent being donated: %d%c\n",
			price, percent, '%');
		puts("-----------------------------------------------------------------\n");
	}

}//end printSale()