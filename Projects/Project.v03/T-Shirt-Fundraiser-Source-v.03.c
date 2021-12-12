/*
* Author: Caleb Harris
* Class: CS2060 - 001
* Project: T-Shirt Fundraiser V.03
*
* Problem statement:
* This program will sell T-shirts to the user based on a percentage of sales that
* goes to an organization that is set every day by an administrator until
* the administrator closes sales for the day; then gives the administrator a
* summary of the total sales and funds raised for each organization.
*/

//preprocessor
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

//structures
typedef struct Organization {

	//data
	char* orgName;
	double tshirtPrice;
	double percentToDonate;
	double totalDonated;
	double totalSales;

	//node pointers
	struct Organization* nextPtr;

} Organization;

typedef struct Sale {

	char size;
	char color;
	double payment;

} Sale;

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
const char* RECEIPTS_FILE_PATH = "C:\\Dev\\CS2060 - Programming with C\\tshirtapp\\receipt.txt";
const char* END_OF_DAY_FILE_PATH = "C:\\Dev\\CS2060 - Programming with C\\tshirtapp\\tshirtfund.txt";
#define VALID_COLORS {'k', 'w', 'r', 'o', 'b', 'p'}
#define VALID_SIZES {'s', 'm', 'l', 'x', 'q' }
#define MAX_COLORS_OR_SIZES 6
#define ADMIN_SIZE 'q'
#define MAX_CREDIT_CARD_SIZE 19
#define MAX_ORG_NAME_LENGTH 20

//function prototypes
//core functions
bool getPin();
char getUserDecision();
double getPriceOrPercent(bool isGettingPrice);
char getSizeOrColor(bool isGettingSize);
double getPayment(double cost, int percent);
void printReceipt(const Organization chosenOrg, const Sale currentSale);
double calcDonation(double percent, double payment);
void printEndOfDay(const Organization* listPtr);
void getOrgs(Organization** listPtr);
Organization* getOrgToSell(const Organization* listPtr);

//supporting functions
bool validScanf(int scanfReturnVal);
void clrBuff();
char* printSizeOrColor(char userChoice);
void printSale(const Organization* listPtr, bool startSequence);
char getValidChar(const char validChars[]);
bool isValidPriceOrPercent(char* str, double range[]);
bool validateCreditCardNum(const char cardNum[]);


//Linked List Manipulation Functions
void insertNode(Organization** headPtr, char* name, double price, double percent);


int main(void) {

	Organization* orgListHeadPtr = NULL; //holds each organization's data
	bool startSequence = false; //flag to see if program is in start sequence
	bool endOfDay = false; //flag used to see if end of day has been indicated by admin

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
		//get all information for organizations from administrator
		getOrgs(&orgListHeadPtr);
		startSequence = true;
		printSale(orgListHeadPtr, startSequence);


		/*
		* Customer selling Sequence
		*/
		startSequence = false;

		//get sales while admin exit not started
		do {

			//print the sale
			printSale(orgListHeadPtr, startSequence);

			//get organization user wants to buy from
			Organization* chosenOrg = getOrgToSell(orgListHeadPtr);
			
			//initialize current sale
			Sale currentSale = {.color = ' ', .payment = 0, .size = ' '};

			//get size
			currentSale.size = getSizeOrColor(true);

			//if not admin exit code
			if (currentSale.size != ADMIN_SIZE) {

				//get golor and payment
				currentSale.color = getSizeOrColor(false);
				currentSale.payment = getPayment(chosenOrg->tshirtPrice, chosenOrg->percentToDonate);

				//add payment to total payments and calculate donation
				chosenOrg->totalSales += currentSale.payment;
				chosenOrg->totalDonated += calcDonation(chosenOrg->percentToDonate, currentSale.payment);

				//prompt user to see if they would like a receipt
				puts("\nWould you like a receipt?");

				//if yes, print receipt
				if (getUserDecision() == 'y') {
					printReceipt(*chosenOrg, currentSale);
				}
				else { puts("\nThank you for your donation! Have a great day!"); }

			}//end if NOT admin exit code

			//if size equals admin exit code
			else if (currentSale.size == ADMIN_SIZE) {

				puts("\n**********You have entered the admin menu.**********\n");

				//if valid pin
				if (getPin()) { endOfDay = true; }

				//if not valid pin
				else { endOfDay = false; }

			}//end if admin exit size

		} while (!endOfDay);

		//print end of day details
		printEndOfDay(orgListHeadPtr);

		//free memory for organizations list
		free(orgListHeadPtr);

	}// end core program

	puts("\nExiting program");


	return EXIT_SUCCESS;

}//end main


/*
* Core functions:
*/

//gets organizations setup information from administrator
void getOrgs(Organization** listPtr) {

	int scanfRetVal = 0; //stores the scanf return value
	bool validInput = false; //flag to see if user input is valid
	unsigned int numOrgs = 0; //how many organizations there will be

	do {

		//get how many organizations will be entered
		printf("%s", "\nHow many organizations will be set up? ");
		scanfRetVal = scanf("%u", &numOrgs);
		clrBuff();

		if (validScanf(scanfRetVal) && numOrgs > 0) { validInput = true; }
		else { puts("Invalid Entry"); }

	} while (!validInput);

	//initialize variables to store price and percent
	double price = 0;
	double percent = 0;
	char** orgNames = malloc(numOrgs * sizeof(char*));

	for (int i = 0; i < numOrgs; i++) {

		printf("\nPlease enter the name of organization %d: ", i + 1);

		//allocate memory for one name
		orgNames[i] = malloc(MAX_ORG_NAME_LENGTH * sizeof(char));

		//get organization's name
		fgets(orgNames[i], MAX_ORG_NAME_LENGTH, stdin);

		//get rid of newLine
		if (strchr(orgNames[i], '\n')) {

			//iterate through chars using pointers
			for (char* c = orgNames[i]; *c; c++) {

				//if char is equal to new line character
				if (*c == '\n') {
					*c = '\0';
				}
			}

		}

		//get price and percent for organization
		price = getPriceOrPercent(true);
		percent = getPriceOrPercent(false);

		//add organization to list
		insertNode(listPtr, orgNames[i], price, percent);

	}

	//free memory for org names array
	free(orgNames);
	

}//getOrgs

//returns a pointer to the organization that user chose
Organization* getOrgToSell(const Organization* listPtr) {

	Organization* userChosenOrg = NULL; //stores pointer to user chosen organization
	bool orgFound = false; //flag to see if organization has been found
	bool userConfirmed = false; //flag to see if user confirmed choice
	char userChoice = ' '; //stores user choice for y or n

	//check to see if list is empty
	if (listPtr != NULL) {

		while (!orgFound && !userConfirmed) {
			//prompt user to select organization from list
			char userChosenName[MAX_ORG_NAME_LENGTH] = { ' ' };
			printf("%s", "Please enter the name of the organization you would like to buy from: ");
			fgets(userChosenName, MAX_ORG_NAME_LENGTH, stdin);

			//get rid of newLine
			if (strchr(userChosenName, '\n')) {

				//iterate through chars using pointers
				for (char* c = userChosenName; *c; c++) {

					//if char is equal to new line character
					if (*c == '\n') {
						*c = '\0';
					}
				}

			}

			//check to see if name is in list
			Organization* currentPtr = listPtr;

			//while current pointer isnt null and name doesnt match
			while (currentPtr != NULL && strcmp(currentPtr->orgName, userChosenName) != 0) {
				currentPtr = currentPtr->nextPtr;
			}

			//if org found
			if (currentPtr != NULL && strcmp(currentPtr->orgName, userChosenName) == 0) {
				
				//see if user confirms choice
				printf("You selected %s. Is this correct?\n", currentPtr->orgName);
				userChoice = getUserDecision();

				if (userChoice == 'y') {
					orgFound = true;
					userChosenOrg = currentPtr;
				}

			}
			else {
				puts("\nOrganization not found. (Note: Entry is case sensitive)\n");
			}

		}

	}
	else {
		puts("List is empty.");
	}

	//if org found, print sale information for that organization
	if (orgFound) {
		printf("\nYou selected %s:\nT-shirt Price: %.2f\nPercent Being Donated: %.0f%c\n\n",
			userChosenOrg->orgName, userChosenOrg->tshirtPrice, userChosenOrg->percentToDonate, '%');
	}

	return userChosenOrg;

}//getOrgToSell

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
		if (validScanf(userEntry)) {
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
	char userSelection[10];
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

		fgets(userSelection, 10, stdin);

		//clear the buffer
		if (strchr(userSelection, '\n') != NULL) {
			for (size_t i = 0; i < MAX_CREDIT_CARD_SIZE; i++) {
				if (userSelection[i] == '\n') { userSelection[i] = '\0'; }
			}
		}
		else {
			clrBuff();
		}

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

	printf("%s set to %s\n\n", type, printSizeOrColor(userSelection));

	return userSelection;


}//end getSizeOrColor

//getPayment() function gets the user payment 
double getPayment(double cost, int percent) {

	char creditCardNum[MAX_CREDIT_CARD_SIZE + 1]; //stores user's credit card num
	double payment = 0; //stores user payment
	bool validCardNum = false; //flag to see if cardNum is valid

	puts("\n-----------Payment-----------");

	//get credit card number
	do {

		//prompt for credit card number
		printf("\n%s", "Please enter your credit card number: ");
		fgets(creditCardNum, MAX_CREDIT_CARD_SIZE + 1, stdin);

		//if creditCardNum has a newline character, remove it, else clear the buffer
		if (strchr(creditCardNum, '\n') != NULL) {
			for (size_t i = 0; i < MAX_CREDIT_CARD_SIZE; i++) {
				if (creditCardNum[i] == '\n') { creditCardNum[i] = '\0'; }
			}
		}
		else {
			clrBuff();
		}


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
void printReceipt(const Organization chosenOrg, const Sale currentSale) {

	int receiptNum = 0;
	FILE* fp;
	fp = fopen(RECEIPTS_FILE_PATH, "a");

	//generate receipt number between 1000 and 9999 (4 digits)
	srand(time(0));
	receiptNum = 1000 + (rand() % 9000);


	//print receipt
	fputs("-----------------------------------------------------------------\n", fp);
	fprintf(fp, "Receipt for order #%d\n", receiptNum);
	fputs("-----------------------------------------------------------------\n", fp);
	
	//print organization
	fprintf(fp, "Organization: %s\n", chosenOrg.orgName);

	//print size
	fprintf(fp, "%s", "Size: ");
	fprintf(fp, "%s\n", printSizeOrColor(currentSale.size));

	//print color
	fprintf(fp, "%s", "Color: ");
	fprintf(fp, "%s\n", printSizeOrColor(currentSale.color));

	//print cost
	fprintf(fp, "Cost: $%.2f\n", chosenOrg.tshirtPrice);

	//print percentage to fundraiser
	fprintf(fp, "Percent donated: %.0f%c\n", chosenOrg.percentToDonate, '%');

	//print total amount donated 
	fprintf(fp, "Current amount raised: $%.2f\n", chosenOrg.totalDonated);

	fputs("\nThank you for donation! Have a great day!\n", fp);
	fputs("-----------------------------------------------------------------\n", fp);

	fclose(fp);

	printf("\nReceipt [#%d] is located here: %s\n", receiptNum, RECEIPTS_FILE_PATH);

}//end printReceipt

//calcDonations returns the donated amount based on user payment and percent to donate
double calcDonation(double percent, double payment) {

	double donation = 0; //stores the amount of user's payment that will be donated

	//calculate donation
	donation = payment * (percent / 100);

	return donation;

}//end calcDonation

//printEndOfDay() prints the end of day details
void printEndOfDay(const Organization* listPtr) {

	//open file for printing
	FILE* fp;
	fp = fopen(END_OF_DAY_FILE_PATH, "w");
	fputs("-----------------------------------------------------------------\n", fp);
	fputs("End of day summary: ", fp);
	fputs("\n-----------------------------------------------------------------\n", fp);

	//print total sales and amount raised for each organization in list
	Organization* currentPtr = listPtr; //used to walk through list
	
	while (currentPtr != NULL) {

		//print data
		fprintf(fp, "\nOrganization: %s\n", currentPtr->orgName);
		fprintf(fp, "Total sales: $%.2f\n", currentPtr->totalSales);
		fprintf(fp, "Total donations for organization: $%.2f", currentPtr->totalDonated);

		//go to next node
		currentPtr = currentPtr->nextPtr;
	}

	//close file
	fclose(fp);

	printf("\nEnd of day summary located here: %s\n", END_OF_DAY_FILE_PATH);

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
char* printSizeOrColor(char userChoice) {

	char* str = { ' ' };

	switch (userChoice) {

		//sizes
	case 's': {
		str = "Small";
		break;
	}
	case 'm': {
		str = "Medium";
		break;
	}
	case 'l': {
		str = "Large";
		break;
	}
	case 'x': {
		str = "Extra Large";
		break;
	}
	case ADMIN_SIZE: {
		str = "Admin Code";
		break;
	}

				   //colors
	case 'k': {
		str = "Black";
		break;
	}
	case 'w': {
		str = "White";
		break;
	}
	case 'r': {
		str = "Red";
		break;
	}
	case 'o': {
		str = "Orange";
		break;
	}
	case 'b': {
		str = "Blue";
		break;
	}
	case 'p': {
		str = "Purple";
		break;
	}

	}

	return str;

}//printSizeOrColor()

//print sale details prints the details of the t-shirt sale
void printSale(const Organization* listPtr, bool startSequence) {

	//check to see if list is empty
	if (listPtr != NULL) {

		Organization* currentPtr = listPtr;

		if (startSequence) {

			puts("\n-----------------------------------------------------------------");
			puts("T-shirt sale program setup complete with the following setup:");
			puts("-----------------------------------------------------------------\n");

		}

		else {
			puts("\n-----------------------------------------------------------------");
			puts("Welcome to CS2060 T-Shirt Fundraiser! Here are the details for today's sale:");
			puts("-----------------------------------------------------------------\n");
		}

		//iterate through linked list printing values
		while (currentPtr != NULL) {

			//display data and go to next node
			printf("Organization: %s\nPrice: $%.2f\nPercent to donate: %.0f%c\n\n",
				currentPtr->orgName, currentPtr->tshirtPrice, currentPtr->percentToDonate, '%');

			currentPtr = currentPtr->nextPtr;

		}

	}//end if !null
	else { 
		puts("No organizations have been set up to sell. ");
	}

}//end printSale()

//gets a valid char out of passed in array
char getValidChar(const char validChars[]) {

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

			printf("\nYou selected: %s\n", printSizeOrColor(userChoice));
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
		if (num >= min && num <= max) { validInput = true; }

	}

	return validInput;

}//end isValidPriceOrPercent

//sees if a credit card number is valid
bool validateCreditCardNum(const char cardNum[]) {

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

/*
* Linked List Manipulation Functions
* 
* Algorithms for node operations from HarrisCalebA07.c and by extension, 
* adapted from professor Harding's "ch12SignleLLAddDelete.c".
*/
//inserts an organization to the linked list alphabetically
void insertNode(Organization** headPtr, char* name, double price, double percent) {

	//allocate memory for node in the heap and setup node
	Organization* orgPtr = malloc(sizeof(Organization));

	//check to make sure pointer to memory location was successful
	if (orgPtr != NULL) {

		//put data in node
		orgPtr->orgName = name;
		orgPtr->tshirtPrice = price;
		orgPtr->percentToDonate = percent;

		//initialize total donated and total sales
		orgPtr->totalDonated = 0;
		orgPtr->totalSales = 0;

		//figure out where new node belongs in list
		Organization* previousPtr = NULL;
		Organization* currentPtr = *headPtr;

		//put in list alphabetically
		while (currentPtr != NULL && currentPtr->orgName[0] <= name[0]) {
			//go to next node
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}

		//if NULL, insert as first node
		if (previousPtr == NULL) {
			*headPtr = orgPtr;
		}
		else {
			previousPtr->nextPtr = orgPtr;
		}

		orgPtr->nextPtr = currentPtr;

	}
	//null pointer from memory allocation
	else {
		printf("No memory to create node. ");
	}

}//insertNode