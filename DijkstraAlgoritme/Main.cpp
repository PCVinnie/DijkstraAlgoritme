#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "FirstAlgoritme.h"
#include "SecondAlgoritme.h"
#include "ThirdAlgoritme.h"
#include "FileHandler.h"

#include <string>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

void priorityQueueExample() {

	priority_queue<pair<int, int>> pq;

	// make_pair(vertex 1, gewicht van verbinding) 
	// make_pair(vertex 2, gewicht van verbinding)

	pq.push(make_pair(3, 3));
	pq.push(make_pair(6, 3));

	pq.push(make_pair(4, 5));
	pq.push(make_pair(2, 5));

	pq.push(make_pair(5, 6));
	pq.push(make_pair(7, 6));

	pq.push(make_pair(10, 1));
	pq.push(make_pair(11, 1));

	pq.push(make_pair(12, 4));
	pq.push(make_pair(8, 4));

	pq.push(make_pair(9, 2));
	pq.push(make_pair(1, 2));

	FirstAlgoritme().getShortestPathPriorityQueue(pq, 0);

}

void graphExample() {

	// Graph
	int graph[9][9] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
						{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
						{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
						{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
						{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
						{ 0, 0, 4, 0, 10, 0, 2, 0, 0 },
						{ 0, 0, 0, 14, 0, 2, 0, 1, 6 },
						{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
						{ 0, 0, 2, 0, 0, 0, 6, 7, 0 }
					  };

	// Zet de tweedimensionale array om naar pointer to pointer.
	int** graph_ptr = new int*[9];
	for (int i = 0; i < 9; ++i) {
		graph_ptr[i] = new int[9];
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			graph_ptr[i][j] = graph[i][j];
		}
	}

	FirstAlgoritme().getShortestPathGraph(graph_ptr, 0);

}
 
void secondExample() {

	/*
	a -> a (Looping)
	d -> a (Parallel)
	*/

	int graph[5][5] = { { 0, 5, 10, 0 },
					    { 5, 0, 4, 11 },
						{ 10, 4, 0, 5 },
						{ 0, 11, 5, 0 },
					  };

	ThirdAlgoritme().dijkstra(graph);

}

int main() {

	while (true) {

		int menuNr;
		string filename;
		int vertices = 0;

		cout << "Datastructuren C++ - Vincent Stout" << endl;
		cout << "---------------------------------" << endl;
		cout << " Type a value between 1 and 5: " << endl;
		cout << " 1: Dijkstra priority queue" << endl;
		cout << " 2: Dijkstra graph (25.3)  " << endl;
		cout << " 2: Dijkstra example 2         " << endl;
		cout << " 3: Load graph from file IO (25.8)" << endl;
		cout << " 4: Load graph from file IO (25.12)" << endl;
		cout << " 5: Exit program				" << endl;
		cout << "---------------------------------" << endl;
		cin >> menuNr;

		switch (menuNr) {
		case 1:
			priorityQueueExample();
			break;
		case 2:
			graphExample();
			break;
		case 3:
			secondExample();
			break;
		case 4:
			FirstAlgoritme().getShortestPathGraph(FileHandler().openTxtFile("graph.txt"), 0);
			break;
		case 5:
			std::cout << "Enter a file name (example: graph.txt): " << std::endl; 
			cin.ignore();
			getline(std::cin, filename);
			
			std::cout << "Enter two vertices (example: 0 1): " << std::endl;
			std::cin >> vertices;
			
			SecondAlgoritme().getShortestPath(FileHandler().openTxtFile(filename), 0, vertices);
			break;
		case 6:
			exit(0);
			break;
		}

	}

}