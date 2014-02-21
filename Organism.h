#ifndef ORGANISM_H
#define ORGANISM_H

#include <string>

class Organism {
	public:
		std::string state;
		int fitnessNumber;

		Organism();
		std::string generateState();
		void fitnessTest();
		void mutate();		
		std::string intToString(int i);
		Organism* operator=(Organism* src);
};

#endif
