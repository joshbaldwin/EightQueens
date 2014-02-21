#ifndef POPULATION_H
#define POPULATION_H

#include "Organism.h"

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


#endif
