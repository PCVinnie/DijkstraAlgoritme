#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "FirstAlgoritme.h"
#include "SecondAlgoritme.h"
#include "FileHandler.h"

using namespace std;

void firstExample() {

	// Dijkstra 1
	/*
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
					  */
	//FirstAlgoritme().getShortestPath(graph, 0);

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

	SecondAlgoritme().dijkstra(graph);

}

int main() {

	while (true) {

		int menuNr;
		cout << "Datastructuren C++ - Vincent Stout" << endl;
		cout << "-------------------------------" << endl;
		cout << " Type a value between 1 and 3: " << endl;
		cout << " 1: Dijkstra example 1         " << endl;
		cout << " 2: Dijkstra example 2         " << endl;
		cout << " 3: Load graph from file IO    " << endl;
		cout << " 4: Exit program				" << endl;
		cout << "-------------------------------" << endl;
		cin >> menuNr;

		switch (menuNr) {
		case 1:
			firstExample();
			break;
		case 2:
			secondExample();
			break;
		case 3:
			FirstAlgoritme().getShortestPath(FileHandler().openTxtFile(), 0);
			break;
		case 4:
			exit(0);
			break;
		}

	}

}