#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "DijkstraAlgoritme.h"
#include "SecondAlgoritme.h"

#define V 9

using namespace std;

void firstExample() {

	// Dijkstra 1
	int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
						{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
						{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
						{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
						{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
						{ 0, 0, 4, 0, 10, 0, 2, 0, 0 },
						{ 0, 0, 0, 14, 0, 2, 0, 1, 6 },
						{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
						{ 0, 0, 2, 0, 0, 0, 6, 7, 0 }
					  };

	DijkstraAlgoritme().getShortestPath(graph, 0);

}

void secondExample() {

	/*
	a -> a (Looping)
	d -> a (Parallel)
	*/

	int vertices[V][V] = { { 5, 1, 0, 1, 0 },
						   { 0, 0, 0, 1, 0 },
						   { 1, 0, 0, 0, 0 },
						   { 1, 0, 0, 0, 1 },
						   { 0, 0, 0, 0, 0 },
						 };

	SecondAlgoritme(vertices).dijkstra();

}

int main() {

	while (true) {

		int menuNr;
		cout << "Datastructuren C++ - Vincent Stout" << endl;
		cout << "-------------------------------" << endl;
		cout << " Type a value between 1 and 3: " << endl;
		cout << " 1: Dijkstra example 1         " << endl;
		cout << " 2: Dijkstra example 2         " << endl;
		cout << " 3: Exit program				" << endl;
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
			exit(0);
			break;
		}

	}

}