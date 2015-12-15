#ifndef DijkstraAlgoritme_H
#define DijkstraAlgoritme_H

#include <queue>
#include <vector>

#define VRTCS 9

class DijkstraAlgoritme {

public:
	//Constructor
	DijkstraAlgoritme();

	//Member constructor
	DijkstraAlgoritme(int);

	//Destructor
	~DijkstraAlgoritme();

public:
	//Fields
	const int LOOP = 9;

	//Methods
	int** removeLoopings(int**);
	int** removeParallel(int**);
	int minimumDistance(int[], bool[]);
	void getShortestPathPriorityQueue(std::vector<std::pair<int, int>> list[VRTCS], int);
	void getShortestPathGraph(int**, int, int);
	void getAlternativeShortestPathGraph(int**, int);
	void printPriorityQueueInput(std::vector<std::pair<int, int>> list[VRTCS]);
	void printGraphInput(int**);
	void printOutput(int[], int[]);
	bool contains(std::vector<int> &T, int);	
	void printOutputBetweenVertices(int[], int, int);

};

#endif