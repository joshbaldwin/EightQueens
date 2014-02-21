#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>

#include "Organism.h"

using namespace std;


/** Constructor.  Initializes a state and the corresponding fitness number. 
* Each state of the board is a string of digits.  Each digit is the row the queen
* is in.  So "18514376" becomes:
*
*   12345678
* 1 Q--Q----
* 2 --------
* 3 -----Q--
* 4 ----Q---
* 5 --Q-----
* 6 -------Q
* 7 ------Q-
* 8 -Q------
*
*/
Organism::Organism() {
	state = generateState();
	fitnessTest();
}

// Copy constructor.
Organism* Organism::operator=(Organism* src) {
	Organism* desc = new Organism();
	desc->fitnessNumber = src->fitnessNumber;
	desc->state = src->state;
	return desc;
}

// Ugly, but quick utility function.
string Organism::intToString(int i) {
	switch (i) {
		case 1:	return "1";
		case 2:	return "2";
		case 3:	return "3";
		case 4:	return "4";
		case 5:	return "5";
		case 6:	return "6";
		case 7:	return "7";
		case 8:	return "8";
	}
}


// Creates a random state.
string Organism:: generateState() {
	string state = "";
	int number;
	for(int i=0; i<8; i++) {
		// 1<=number<=8;
		number = rand() % 8 +1;
		state.append( intToString(number) );
	}
	return state;
}

/**
* The fitness test is the total number of attacks a queen can make minus a perfect
* score where no queen can attack any other queen which is a score of 28.  Note: 
* we do not count double dipping.  For example: if q1 can attack q2, that counts 
* as one attack.  We do not include the fact that q2 can attack q1.
*/
void Organism::fitnessTest() {
	fitnessNumber = 28;
	string currentQueenState;
	string nextQueenState;
	int index;
	int currentQueenPosition, nextQueenPosition;
	int diagonalIndex;

	for(int i=0; i<8; i++) {
		diagonalIndex = 0;
		currentQueenState = state.substr(i,1);

		for(index=i+1; index<8; index++) {
			diagonalIndex = index - i;
			nextQueenState = state.substr(index, 1);

			// Count side attacks.
			if(currentQueenState == nextQueenState) {
				fitnessNumber -= 1;
			}

			// Count diagonal attacks.
			currentQueenPosition = atoi(currentQueenState.c_str());
			nextQueenPosition = atoi(nextQueenState.c_str());

			if((nextQueenPosition - currentQueenPosition) == diagonalIndex) {
				fitnessNumber -= 1;
			} else if((currentQueenPosition - nextQueenPosition) == diagonalIndex) {
				fitnessNumber -= 1;
			}
		}
	} 
}

/**
* Randomly mutate one random gene in each organism.  That is, move
* one queen in each state to another random row.  For example: s3="12347432".  
* After mutating we have s3="15347432"  The "2" in position 2 is now a "5".
*/
void Organism::mutate() {
	int genePosition = rand() % 8;
	string newGene = intToString( rand() % 8 + 1);
	
	if(genePosition == 0) {
		state = newGene + state.substr(genePosition + 1);
	} else if (genePosition == 7 ) {
		state = state.substr(0, genePosition) + newGene;
	} else {
		state = state.substr(0, genePosition) + newGene + state.substr(genePosition + 1);
	}
}
