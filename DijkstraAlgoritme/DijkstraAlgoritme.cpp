#include "stdafx.h"
#include "limits.h"
#include <iostream>
#include <string>
#include "DijkstraAlgoritme.h"

DijkstraAlgoritme::DijkstraAlgoritme() { }

DijkstraAlgoritme::~DijkstraAlgoritme() { }

template <class T> struct greater : std::binary_function <T, T, bool> {
	bool operator() (const T& x, const T& y) const { 
		return x > y; 
	}
};

template <class T> struct smaller : std::binary_function <T, T, bool> {
	bool operator() (const std::pair<T, T>& x, const std::pair<T, T>& y) const {
		return x < y;
	}
};

bool DijkstraAlgoritme::contains(std::vector<int> &T, int v) {

	for (int i = 0; i < T.size(); i++) {
		if (T[i] == v)
			return true;
	}

	return false;

}

class Weighted {

public:
	double weight;
	int u, v;

	Weighted(int u, int v, double weight) {
		this->weight = weight; this->u = u; this->v = v;
	}

	bool operator>(const Weighted& edge) const {
		return (*this).weight > edge.weight;
	}

};

std::vector<std::priority_queue<Weighted, std::vector<Weighted>, greater<Weighted>>> createQueues(int** graph) {

	std::vector<std::priority_queue<Weighted, std::vector<Weighted>, greater<Weighted>>> queues;

	for (int i = 0; i < VRTCS; i++) {
		queues.push_back(std::priority_queue<Weighted, std::vector<Weighted>, greater<Weighted> >());
	}

	for (int row = 0; row < VRTCS; row++) {
		for (int column = 0; column < VRTCS; column++) {
			if (graph[row][column] != 0)
				queues[row].push(Weighted(row, column, graph[row][column]));
		}
	}

	return queues;

}

// Haalt de loopings weg door het te vervangen met een 0.
int** DijkstraAlgoritme::removeLoopings(int** cost) {

	for (int row = 0; row < VRTCS; row++) {
		for (int column = 0; column < VRTCS; column++) {
			if (cost[row][column] > 0 && row == column) {
				cost[row][column] = 0;
			}
		}
	}

	return cost;
}

// Haalt de parallelle verbindingen weg door het te vervangen met de hoogste waarden.
int** DijkstraAlgoritme::removeParallel(int** cost) {

	for (int row = 0; row < VRTCS; row++) {
		for (int column = 0; column < VRTCS; column++) {
			if (cost[row][column] > 0) {
				if (cost[row][column] > cost[column][row]) {
					cost[column][row] = cost[row][column];
				}
				else {
					cost[row][column] = cost[column][row];
				}
			}
		}
	}

	return cost;
}

// Controlleert op de kleinste waarde in distance[] en geeft daarvan een indexnummer terug.
int DijkstraAlgoritme::minimumDistance(int distance[], bool sptSet[]) {

	int min = INT_MAX;
	int min_index = 0;

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
		if (cost[i] != INT_MAX) {
			std::cout << "Parent: " << parent[i] << std::endl;
		} else {
			std::cout << "Parent: -" << std::endl;
		}
	}
	std::cout << "" << std::endl;

}

void DijkstraAlgoritme::printOutputBetweenVertices(int cost[], int start, int end) {

	std::priority_queue<std::pair<int, int>>queues;

	for (int i = 0; i < VRTCS; i++) {
		queues.push(std::pair<int, int>(cost[i], i));
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

void DijkstraAlgoritme::getShortestPathPriorityQueue(std::vector<std::pair<int, int>> list[VRTCS], int s) {
	
	printPriorityQueueInput(list);

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, smaller<int>> queues;

	int cost[VRTCS];
	int parent[VRTCS];
	
	int u, v, w;

	for (int i = 0; i < VRTCS; i++) {
		cost[i] = INT_MAX;
		parent[i] = INT_MAX;
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

	int** g = removeParallel(removeLoopings(graph));

	int cost[VRTCS];
	int parent[VRTCS];
	bool spt[VRTCS];

	for (int i = 0; i < VRTCS; i++) {
		cost[i] = INT_MAX;
		parent[i] = INT_MAX;
		spt[i] = false;
	}

	cost[start] = 0;
	parent[start] = -1;

	for (int i = 0; i < VRTCS - 1; i++) {

		int u = minimumDistance(cost, spt);

		spt[u] = true;

		for (int v = 0; v < VRTCS; v++) {

			if (spt[v] == false) {

				if (g[u][v] && cost[u] != INT_MAX) {

					if (cost[v] > cost[u] + g[u][v]) {

						cost[v] = cost[u] + g[u][v];
						parent[v] = u;

					}

					if (v == end) 
						break;

				}

			}

		}
	}

	if (end == 0) {
		printOutput(cost, parent);
	} else {
		printOutputBetweenVertices(cost, start, end);
	}
}

/*
*	Opdracht: 25.10 alternatieve uitwerking van Dijkstra's algoritme
*/

void DijkstraAlgoritme::getAlternativeShortestPathGraph(int** graph, int s) {

	printGraphInput(graph);

	int** g = removeParallel(removeLoopings(graph));

	std::vector<std::priority_queue<Weighted, std::vector<Weighted>,
		greater<Weighted> > > queues = createQueues(removeParallel(removeLoopings(g)));

	std::vector<int> T;
	int parent[VRTCS];
	int cost[VRTCS];

	for (int i = 0; i < VRTCS; i++) {
		cost[i] = INT_MAX;
		parent[VRTCS] = INT_MAX;
	}

	T.push_back(s);
	parent[s] = -1;
	cost[s] = 0;

	while (T.size() < VRTCS)
	{
		int v = -1;
		int smallestCost = INT_MAX;

		for (int i = 0; i < T.size(); i++)
		{
			int u = T[i];
			while (!queues[u].empty() && contains(T, queues[u].top().v)) {
				queues[u].pop();
			}

			if (queues[u].empty()) {
				continue;
			}

			Weighted e = queues[u].top();

			if (cost[u] + e.weight < smallestCost)
			{
				v = e.v;
				smallestCost = cost[u] + e.weight;
				parent[v] = u;
			}
		} 

		T.push_back(v);
		cost[v] = smallestCost;
	} 

	printOutput(cost, parent);

}