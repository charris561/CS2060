/*
* Author: Caleb Harris
* Class: CS2060 - 001
* Project: T-Shirt Fundraiser V.02
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
#include <string.h>

//constants
const unsigned int MAX_PIN_ATTEMPTS = 4;
const unsigned int VALID_PIN = 81405;
const double MIN_PRICE = 20;
const double MAX_PRICE = 50;
const double MIN_PERCENT = 5;
const double MAX_PERCENT = 20;
const unsigned int ZIP_MIN = 10000;
const unsigned int ZIP_MAX = 99999;
const char* COLOR_STRING = { "blac(k), (w)hite, (r)ed, (o)range, (b)lue, (p)urple" };
const char* SIZES_STRING = { "(s)mall, (m)edium, (l)arge, (x)tra Large" };
#define VALID_COLORS {'k', 'w', 'r', 'o', 'b', 'p'}
#define VALID_SIZES {'s', 'm', 'l', 'x', 'q' }
#define MAX_COLORS_OR_SIZES 6
#define ADMIN_SIZE 'q'
#define MAX_DIGITS 2
#define MAX_CREDIT_CARD_SIZE 19

//function prototypes
//core functions
bool getPin();
char getUserDecision();
double getPriceOrPercent(bool isGettingPrice);
char getSizeOrColor(bool isGettingSize);
double getPayment(double cost, int percent);
void printReceipt(char size, char color, double cost, double payment, double totalDonations, int percentDonated);
double calcDonation(int percent, double payment);
void printEndOfDay(double totalSales, double totalDonations);

//supporting functions
bool validScanf(int scanfReturnVal);
void clrBuff();
void printSizeOrColor(char userChoice);
void printSale(double price, int percent, bool startSequence);
char getValidChar(char validChars[]);
bool isValidPriceOrPercent(char* str, double range[]);
bool validateCreditCardNum(char cardNum[]);


int main(void) {

	while (1) {
		getPayment(25, 15);
	}

	double price = 0; //stores admin determined price for t-shirts
	double percent = 0; //stores admin determined percentage to be donated
	bool startSequence = false; //flag to see if program is in start sequence
	bool endOfDay = false; //flag used to see if end of day has been indicated by admin
	double totalDonated = 0; //stores the total amount donated
	double totalPayments = 0; //stores the total payments received
	double payment = 0; //stores the current payment
	char size = ' '; //stores size of shirt
	char color = ' '; //stores the color user wants

	//get pin entry to start selling program
	puts("Welcome to CS2060 T-Shirt Fundraiser Program\n");

	puts("-----------------------------------------------------------------");
	puts("Administrator setup Sequence:");
	puts("-----------------------------------------------------------------");

	//if admin setup pin is correct
	if (getPin()) {

		/*
		* Admin Setup Sequence:
		*/
		//get price for shirts and percentage to be donated
		price = getPriceOrPercent(true);
		percent = getPriceOrPercent(false);
		startSequence = true;
		printSale(price, percent, startSequence);


		/*
		* Customer selling Sequence
		*/
		startSequence = false;

		//get sales while admin exit not started
		do {

			//print the sale
			printSale(price, percent, startSequence);

			//get size
			size = getSizeOrColor(true);

			//if not admin exit code
			if (size != ADMIN_SIZE) {

				//get golor and payment
				color = getSizeOrColor(false);
				payment = getPayment(price, percent);

				//add payment to total payments and calculate donation
				totalPayments += payment;
				totalDonated += calcDonation(percent, payment);

				//prompt user to see if they would like a receipt
				puts("\nWould you like a receipt?");

				//if yes, print receipt
				if (getUserDecision() == 'y') {
					printReceipt(size, color, price, payment, totalDonated, percent);
				}
				else { puts("\nThank you for your donation! Have a great day!"); }

			}//end if NOT admin exit code

			//if size equals admin exit code
			else if (size == ADMIN_SIZE) {

				puts("\nYou have entered the admin menu.");

				//if valid pin
				if (getPin()) { endOfDay = true; }

				//if not valid pin
				else { endOfDay = false; }

			}//end if admin exit size

		} while (!endOfDay);

		//print end of day details
		printEndOfDay(totalPayments, totalDonated);

	}// end core program

	puts("Exiting program");
	

	return EXIT_SUCCESS;

}//end main


/*
* Core functions:
*/

//getPin() function gets pin from user and see's if its correct
bool getPin() {

	bool validEntry = false; //flag to see if pin is valid
	unsigned int invalidCount = 0; //counts the number of invalid attempts
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

		if (invalidCount == MAX_PIN_ATTEMPTS) { puts("\nMax invalid pin attempts reached!\n"); }

	} while (!validEntry && invalidCount < MAX_PIN_ATTEMPTS);

	return validEntry;

}//getPin()

//getPriceOrPercent() funciton returns the value the user enters as the price of the shirt or the percentage to be donated
double getPriceOrPercent(bool isGettingPrice) {

	double priceOrPercent = 0;
	char userSelection[MAX_DIGITS + 1];
	bool validInput = false;
	double num;
	char userChoice = ' ';

	do {

		double validRange[2];//stores the valid range [min, max]

		//if getting price, use fgets to get price from user entry
		if (isGettingPrice) {
			printf("\nPlease enter a price for the T-shirts ($%.2f - $%.2f): ", MIN_PRICE, MAX_PRICE);
			validRange[0] = MIN_PRICE, validRange[1] = MAX_PRICE;
		}

		//else get the percent using fgets
		else {
			printf("\nPlease enter a percent to be donated (%c%.0f - %c%.0f): ", '%', MIN_PERCENT, '%', MAX_PERCENT);
			validRange[0] = MIN_PERCENT, validRange[1] = MAX_PERCENT;
		}

		fgets(userSelection, MAX_DIGITS + 1, stdin);
		clrBuff();

		//validate either price or percent
		if (isValidPriceOrPercent(userSelection, validRange)) {
			validInput = true;
		}
		else { puts("Invalid Entry."); }

		//if valid, convert to double
		if (validInput) {
			char* ptr;
			num = strtod(userSelection, &ptr);

			//confirm with user this is correct value
			
			//if getting percentage
			if (!isGettingPrice) { 
				printf("\nIs %.0f%c the correct percentage? ", num, '%');
			}
			else {
				printf("\nIs $%.2f the correct price? ", num);
			}

			userChoice = getUserDecision();

			if (userChoice == 'y') { validInput = true; }
			else { validInput = false; }
		}

	} while (!validInput);

	priceOrPercent = num;

	return priceOrPercent;

}//end getPriceOrPercent

//get y or n function returns a yes or no value from user
char getUserDecision() {

	bool validInput = false; //flag used to tell if the input was valid
	char userChoice = ' '; //used to hold the user's decision
	int userEntry = 0; //used to hold scanf return value

	//get user choice for y or n
	do {

		printf("\n%s", "(Y)es or (N)o? ");
		userEntry = scanf("%c", &userChoice);
		clrBuff();
		userChoice = tolower(userChoice);
		
		//if valid scanf return and userchoice is a y or n
		if (validScanf(userEntry) && (userChoice == 'y' || userChoice == 'n')) { validInput = true; }
		else { puts("\nInvalid Entry"); }

	} while (!validInput);

	return userChoice;

}//end getUserDecision()

//function getSizeOrColor() gets either the size or the color from the user
char getSizeOrColor(bool isGettingSize) {

	char userSelection = ' '; //stores user selection
	char* type; //stores color or size

	//if getting color
	if (!isGettingSize) {
		//prompt user to get their color
		printf("%s%s%s", "Please select your color (", COLOR_STRING, "): ");

		//get valid color
		char validColors[] = VALID_COLORS;
		userSelection = getValidChar(validColors);
		type = "Color";
	}

	//if getting size
	else {
		//prompt user to get their size
		printf("%s%s%s", "Please select your size (", SIZES_STRING, "): ");

		//get valid size
		char validSizes[] = VALID_SIZES;
		userSelection = getValidChar(validSizes);
		type = "Size";
	}

	printf("%s set to ", type);
	printSizeOrColor(userSelection);

	return userSelection;


}//end getSizeOrColor

//getPayment() function gets the user payment 
double getPayment(double cost, int percent) {

	char creditCardNum[MAX_CREDIT_CARD_SIZE + 1]; //stores user's credit card num
	double payment = 0; //stores user payment
	bool validInput = false; //flag to see if input was valid
	bool validCardNum = false; //flag to see if cardNum is valid

	puts("\n-----------Payment-----------");

	//get credit card number
	do {

		//prompt for credit card number
		printf("\n%s", "Please enter your credit card number: ");
		fgets(creditCardNum, MAX_CREDIT_CARD_SIZE + 1, stdin);		

		//validate number
		if (validateCreditCardNum(creditCardNum)) { validCardNum = true; }
		else {
			puts("\nInvalid Entry.");
		}

	} while (!validCardNum);

	//print if successfully processed payment
	puts("\nSuccessfully processed payment!");

	//get payment and print payment and donation
	payment = cost;
	printf("\nYou paid: $%.2f and donated: $%.2f\n", payment, calcDonation(percent, payment));

	return payment;

}//end getPayment()

//printReceipt will print the receipt for the sale
void printReceipt(char size, char color, double cost, double payment, double totalDonations, int percentDonated) {

	int receiptNum = 0;

	//generate receipt number between 1000 and 9999 (4 digits)
	srand(time(0));
	receiptNum = 1000 + (rand() % 9000);


	//print receipt
	puts("\n-----------------------------------------------------------------");
	printf("Receipt for order #%d\n", receiptNum);
	puts("-----------------------------------------------------------------");

	//print size
	printf("%s", "Size: ");
	printSizeOrColor(size);

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

//printEndOfDay() prints the end of day details
void printEndOfDay(double totalSales, double totalDonations) {

	puts("\n-----------------------------------------------------------------");
	puts("End of day summary: ");
	puts("-----------------------------------------------------------------\n");

	//print total sales and amount raised for organization
	printf("Total sales today: $%.2f\n", totalSales);
	printf("Total donations for organization: $%.2f\n\n", totalDonations);

}//end printEndOFDay()


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

//takes in the user input and prints the size or color
void printSizeOrColor(char userChoice) {

	switch (userChoice) {

	//sizes
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
		break;
	}
	
	//colors
	case 'k': {
		puts("Black");
		break;
	}
	case 'w': {
		puts("White");
		break;
	}
	case 'r': {
		puts("Red");
		break;
	}
	case 'o': {
		puts("Orange");
		break;
	}
	case 'b': {
		puts("Blue");
		break;
	}
	case 'p': {
		puts("Purple");
		break;
	}

	}

}//printSizeOrColor()

//print sale details prints the details of the t-shirt sale
void printSale(double price, int percent, bool startSequence) {

	if (startSequence) {
		puts("\n-----------------------------------------------------------------");
		puts("T-shirt sale program setup complete with the following setup:");
		printf("Price: $%.2f\nPercent to donate: %d%c\n",
			price, percent, '%');
		puts("-----------------------------------------------------------------\n");
	}

	else {
		puts("\n-----------------------------------------------------------------");
		puts("Welcome to CS2060 T-Shirt Fundraiser! Here are the details for today's sale:");
		printf("Price: $%.2f\nPercent being donated: %d%c\n",
			price, percent, '%');
		puts("-----------------------------------------------------------------\n");
	}

}//end printSale()

//gets a valid char out of passed in array
char getValidChar(char validChars[]) {

	bool validInput = false; //flag to tell if input was valid
	char userChoice = ' '; //used to hold the selection
	char isCorrectInput = ' '; //used to store y or n per user's validation of entry
	int userEntry = 0; //holds scanf return value

	do {

		userEntry = scanf("%c", &userChoice);
		clrBuff();
		userChoice = tolower(userChoice);

		//if valid scanf return
		if (validScanf(userEntry)) {
			
			//see if userChoice equals a characterin passed in array
			for (size_t i = 0; i < MAX_COLORS_OR_SIZES; i++) {
				if (!validInput && validChars[i] != NULL) {
					if (userChoice == validChars[i]) { validInput = true; }
				}
			}

			//if not in array, let user know invalid data was entered
			if (!validInput) { puts("Invalid Entry"); }

		}

		//confirm choice with user
		if (validInput) {

			printf("\nYou selected: ");
			printSizeOrColor(userChoice);
			puts("Is this correct?");
			isCorrectInput = getUserDecision();

			if (isCorrectInput == 'n') { 
				validInput = false;
				puts("Please select a new entry.");
			}

		}

	} while (!validInput);

	return userChoice;

}//end getValidChar

//sees if a string of numbers is inside of correct range
bool isValidPriceOrPercent(char* str, double range[]) {

	bool validInput = false;
	char* ptr;
	double min = range[0];
	double max = range[1];
	double num = strtod(str, &ptr);

	//see if str is digit
	if (num != 0 && ptr != str) { 

		//check to see if number is in range
		if (num > min && num < max) { validInput = true; }

	}

	return validInput;

}//end isValidPriceOrPercent

//sees if a credit card number is valid
bool validateCreditCardNum(char cardNum[]) {

	bool validCardNum = true;
	int i = 0;

	//make sure card num is in format ####-####-####-####
	while (validCardNum && i < MAX_CREDIT_CARD_SIZE) {

		//make sure there is not a null value in index
		if (cardNum[i] != NULL) {

			//check to see if end of data reached
			if (cardNum[i] != '\0') {

				//check to see if value is not a digit
				if (!isdigit(cardNum[i])) {

					//check to see if index is not one of the '-'
					if (i != 4 && i != 9 && i != 14) {
						validCardNum = false;
					}

				}

			}

		}

		//check to see if '-' are in string
		if (cardNum[4] != '-' || cardNum[9] != '-' || cardNum[14] != '-') {
			validCardNum = false;
		}

		//iterate i
		i++;

	}

	return validCardNum;

}//validateCreditCardNum