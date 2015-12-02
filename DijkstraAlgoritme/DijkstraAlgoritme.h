#ifndef DijkstraAlgoritme_H
#define DijkstraAlgoritme_H

#include <queue>
#include <vector>

#define VRTCS 9

class DijkstraAlgoritme {

public:
	//Constructor
	DijkstraAlgoritme();

	//Destructor
	~DijkstraAlgoritme();

	//Methods
	int** removeLoopings(int**);
	int** removeParallel(int**);
	int minimumDistance(int[], bool[]);
	void getShortestPathPriorityQueue(std::vector<std::pair<int, int>> G[VRTCS + 1], int);
	void getShortestPathGraph(int**, int, int, int);
	void getAlternativeShortestPathGraph(int**, int);
	void printPriorityQueueInput(std::priority_queue<std::pair<int, int>>);
	void printGraphInput(int**);
	void printOutput(int[], int[]);
	bool contains(std::vector<int> &T, int v);	
	//std::vector<std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, 
	//	greater<WeightedEdge> > > createQueues(int**);

};

#endif