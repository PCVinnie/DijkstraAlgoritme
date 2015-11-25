#include "stdafx.h"
#include "limits.h"
#include <vector>
#include <queue>
#include <iostream>
#include "FirstAlgoritme.h"

FirstAlgoritme::FirstAlgoritme() { }

FirstAlgoritme::~FirstAlgoritme() { }

int FirstAlgoritme::minDistance(int distance[], bool sptSet[]) {

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

void FirstAlgoritme::printPriorityQueueInput(std::priority_queue<std::pair<int, int>> pq) {

	std::cout << "Input:" << std::endl;
	while (!pq.empty()) {
		std::cout << pq.top().first << " " << pq.top().second << std::endl;
		pq.pop();
	}
	std::cout << "" << std::endl;

}

void FirstAlgoritme::printGraphInput(int** graph) {

	std::cout << "Input:" << std::endl;
	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			std::cout << graph[row][column];
		}
		std::cout << "" << std::endl;
	}
	std::cout << "" << std::endl;

}

void FirstAlgoritme::printOutput(int distance[]) {

	std::cout << "Output:" << std::endl;
	for (int i = 0; i < V; i++) {
		std::cout << "Node: " << i << " min weight: " << distance[i] << std::endl;
	}
	std::cout << "" << std::endl;

}

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

void FirstAlgoritme::getShortestPathPriorityQueue(std::vector<pp> G[V + 1], int src) {

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

void FirstAlgoritme::getShortestPathGraph(int** graph, int src) {

	int distance[V]; // Geeft een output van de kortste pad.
	bool sptSet[V];

	printGraphInput(graph);

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