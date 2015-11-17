#ifndef DijkstraAlgoritme_H
#define DijkstraAlgoritme_H

#define V 9

class FirstAlgoritme {

public:
	//Constructor
	FirstAlgoritme();

	//Destructor
	~FirstAlgoritme();

	//Methods
	int minDistance(int[], bool[]);
	void getShortestPath(int**, int);
	//void getShortestPath(int[V][V], int);
	//void printInput(int[V][V]);
	void printInput(int**);
	void printOutput(int[]);

};

#endif