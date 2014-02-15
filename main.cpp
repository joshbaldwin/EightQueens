#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <ctime>
using namespace std;

// Define maximum population size.
const int maxPopulation = 20;

// Define maximum generation size.
const int maxGeneration = 20;

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
		Organism* operator=(Organism* src);
};

Organism::Organism() {
	state = generateState();
	fitnessNumber = 0;
}

Organism* Organism::operator=(Organism* src) {
	Organism* desc = new Organism();
	desc->fitnessNumber = src->fitnessNumber;
	desc->state = src->state;
	return desc;
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
		//cout << "i=" << i << " state=" << state << " current=" << currentQueenState << endl;
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


class Population {
	public:
		int maxPopulation;
		int maxGeneration;
		Organism* organisms[];

		Population(int maxPop, int maxGen);
		~Population();
		void evolve();
		void printPop();
	private:
		void sort();
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

void Population::sort() {
	bool flag = true;
	Organism* tempOrganism;
	int j;
	while(flag) {
		flag = false;  // Assume no swap happened.
		for(j=0; j<maxPopulation-1; j++) {
			if(organisms[j]->fitnessNumber < organisms[j+1]->fitnessNumber ) {
				tempOrganism = organisms[j]; // the swap element.
				organisms[j] = organisms[j+1];
				organisms[j+1] = tempOrganism;
				flag = true; // a swap occurred, so we continue.
			}
		}
	}
}

void Population::printPop() {
	for(int i=0; i<maxPopulation; i++) {
		cout << "state=" << organisms[i]->state << " fitnessNumber=" 
			<< organisms[i]->fitnessNumber << endl;
	}
}

void Population::evolve() {
	// Select the top half.
	int selectionNumber = ceil(maxPopulation / 2.0 );

	// These will store the front and back half of the genome.
	string* frontGenes = new string[selectionNumber];
	string* backGenes = new string[selectionNumber]; 

	int front, back;

	for(int i=0; i<maxGeneration; i++) {
		// Filter the best organisms to the top of the array.
		sort();

		// Here we split each genome in half to have the front and back genes.
		for(int j=0; j<selectionNumber; j++) {
			frontGenes[j] = (organisms[j]->state).substr(0,4);
			backGenes[j] = (organisms[j]->state).substr(4,8);
		}

		// Mate by randomly swapping around the front and back genes.
		for(int j=0; j<maxPopulation; j++) {
			front = rand() % selectionNumber;
			back = rand() % selectionNumber;
			while(front == back) {
				back = rand() % selectionNumber;
			}
			organisms[j]->state = frontGenes[front] + backGenes[back];
		}

		// Mutate.
		for(int j=0; j<maxPopulation; j++) {
			organisms[j]->mutate();
		}


		for(int j=0; j<maxPopulation; j++) {
			organisms[j]->fitnessTest();
			if(organisms[j]->fitnessNumber == 28 ) {
				// We have a winner.  Kick out of the main loop.
				// Assumes maxGeneration < 1000000;
				cout << "*****" << organisms[j]->state << "*******" << endl;
				i = j = 1000000;
				break;
			}
		}
	}

	delete[] frontGenes;
	delete[] backGenes;
}

int main(int argc, char* argv[]) {
	// Ensure our rand() is a bit more random than normal.
	srand( time(0));

	Population *population = new Population( maxPopulation, maxGeneration );
	population->printPop();
	cout << endl;
	//population->printPop();
	population->evolve();
population->printPop();

	return 0;
}
