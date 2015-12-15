#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "DijkstraAlgoritme.h"
#include "FileHandler.h"

#include "ShortestPathTree.h"
#include "WeightedGraph.h"
#include "WeightedEdge.h"

#include <string>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

void priorityQueueExample() {

	priority_queue<pair<int, int>> pq;

	// make_pair(gewicht, van vertex) 
	// make_pair(gewicht, naar vertex)

	#define pp std::pair<int,int>
	std::vector<pair<int, int>> list[VRTCS + 1];

	list[1].push_back(pp(0, 4));
	list[0].push_back(pp(1, 4));

	list[2].push_back(pp(1, 8));
	list[1].push_back(pp(2, 8));

	list[3].push_back(pp(2, 7));
	list[2].push_back(pp(3, 7));

	list[4].push_back(pp(3, 9));
	list[3].push_back(pp(4, 9));

	list[5].push_back(pp(4, 10));
	list[4].push_back(pp(5, 10));

	list[6].push_back(pp(5, 3));
	list[5].push_back(pp(6, 3));

	list[7].push_back(pp(6, 2));
	list[6].push_back(pp(7, 2));

	list[8].push_back(pp(7, 11));
	list[7].push_back(pp(8, 11));

	DijkstraAlgoritme().getShortestPathPriorityQueue(list, 0);

}

void priorityQueueInput() {

	std::vector<pair<int, int>> list[VRTCS + 1];
	int e, u, v, w;

	std::cout << "Give the number of vertices." << std::endl;
	std::cin >> e;

	for (int i = 0; i < e; i++) {

		std::cout << "Give the value from a vertex, to vertex and weight." << std::endl;
		std::cin >> u >> v >> w;
		list[u].push_back(pp(v, w));
		list[v].push_back(pp(u, w));

	}

	DijkstraAlgoritme().getShortestPathPriorityQueue(list, 0);

}

int** graphExample() {

	// Graph
	int graph[9][9] = { { 0, 6, 0, 0, 0, 0, 0, 3, 0 },
						{ 6, 0, 8, 0, 0, 0, 0, 11, 0 },
						{ 0, 8, 0, 5, 0, 4, 0, 0, 2 },
						{ 0, 0, 5, 0, 9, 14, 0, 0, 0 },
						{ 0, 0, 0, 9, 0, 13, 0, 0, 0 },
						{ 0, 0, 4, 0, 13, 0, 2, 0, 0 },
						{ 0, 0, 0, 14, 0, 2, 0, 1, 6 },
						{ 3, 11, 0, 0, 0, 0, 1, 0, 7 },
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

	return graph_ptr;

}

/*
*	Opdracht: 25.11  alleen het gedeelte uitwerking m.b.t. getShortestPath
*/

template<typename T>
void printAllPaths(ShortestPathTree& tree, vector<T> vertices) {

	cout << "All shortest paths from " << vertices[tree.getRoot()] << " are:" << endl;

	for (unsigned i = 0; i < vertices.size(); i++) {
		cout << "To " << vertices[i] << ": ";

		// Print a path from i to the source
		vector<int> path = tree.getPath(i);

		for (int j = path.size() - 1; j >= 0; j--) {
			cout << vertices[path[j]] << " ";
		}
		cout << "(cost: " << tree.getCost(i) << ")" << endl;

	}
}

void weightedGraph() {

	// Vertices for graph in Figure 25.1
	std::string vertices[] = { "Seattle", "San Francisco", "Los Angeles",
		"Denver", "Kansas City", "Chicago", "Boston", "New York",
		"Atlanta", "Miami", "Dallas", "Houston" };

	// Edge array for graph in Figure 25.1
	int edges[][3] = {
		{ 0, 1, 807 },{ 0, 3, 1331 },{ 0, 5, 2097 },
		{ 1, 0, 807 },{ 1, 2, 381 },{ 1, 3, 1267 },
		{ 2, 1, 381 },{ 2, 3, 1015 },{ 2, 4, 1663 },{ 2, 10, 1435 },
		{ 3, 0, 1331 },{ 3, 1, 1267 },{ 3, 2, 1015 },{ 3, 4, 599 },
		{ 3, 5, 1003 },
		{ 4, 2, 1663 },{ 4, 3, 599 },{ 4, 5, 533 },{ 4, 7, 1260 },
		{ 4, 8, 864 },{ 4, 10, 496 },
		{ 5, 0, 2097 },{ 5, 3, 1003 },{ 5, 4, 533 },
		{ 5, 6, 983 },{ 5, 7, 787 },
		{ 6, 5, 983 },{ 6, 7, 214 },
		{ 7, 4, 1260 },{ 7, 5, 787 },{ 7, 6, 214 },{ 7, 8, 888 },
		{ 8, 4, 864 },{ 8, 7, 888 },{ 8, 9, 661 },
		{ 8, 10, 781 },{ 8, 11, 810 },
		{ 9, 8, 661 },{ 9, 11, 1187 },
		{ 10, 2, 1435 },{ 10, 4, 496 },{ 10, 8, 781 },{ 10, 11, 239 },
		{ 11, 8, 810 },{ 11, 9, 1187 },{ 11, 10, 239 }

	};

	// 23 undirected edges in Figure 25.1
	const int NUMBER_OF_EDGES = 46;

	// Create a vector for vertices
	vector<string> vectorOfVertices(12);
	copy(vertices, vertices + 12, vectorOfVertices.begin());

	// Create a vector for edges
	vector<WeightedEdge> edgeVector;

	for (int i = 0; i < NUMBER_OF_EDGES; i++)
		edgeVector.push_back(WeightedEdge(edges[i][0], edges[i][1], edges[i][2]));

	WeightedGraph<string> graph1(vectorOfVertices, edgeVector);
	ShortestPathTree tree = graph1.getShortestPath(5);
	printAllPaths<string>(tree, graph1.getVertices());

}

int main() {

	while (true) {

		int menuNr;
		string filename;
		int start = 0;
		int end = 0;
		FileHandler fileHandler = FileHandler();

		cout << "Datastructuren C++ - Vincent Stout" << endl;
		cout << "---------------------------------" << endl;
		cout << " Type a value between 1 and 8: " << endl;
		cout << " 1: Dijkstra priority queue" << endl;
		cout << " 2: Dijkstra priority queue input" << endl;
		cout << " 3: Dijkstra graph (25.3)" << endl;
		cout << " 4: Dijkstra alternative" << endl;
		cout << " 5: Load graph from file IO (25.8)" << endl;
		cout << " 6: Load graph from file IO (25.12) input" << endl;
		cout << " 7: WeightedGraph" << endl;
		cout << " 8: Exit program" << endl;
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
			DijkstraAlgoritme().getShortestPathGraph(graphExample(), 0, 0);
			break;
		case 4:
			DijkstraAlgoritme().getAlternativeShortestPathGraph(graphExample(), 0);
			break;
		case 5:
			DijkstraAlgoritme(fileHandler.getSize()).getShortestPathGraph(fileHandler.openTxtFile("graph2.txt"), 0, 0);
			break;
		case 6:
			std::cout << "Enter a file name (example: graph.txt): " << std::endl; 
			cin.ignore();
			getline(std::cin, filename);
			
			std::cout << "Enter start vertex (example: 0): " << std::endl;
			std::cin >> start;

			std::cout << "Enter end vertex (example: 1): " << std::endl;
			std::cin >> end;

			DijkstraAlgoritme(fileHandler.getSize()).getShortestPathGraph(fileHandler.openTxtFile(filename), start, end);
			break;
		case 7:
			weightedGraph();
			break;
		case 8:
			exit(0);
			break;
		}

	}

}