#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "DijkstraAlgoritme.h"
#include "FileHandler.h"

#include <string>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

void priorityQueueExample() {

	/*
	priority_queue<pair<int, int>> pq;

	// make_pair(gewicht, van vertex) 
	// make_pair(gewicht, naar vertex)
*/

	#define pp std::pair<int,int>
	std::vector<pair<int, int>> G[V + 1];

	G[1].push_back(pp(0, 4));
	G[0].push_back(pp(1, 4));

	G[2].push_back(pp(1, 8));
	G[1].push_back(pp(2, 8));

	G[3].push_back(pp(2, 7));
	G[2].push_back(pp(3, 7));

	G[4].push_back(pp(3, 9));
	G[3].push_back(pp(4, 9));

	G[5].push_back(pp(4, 10));
	G[4].push_back(pp(5, 10));

	DijkstraAlgoritme().getShortestPathPriorityQueue(G, 0);

}

void priorityQueueInput() {

	std::vector<pair<int, int>> G[V + 1];
	int e, u, v, w;

	std::cout << "Geeft de aantal vertices op." << std::endl;
	std::cin >> e;

	for (int i = 0; i < e; i++) {

		std::cout << "Geeft de waarde: van vertex, naar vertex en weight op." << std::endl;
		std::cin >> u >> v >> w;
		G[u].push_back(pp(v, w));
		G[v].push_back(pp(u, w));

	}

	DijkstraAlgoritme().getShortestPathPriorityQueue(G, 0);

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

	DijkstraAlgoritme().getShortestPathGraph(graph_ptr, 0, 0, 0);

}

int main() {

	while (true) {

		int menuNr;
		string filename;
		int start = 0;
		int end = 0;

		cout << "Datastructuren C++ - Vincent Stout" << endl;
		cout << "---------------------------------" << endl;
		cout << " Type a value between 1 and 7: " << endl;
		cout << " 1: Dijkstra priority queue template" << endl;
		cout << " 2: Dijkstra priority queue input" << endl;
		cout << " 3: Dijkstra graph (25.3)" << endl;
		cout << " 4: Dijkstra alternative" << endl;
		cout << " 5: Load graph from file IO (25.8)" << endl;
		cout << " 6: Load graph from file IO (25.12)" << endl;
		cout << " 7: Exit program				" << endl;
		cout << "---------------------------------" << endl;
		cin >> menuNr;

		switch (menuNr) {
		case 1:
			priorityQueueExample();
			break;
		case 2:
			priorityQueueInput();
			break;
		case 3:
			graphExample();
			break;
		case 4:
			// Alternatief
			break;
		case 5:
			DijkstraAlgoritme().getShortestPathGraph(FileHandler().openTxtFile("graph2.txt"), 0, 0, 0);
			break;
		case 6:
			std::cout << "Enter a file name (example: graph.txt): " << std::endl; 
			cin.ignore();
			getline(std::cin, filename);
			
			std::cout << "Enter start vertex (example: 0): " << std::endl;
			std::cin >> start;

			std::cout << "Enter end vertex (example: 1): " << std::endl;
			std::cin >> end;
			
			DijkstraAlgoritme().getShortestPathGraph(FileHandler().openTxtFile(filename), 0, start, end);
			break;
		case 7:
			exit(0);
			break;
		}

	}

}