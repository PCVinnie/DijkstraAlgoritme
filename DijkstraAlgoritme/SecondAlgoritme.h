#ifndef SecondAlgoritme_H
#define SecondAlgoritme_H

#include <list>

#define V 9

class SecondAlgoritme {

public:
	//Constructor
	SecondAlgoritme();

	//Destructor
	~SecondAlgoritme();

	//Methods
	int minDistance(int[], bool[]);
	void getShortestPath(int**, int, int);
	void printInput(int**);
	void printOutput(int[]);
	std::list<int> splitNumber(int);

};

#endif