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

	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			if (vertices[row][column] > 0 && row == column) {
				vertices[row][column] = 0;
			}
		}
	}

	return vertices;
}

// Haalt de parallelle verbindingen weg door het te vervangen met de hoogste waarden.
int** DijkstraAlgoritme::removeParallel(int** vertices) {

	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
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

int DijkstraAlgoritme::minDistance(int distance[], bool sptSet[]) {

	int min = INT_MAX;
	int min_index = 0;

	// Controlleert op de kleinste waarde in distance[] en geeft daarvan een indexnummer terug.
	for (int v = 0; v < V; v++) {
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
	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			std::cout << graph[row][column] << " ";
		}
		std::cout << "" << std::endl;
	}
	std::cout << "" << std::endl;

}

void DijkstraAlgoritme::printOutput(int distance[]) {

	std::cout << "Output:" << std::endl;
	for (int i = 0; i < V; i++) {
		if (distance[i] != INT_MAX) 
			std::cout << "Node: " << i << " min weight: " << distance[i] << std::endl;
		else 
			std::cout << "Node: " << i << " min weight: -" << std::endl;
	}
	std::cout << "" << std::endl;

}

/*
*	Het beschreven algoritme van Dijkstra's algoritme met priority queue uitwerken
*/

#define pp std::pair<int,int>
typedef std::pair<int, int> ii;

class Prioritize
{
public:
	int operator() (const std::pair<int, int>& p1, const std::pair<int, int>& p2)
	{
		return p1.second < p2.second;
	}
};

void DijkstraAlgoritme::getShortestPathPriorityQueue(std::vector<pp> G[V + 1], int src) {

	std::priority_queue<pp, std::vector<pp>, Prioritize> pq;
	int u, v, w;
	int distance[V + 1];
	
	// Initialiseerd alle afstanden als oneindig.
	for (int i = 0; i < V; i++) {
		distance[i] = INT_MAX;
	}

	// De afstand van de begin vertex is altijd 0.
	distance[src] = 0;
	pq.push(pp(src, distance[src]));
	
	while (!pq.empty()) {

		u = pq.top().first;
		pq.pop();

		for (int i = 0; i < G[u].size(); i++) {

			v = G[u][i].first;
			w = G[u][i].second;

			std::cout << u << " " << v << " " << w << std::endl;

			if (distance[v] > distance[u] + w) {

				pq.push(pp(v, distance[v] = distance[u] + w));

			}

		}
	}

	printOutput(distance);

}

/*
*	Opdracht: 25.3 alternatieve implementatie met adjecency matrix
*/

void DijkstraAlgoritme::getShortestPathGraph(int** g, int src, int start, int end) {

	int distance[V]; // Geeft een output van de kortste pad.
	bool sptSet[V];

	printGraphInput(g);

	int** graph = removeParallel(removeLoopings(g));

	// Initialiseerd alle afstanden als oneindig en zet stpSet[] op false.
	for (int i = 0; i < V; i++) {
		distance[i] = INT_MAX;
		sptSet[i] = false;
	}

	// De afstand van de begin vertex is altijd 0.
	distance[src] = 0;

	// Vindt de kortste pad van alle vertices.
	for (int count = 0; count < V - 1; count++) {
		
		// Geeft de minimum afstand van een set vertices.
		int u = minDistance(distance, sptSet);

		// Als de indexnummer van minDistance is bepaald, wordt de indexwaarde true in sptSet[].
		sptSet[u] = true;

		for (int v = 0; v < V; v++) {

			// Controlleert of sptSet[v] waardes niet true zijn.
			if (sptSet[v] == false) {

				// Controlleert in graph[][] en distance[] geen maximale waarden wordt toegelaten.
				if (graph[u][v] && distance[u] != INT_MAX) {

					// Telt de distance en graph met elkaar op en kijkt of het kleiner is dan de huidige waardes van distance.
					if (distance[u] + graph[u][v] < distance[v]) {

						distance[v] = distance[u] + graph[u][v];
					
					}

				}

			}
		
		}
	}

	printOutput(distance);

}