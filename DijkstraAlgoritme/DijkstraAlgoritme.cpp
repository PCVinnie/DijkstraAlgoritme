#include "stdafx.h"
#include "limits.h"
#include <iostream>
#include "DijkstraAlgoritme.h"

DijkstraAlgoritme::DijkstraAlgoritme() { }

DijkstraAlgoritme::~DijkstraAlgoritme() { }


int DijkstraAlgoritme::minDistance(int dist[], bool sptSet[]) {

	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++) {
		if (sptSet[v] == false && dist[v] <= min) {
			min = dist[v], min_index = v;
		}
	}
	return min_index;
}

void DijkstraAlgoritme::printInput(int graph[V][V]) {

	std::cout << "Invoer:" << std::endl;
	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			std::cout << graph[row][column];
		}
		std::cout << "" << std::endl;
	}
	std::cout << "" << std::endl;

}

void DijkstraAlgoritme::printOutput(int distance[]) {

	std::cout << "Output:" << std::endl;
	for (int i = 0; i < V; i++) {
		std::cout << distance[i] << std::endl;
	}
	std::cout << "" << std::endl;

}

void DijkstraAlgoritme::getShortestPath(int graph[V][V], int src) {

	int distance[V]; // Geeft een output van de kortste pad.
	bool sptSet[V];

	printInput(graph);

	// Initialiseerd alle afstanden als oneindig en zet stpSet[] op false.
	for (int i = 0; i < V; i++) {
		distance[i] = INT_MAX;
		sptSet[i] = false;
	}

	distance[src] = 0;

	for (int count = 0; count < V - 1; count++) {
		int u = minDistance(distance, sptSet);
		sptSet[u] = true;
		for (int v = 0; v < V; v++) {
			if (!sptSet[v] && graph[u][v] && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v])
				distance[v] = distance[u] + graph[u][v];
		
		}
	}

	printOutput(distance);

}
