#include <stdio.h>
#include <stdlib.h>


/*
* Write a program that calculates and prints the product of the odd integers from 1 to 15
*/
int main(void) {

	int sum = 0;
	int expectedSum = 1 + 3 + 5 + 7 + 9 + 11 + 13 + 15;

	// adds odd values
	for (int i = 0; i < 16; i++) {

		if (i % 2 == 1) {
			sum += i;
		}

	}//end for

	//prints sum
	printf("The sum of the odd numbers is: %d and should be: %d\n", sum, expectedSum);

}//end main