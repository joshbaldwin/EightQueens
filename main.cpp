#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
using namespace std;

// Define maximum population size.
const int maxPopulation = 1;

// Define maximum generation size.
const int maxGeneration = 15;

// A chess board is 8x8.
const int boardSize = 8;

class Organism {
	public:
		string state;
		int fitnessNumber;

		Organism();
		string generateState();
		void fitnessTest();
		void mutate();		
		string intToString(int i);
};

Organism::Organism() {
	state = generateState();
	fitnessNumber = 0;
}

string Organism::intToString(int i) {
	switch (i) {
		case 1:
			return "1";
		case 2:
			return "2";
		case 3:
			return "3";
		case 4:
			return "4";
		case 5:
			return "5";
		case 6:
			return "6";
		case 7:
			return "7";
		case 8:
			return "8";
	}
}

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
		cout << "i=" << i << " state=" << state << " current=" << currentQueenState << endl;
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
		
			//if((fabs( nextQueenPostion - currentQueenPosition )) == diagonalIndex) {
			//	fitnessNumber -= 1;
			//}

			if((nextQueenPosition - currentQueenPosition) == diagonalIndex) {
				fitnessNumber -= 1;
			} else if((currentQueenPosition - nextQueenPosition) == diagonalIndex) {
				fitnessNumber -= 1;
			}
			//cout << "nextQ=" << nextQueenState << " dia=" << diagonalIndex << " fit=" << fitnessNumber << endl;
		}
	} 
}

void Organism::mutate() {
	// Mutate one random gene in the organism (one random queen in the state string).
	string genePosition = intToString( rand() % 8 );
	
}

class Population {
	public:
		int maxPopulation;
		int maxGeneration;
		Organism* organisms[];

		Population(int maxPop, int maxGen);
		~Population();
};

Population::Population(int maxPop, int maxGen) {
	this->maxPopulation = maxPop;
	this->maxGeneration = maxGen;
	*organisms = new Organism[maxPop];
	for(int i=0; i<maxPop; i++) {
		organisms[i] = new Organism();
		organisms[i]->fitnessTest();
		//cout << "i=" << i << " fit=" << organisms[i]->fitnessNumber << endl;
	}
}

Population::~Population() {
	delete organisms;
}

int main(int argc, char* argv[]) {

	Population *population = new Population( maxPopulation, maxGeneration );
	
	return 0;
}
