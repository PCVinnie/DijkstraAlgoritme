// DijkstraAlgoritme.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "limits.h"

/*

// De hoeveelheid paden in een diagram
#define V 9

int minDistance(int dist[], bool sptSet[]) {

	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++) {
		if (sptSet[v] == false && dist[v] <= min) {
			min = dist[v], min_index = v;
		}
	}
	return min_index;
}

void getShortestPath(int graph[V][V], int src) {

	int distance[V]; // Geeft een output van de kortste pad.
	bool sptSet[V];

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

}

int main()
{

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

	getShortestPath(graph, 0);
	
	return 0;
}

*/

