/*
* Author: Caleb Harris
* Class: CS2060 - 001
* Assignment: 07
*
* Problem statement:
* This program will ask for pet names and ages, store them in a linked list,
* then sort and display the linked list alphabetically. 
*/

//preprocessor
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

//structures
typedef struct Node {

	//data
	char* name;
	int age;

	//node pointers
	struct Node* nextPtr;

}Node;

//function prototypes
void insertNode(Node** headPtr, int age, char* name);
void deleteNode(Node** headPtr, char* nameToDelete);
void printList(const Node* listPtr);
void printListByAge(const Node* listPtr);
char getUserDecision();
void clrBuff();
bool validScanf(int scanfReturnVal);
void getPets(Node** listPtr);
void delPets(Node** listPtr);

//constants
#define MAX_AGE 100
#define MAX_NAME_LENGTH 10

int main(void) {

	//create a linked list to store pet information
	//pointer to head
	Node* petListHeadPtr = NULL;
	
	//get names and ages of pets from user
	getPets(&petListHeadPtr);

	//print list alphabetically
	printList(petListHeadPtr);

	//print list by age
	printListByAge(petListHeadPtr);

	//delete pets
	delPets(&petListHeadPtr);

	//free memory for petListHeadPtr
	free(petListHeadPtr);

}//end main


//functions

// Inserts a node into the linked list 
//****algorithm adapted from "ch12SignleLLAddDelete.c" provided by Professor Harding****
void insertNode(Node** headPtr, int age, char* name) {

	// Allocate memory for node in the heap and setup node
	Node* nodePtr = malloc(sizeof(Node));

	// check to make pointer to memory location was successful
	if (nodePtr != NULL) {
		//put data in node
		nodePtr->age = age;
		nodePtr->name = name;
		nodePtr->nextPtr = NULL;

		// Figure out where new node belongs in linked list, create 2 pointers to help
		Node* previousPtr = NULL;
		Node* currentPtr = *headPtr;

		//Looking for where to put node in list
		// Loop while haven't reached end of list and 
		// current name first letter > previous
		while (currentPtr != NULL && currentPtr->name[0] <= name[0]){
			//go to next node
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}

		// if NULL, inserting as 1st node!
		if (previousPtr == NULL){
			//inserting as 1st node set headPtr
			*headPtr = nodePtr;
		}
		// currentPtr pointing to node AFTER insertion point
		else{
			//previous ptr needs to point to current node
			previousPtr->nextPtr = nodePtr;
		}

		// Connect new node into list
		nodePtr->nextPtr = currentPtr;

	}
	//null pointer from memory allocation
	else{
		printf("No memory to create node for %s\n", name);
	}

} // insertNode

// Delete a node in the linked list if it exists
//****algorithm adapted from "ch12SignleLLAddDelete.c" provided by Professor Harding ****
void deleteNode(Node** headPtr, char* nameToDelete){

	// Figure out where node to delete is in linked list, 
	//create nodes to keep track of previous and current pointers
	Node* previousPtr = NULL;
	Node* currentPtr = *headPtr;

	// Check if node to delete is 1st node!
	if (currentPtr != NULL && strcmp(currentPtr->name, nameToDelete) == 0){

		//update headPtr to point to second node
		*headPtr = (*headPtr)->nextPtr;

		//free data at current pointer
		free(currentPtr->name);

		// now can delete current node
		free(currentPtr);
		currentPtr = NULL;
	}
	else{

		//Loop through remaining nodes
		// While haven't reached end of list and 
		//current node's name != nameToDelete
		while (currentPtr != NULL && strcmp(currentPtr->name, nameToDelete) != 0) {

			// go to the next node
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;

		}

		// if found node to delete 	
		if (currentPtr != NULL && previousPtr != NULL) {

			// previousPtr is pointing to node BEFORE node to delete 
			// Update to point to next node
			previousPtr->nextPtr = currentPtr->nextPtr;

			//delete data on current node
			free(currentPtr->name);

			//delete current node
			free(currentPtr);
			currentPtr = NULL;

		}

		//NULL, node is not in list!	
		else{
			printf("Pet named %s not in list! (*note: name is case sensitive)\n\n", nameToDelete);
		}

	} // not 1st node

} //deleteNode

// Walk down list printing the value in each node
void printList(const Node* listPtr){

	// Walk list and print values if list is not empty
	if (listPtr != NULL){

		printf("\nPets in list by name:\n");
		puts("--------------------------------------");

		//set currentPtr to first node in list
		Node* currentPtr = listPtr;

		//loop through the list until the last node points to null
		while (currentPtr != NULL){

			// display and go to next node
			printf("Name: %s\nAge: %d\n\n", currentPtr->name, currentPtr->age);
			currentPtr = currentPtr->nextPtr;

		}

	}
	// linked list is empty
	else{
		puts("No pets in list\n");
	}

} // printList

// Walk down list printing the value in each node by age
void printListByAge(const Node* listPtr) {

	// Walk list and print values if list is not empty
	if (listPtr != NULL) {

		printf("\nPets in list by age:\n");
		puts("--------------------------------------");

		//set currentPtr to first node in list
		Node* currentPtr = listPtr;

		//iterate through maximum age
		for (int currentAge = 0; currentAge < MAX_AGE; currentAge++) {

			//iterate through entire list, look for age, print if found
			while (currentPtr != NULL) {

				//if age is equal to value looking for, print it
				if (currentPtr->age == currentAge) {

					printf("Name: %s\nAge: %d\n\n", currentPtr->name, currentPtr->age);

				}

				//go to next node
				currentPtr = currentPtr->nextPtr;

			}

			//reset currentPtr
			currentPtr = listPtr;

		} // for

	}
	// linked list is empty
	else {
		puts("No pets in list\n");
	}

}// printListByAge

//get y or n function returns a yes or no value from user
char getUserDecision() {

	bool validInput = false; //flag used to tell if the input was valid
	char userChoice = ' '; //used to hold the user's decision
	int userEntry = 0; //used to hold scanf return value

	//get user choice for y or n
	do {

		//prompt user
		printf("\n%s", "(Y)es or (N)o? ");
		userEntry = scanf("%c", &userChoice);

		//clear buffer
		clrBuff();

		//make answer lowerCase
		userChoice = tolower(userChoice);

		//if valid scanf return and userchoice is a y or n
		if (validScanf(userEntry) && (userChoice == 'y' || userChoice == 'n')) { validInput = true; }
		else { puts("\nInvalid Entry"); }

	} while (!validInput);

	return userChoice;

}//end getUserDecision()

//get pets input from user
void getPets(Node** listPtr) {

	int scanfRetVal = 0; //stores the scanf return value
	bool validInput = false; //flag used to tell if the input was valid
	int numPets = 0; //holds number pets

	do {

		//ask how many pets will be entered
		printf("%s", "How many pets will be entered? ");
		scanfRetVal = scanf("%d", &numPets);

		//clear buffer
		clrBuff();

		//if valid scanf
		if (validScanf(scanfRetVal) && numPets >= 0) { validInput = true; }
		else { puts("\nInvalid Entry"); }

	} while (!validInput);

	//when we have valid number of pets, get pets and add to list
	int petAge = 0; //holds age of pet

	//create an array to store all pet names so that each address for each name is passed to the node
	// and allocate memory for every string. 
	// memory allocation: number of pets * size of one string
	char** allPetNames = malloc(numPets * sizeof(char*));

	for (int i = 0; i < numPets; i++) {

		printf("\nPlease enter pet %d:\n", i + 1);

		//allocate memory for one name on allPetNames array
		allPetNames[i] = malloc(MAX_NAME_LENGTH * sizeof(char));

		//get pets name
		printf("%s", "Name: ");
		fgets(allPetNames[i], MAX_NAME_LENGTH, stdin);

		//get rid of newLine
		if (strchr(allPetNames[i], '\n')) {
			
			//iterate through chars using pointers
			for (char *c = allPetNames[i]; *c; c++) {
				
				//if char is equal to new line character
				if (*c == '\n') {
					*c = '\0';
				}
			}

		}

		//get pets age
		do {
			printf("%s", "Age: ");
			scanfRetVal = scanf("%d", &petAge);

			//clear buffer
			clrBuff();
		} while (scanfRetVal == 0);
		
		//add pet to linked list
		insertNode(listPtr, petAge, allPetNames[i]);

	}

	//free memory for allPetsNames
	free(allPetNames);

}// getPets

//clears input buffer
void clrBuff() { while ((getchar()) != '\n'); }

//validScanf() function validates user input based on valid value passed in
bool validScanf(int scanfReturnVal) {

	bool valid = false;

	//check to see if integer was entered
	if (scanfReturnVal == 0) { valid = false; }

	else { valid = true; }

	return valid;

}//end getInput

//delete pets asks the user to delete pets if they would like
void delPets(Node** listPtr) {

	bool userFinished = false; //flag to see if user is done deleting pets
	char userChoice = '\0'; //character to store y or n

	//prompt the user to see what pet they would like to delete
	if (*listPtr != NULL) {
		puts("Would you like to remove a pet from the list?");
		userChoice = getUserDecision();

		//see if user wants to delete a pet or not
		if (userChoice == 'n') { userFinished = true; }
	}

	while (!userFinished && (*listPtr) != NULL) {

		printf("%s", "Please enter name of the pet to delete: ");
		char petName[MAX_NAME_LENGTH] = {' '};
		fgets(petName, MAX_NAME_LENGTH, stdin);

		//get rid of newLine
		if (strchr(petName, '\n')) {

			//iterate through chars using pointers
			for (char* c = petName; *c; c++) {

				//if char is equal to new line character
				if (*c == '\n') {
					*c = '\0';
				}
			}

		}

		//delete node for that pet name or notify customer no pet with such name
		deleteNode(listPtr, petName);

		//print remaining pets in list
		puts("---------- Remaining Pets ----------");
		printList(*listPtr);

		//ask user if they would like to delete more
		if ((*listPtr) != NULL) {

			puts("Would you like to delete more pet entries?");
			
			userChoice = getUserDecision();

			//see if they answered yes
			if (userChoice == 'n') {
				userFinished = true;
			}

		}

	}

}//delPets