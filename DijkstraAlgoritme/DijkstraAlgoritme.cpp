#include "stdafx.h"
#include "limits.h"
//#include <vector>
//#include <queue>
#include <iostream>
#include <string>
#include "DijkstraAlgoritme.h"
#include "WeightedEdge.h"

DijkstraAlgoritme::DijkstraAlgoritme() { }

DijkstraAlgoritme::~DijkstraAlgoritme() { }

template <class T> struct greater : std::binary_function <T, T, bool> {
	bool operator() (const T& x, const T& y) const { return x>y; }
};

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

void DijkstraAlgoritme::printPriorityQueueInput(std::vector<std::pair<int, int>> list[VRTCS]) {

	std::cout << "Input:" << std::endl;

	for (int l = 0; l < VRTCS; l++) {

		for (int i = 0; i < list[l].size(); i++) {

			int v = list[l][i].first;
			int w = list[l][i].second;

			std::cout << v << " " << w << std::endl;

		}

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
			std::cout << "Vertices: " << i << " min weight: " << cost[i] << std::endl;
		} else {
			std::cout << "Vertices: " << i << " min weight: -" << std::endl;
		}
	}
	std::cout << "" << std::endl;

	for (int i = 0; i < VRTCS; i++) {
		std::cout << "Parent: " << parent[i] << std::endl;
	}
	std::cout << "" << std::endl;

}

#define pp std::pair<int, int>

void DijkstraAlgoritme::printOutputBetweenVertices(int cost[], int start, int end) {

	std::priority_queue<std::pair<int, int>>queues;

	for (int i = 0; i < VRTCS; i++) {
		queues.push(pp(cost[i], i));
	}

	std::cout << "A path from: " << start << " to " << end << ": ";

	std::string tmp1 = "";
	std::string tmp2 = "";

	while (!queues.empty()) {

		if (queues.top().second == 0) {
			tmp1 = std::to_string(queues.top().second);
		}
		else {
			tmp2 += std::to_string(queues.top().second);
		}
		queues.pop();
	}

	for (int i = 0; i < tmp1.size(); i++)
		std::cout << tmp1[i] << " ";

	for (int i = 0; i < tmp2.size(); i++)
		std::cout << tmp2[i] << " ";

	std::cout << "" << std::endl;

}

/*
*	Het beschreven algoritme van Dijkstra's algoritme met priority queue uitwerken
*/

class Prioritize {

public:
	int operator() (const std::pair<int, int>& p1, const std::pair<int, int>& p2)
	{
		return p1.second < p2.second;
	}

};

void DijkstraAlgoritme::getShortestPathPriorityQueue(std::vector<std::pair<int, int>> list[VRTCS], int s) {
	
	printPriorityQueueInput(list);

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Prioritize> queues;

	int cost[VRTCS];
	int parent[VRTCS];
	
	int u, v, w;

	for (int i = 0; i < VRTCS; i++) {
		cost[i] = INT_MAX;
	}

	cost[s] = 0;
	parent[s] = -1;

	queues.push(std::pair<int, int>(s, cost[s]));
	
	while (!queues.empty()) {

		u = queues.top().first;
		queues.pop();

		for (int i = 0; i < list[u].size(); i++) {

			v = list[u][i].first;
			w = list[u][i].second;

			if (cost[v] > cost[u] + w) {

				queues.push(std::pair<int, int>(v, cost[v] = cost[u] + w));
				parent[v] = u;

			}

		}
	}

	printOutput(cost, parent);

}

/*
*	Opdracht: 25.3 alternatieve implementatie met adjecency matrix
*/

void DijkstraAlgoritme::getShortestPathGraph(int** graph, int start, int end) {

	printGraphInput(graph);

	int cost[VRTCS]; // Geeft een output van de kortste pad.
	int parent[VRTCS];
	bool spt[VRTCS];
	int size = 0;

	int** w = removeParallel(removeLoopings(graph));

	// Initialiseerd alle afstanden als oneindig en zet stpSet[] op false.
	for (int i = 0; i < VRTCS; i++) {
		cost[i] = INT_MAX;
		spt[i] = false;
	}

	// De afstand van de begin vertex is altijd 0.
	cost[start] = 0;
	parent[start] = -1;

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
					// Relaxing an Edge
					if (cost[v] > cost[u] + w[u][v]) {

						cost[v] = cost[u] + w[u][v];
						parent[v] = u;

					}

					if (v == end) break;

				}

			}

		}
	}

	printOutput(cost, parent);

	printOutputBetweenVertices(cost, start, end);

}

/*
*	Opdracht: 25.10 alternatieve uitwerking van Dijkstra's algoritme
*/

std::vector<std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, greater<WeightedEdge> > > createQueues(int** graph) {

	std::vector<std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, greater<WeightedEdge> > > queues;

	for (int i = 0; i < VRTCS; i++) {
		queues.push_back(std::priority_queue<WeightedEdge, std::vector<WeightedEdge>, greater<WeightedEdge> >());
	}

	for (int row = 0; row < VRTCS; row++) {
		for (int column = 0; column < VRTCS; column++) {
			if (graph[row][column] != 0)
				queues[row].push(WeightedEdge(row, column, graph[row][column]));
		}
	}

	return queues;

}

bool DijkstraAlgoritme::contains(std::vector<int> &T, int v)
{
	for (int i = 0; i < T.size(); i++)
	{
		if (T[i] == v) return true;
	}

	return false;
}

void DijkstraAlgoritme::getAlternativeShortestPathGraph(int** graph, int s) {

	printGraphInput(graph);

	int** w = removeParallel(removeLoopings(graph));

	std::vector<std::priority_queue<WeightedEdge, std::vector<WeightedEdge>,
		greater<WeightedEdge> > > queues = createQueues(removeParallel(removeLoopings(w)));

	std::vector<int> T;
	int parent[VRTCS];
	int costs[VRTCS];

	for (int i = 0; i < VRTCS; i++) {
		costs[i] = INT_MAX; 
	}

	T.push_back(s);
	parent[s] = -1;
	costs[s] = 0; 

	while (T.size() < VRTCS)
	{
		int v = -1;
		int smallestCost = INT_MAX;

		for (int i = 0; i < T.size(); i++)
		{
			int u = T[i];
			while (!queues[u].empty() && contains(T, queues[u].top().v))
				queues[u].pop();

			if (queues[u].empty())
				continue;

			WeightedEdge e = queues[u].top();
			if (costs[u] + e.weight < smallestCost)
			{
				v = e.v;
				smallestCost = costs[u] + e.weight;
				parent[v] = u;
			}
		} 

		T.push_back(v);
		costs[v] = smallestCost;
	} 

	printOutput(costs, parent);

}
