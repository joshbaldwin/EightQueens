#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>

#include "Population.h"
#include "Organism.h"

using namespace std;

// The population of organisms.  
Population::Population(int maxPop, int maxGen) {
	this->maxPopulation = maxPop;
	this->maxGeneration = maxGen;
	*organisms = new Organism[maxPop];
	for(int i=0; i<maxPop; i++) {
		organisms[i] = new Organism();
	}
}

Population::~Population() {
	delete organisms;
}

// Currently a bubble sort.  Good enough for our small population.
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

// Print each state and the fitness number.
void Population::printPop() {
	for(int i=0; i<maxPopulation; i++) {
		cout << "state=" << organisms[i]->state << " fitnessNumber=" 
			<< organisms[i]->fitnessNumber << endl;
	}
}

// Main loop to evolve the population.
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

	// Clean up.
	delete[] frontGenes;
	delete[] backGenes;
}

