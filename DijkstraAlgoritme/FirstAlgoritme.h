#ifndef DijkstraAlgoritme_H
#define DijkstraAlgoritme_H

#include <queue>

#define V 9

class FirstAlgoritme {

public:
	//Constructor
	FirstAlgoritme();

	//Destructor
	~FirstAlgoritme();

	//Methods
	int minDistance(int[], bool[]);
	void getShortestPathPriorityQueue(std::priority_queue<std::pair<int, int>>, int);
	void getShortestPathGraph(int**, int);
	void printPriorityQueueInput(std::priority_queue<std::pair<int, int>> pq);
	void printGraphInput(int**);
	void printOutput(int[]);

};

#endif