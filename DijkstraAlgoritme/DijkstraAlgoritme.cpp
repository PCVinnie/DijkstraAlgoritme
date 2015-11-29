#include "stdafx.h"
#include "limits.h"
#include <vector>
#include <queue>
#include <iostream>
#include "DijkstraAlgoritme.h"

DijkstraAlgoritme::DijkstraAlgoritme() { }

DijkstraAlgoritme::~DijkstraAlgoritme() { }


// Haalt de loopings weg door het te vervangen met een 0.
int** DijkstraAlgoritme::removeLoopings(int** vertices) {

	for (int row = 0; row < VRTCS; row++) {
		for (int column = 0; column < VRTCS; column++) {
			if (vertices[row][column] > 0 && row == column) {
				vertices[row][column] = 0;
			}
		}
	}

	return vertices;
}

// Haalt de parallelle verbindingen weg door het te vervangen met de hoogste waarden.
int** DijkstraAlgoritme::removeParallel(int** vertices) {

	for (int row = 0; row < VRTCS; row++) {
		for (int column = 0; column < VRTCS; column++) {
			if (vertices[row][column] > 0) {
				if (vertices[row][column] > vertices[column][row]) {
					vertices[column][row] = vertices[row][column];
				}
				else {
					vertices[row][column] = vertices[column][row];
				}
			}
		}
	}

	return vertices;
}

int DijkstraAlgoritme::minimumDistance(int distance[], bool sptSet[]) {

	int min = INT_MAX;
	int min_index = 0;

	// Controlleert op de kleinste waarde in distance[] en geeft daarvan een indexnummer terug.
	for (int v = 0; v < VRTCS; v++) {
		if (sptSet[v] == false && distance[v] <= min) {
			min = distance[v], min_index = v;
		}
	}

	return min_index;
}

void DijkstraAlgoritme::printPriorityQueueInput(std::priority_queue<std::pair<int, int>> pq) {

	std::cout << "Input:" << std::endl;
	while (!pq.empty()) {
		std::cout << pq.top().first << " " << pq.top().second << std::endl;
		pq.pop();
	}
	std::cout << "" << std::endl;

}

void DijkstraAlgoritme::printGraphInput(int** graph) {

	std::cout << "Input:" << std::endl;
	for (int row = 0; row < VRTCS; row++) {
		for (int column = 0; column < VRTCS; column++) {
			std::cout << graph[row][column] << " ";
		}
		std::cout << "" << std::endl;
	}
	std::cout << "" << std::endl;

}

void DijkstraAlgoritme::printOutput(int cost[], int parent[]) {

	std::cout << "Output:" << std::endl;
	for (int i = 0; i < VRTCS; i++) {
		if (cost[i] != INT_MAX) {
			std::cout << "Node: " << i << " min weight: " << cost[i] << std::endl;
		} else {
			std::cout << "Node: " << i << " min weight: -" << std::endl;
		}
	}
	std::cout << "" << std::endl;

	for (int i = 0; i < VRTCS; i++) {
		std::cout << "Parent: " << parent[i] << std::endl;
	}
	std::cout << "" << std::endl;

}

/*
*	Het beschreven algoritme van Dijkstra's algoritme met priority queue uitwerken
*/

#define pp std::pair<int,int>
typedef std::pair<int, int> ii;

class Prioritize{

public:
	int operator() (const std::pair<int, int>& p1, const std::pair<int, int>& p2)
	{
		return p1.second < p2.second;
	}

};

void DijkstraAlgoritme::getShortestPathPriorityQueue(std::vector<pp> G[VRTCS + 1], int s) {

	std::priority_queue<pp, std::vector<pp>, Prioritize> pq;
	int u, v, w;
	int cost[VRTCS + 1];
	int parent[VRTCS];
	
	// Initialiseerd alle afstanden als oneindig.
	for (int i = 0; i < VRTCS; i++) {
		cost[i] = INT_MAX;
	}

	// De afstand van de begin vertex is altijd 0.
	cost[s] = 0;
	parent[s] = -1;

	pq.push(pp(s, cost[s]));
	
	while (!pq.empty()) {

		u = pq.top().first;
		pq.pop();

		for (int i = 0; i < G[u].size(); i++) {

			v = G[u][i].first;
			w = G[u][i].second;

			std::cout << u << " " << v << " " << w << std::endl;

			if (cost[v] > cost[u] + w) {

				pq.push(pp(v, cost[v] = cost[u] + w));
				parent[v] = u;

			}

		}
	}

	std::cout << "" << std::endl;

	printOutput(cost, parent);

}

/*
*	Opdracht: 25.3 alternatieve implementatie met adjecency matrix
*/

void DijkstraAlgoritme::getShortestPathGraph(int** graph, int s, int start, int end) {

	int cost[VRTCS]; // Geeft een output van de kortste pad.
	int parent[VRTCS];
	bool spt[VRTCS];
	int size = 0;

	printGraphInput(graph);

	int** w = removeParallel(removeLoopings(graph));

	// Initialiseerd alle afstanden als oneindig en zet stpSet[] op false.
	for (int i = 0; i < VRTCS; i++) {
		cost[i] = INT_MAX;
		spt[i] = false;
	}

	// De afstand van de begin vertex is altijd 0.
	cost[s] = 0;
	parent[s] = -1;

	if (end > 0) 
		size = end;
	else 
		size = VRTCS;

	// Vindt de kortste pad van alle vertices.
	for (int i = start; i < size; i++) {

		// Geeft de minimum afstand van een set vertices.
		int u = minimumDistance(cost, spt);

		// Als de indexnummer van minDistance is bepaald, wordt de indexwaarde true in sptSet[].
		spt[u] = true;

		for (int v = 0; v < VRTCS; v++) {

			// Controlleert of sptSet[v] waardes false zijn.
			if (spt[v] == false) {

				// Controlleert in graph[][] en distance[] geen maximale waarden wordt toegelaten.
				if (w[u][v] && cost[u] != INT_MAX) {

					// Telt de distance en graph met elkaar op en kijkt of het groter is dan de huidige waardes van distance.
					if (cost[v] > cost[u] + w[u][v]) {

						cost[v] = cost[u] + w[u][v];
						parent[v] = u;

					}

				}

			}

		}
	}

	printOutput(cost, parent);

}

/*
*	Opdracht: 25.10 alternatieve uitwerking van Dijkstra's algoritme
*/

void DijkstraAlgoritme::getAlternativeShortestPathGraph(int** graph, int s) {

	int cost[VRTCS]; // Geeft een output van de kortste pad.
	int parent[VRTCS];
	bool spt[VRTCS];

	printGraphInput(graph);

	int** w = removeParallel(removeLoopings(graph));

	// Initialiseerd alle afstanden als oneindig en zet stpSet[] op false.
	for (int i = 0; i < VRTCS; i++) {
		cost[i] = INT_MAX;
		spt[i] = false;
	}

	// De afstand van de begin vertex is altijd 0.
	cost[s] = 0;
	parent[s] = -1;

	// Vindt de kortste pad van alle vertices.
	for (int i = 0; i < VRTCS - 1; i++) {

		// Geeft de minimum afstand van een set vertices.
		int u = minimumDistance(cost, spt);

		// Als de indexnummer van minDistance is bepaald, wordt de indexwaarde true in sptSet[].
		spt[u] = true;

		for (int v = 0; v < VRTCS; v++) {

			// Controlleert of sptSet[v] waardes false zijn.
			if (spt[v] == false) {

				// Controlleert in graph[][] en distance[] geen maximale waarden wordt toegelaten.
				if (w[u][v] && cost[u] != INT_MAX) {

					// Telt de distance en graph met elkaar op en kijkt of het groter is dan de huidige waardes van distance.
					if (cost[v] > cost[u] + w[u][v]) {

						cost[v] = cost[u] + w[u][v];
						parent[v] = u;

					}

				}

			}

		}
	}

	printOutput(cost, parent);

}
