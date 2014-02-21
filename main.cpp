#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <ctime>

#include "Organism.h"
#include "Population.h"

using namespace std;

// Define maximum population size.
const int maxPopulation = 20;

// Define maximum generation size.
const int maxGeneration = 20;

// A chess board is 8x8.
const int boardSize = 8;

int main(int argc, char* argv[]) {
	// Ensure our rand() is a bit more random than normal.
	srand( time(0));

	Population *population = new Population( maxPopulation, maxGeneration );
	population->printPop();
	cout << endl;
	population->evolve();
	population->printPop();

	return 0;
}
