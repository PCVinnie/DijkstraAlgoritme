#include "stdafx.h"
#include "limits.h"
#include <iostream>
#include <string>
#include "DijkstraAlgoritme.h"

DijkstraAlgoritme::DijkstraAlgoritme() { }

DijkstraAlgoritme::DijkstraAlgoritme(int size) {

	int *ptr;
	ptr = (int*)(&LOOP);
	*ptr = size;

}

DijkstraAlgoritme::~DijkstraAlgoritme() { }

template <class T> struct greater : std::binary_function <T, T, bool> {

	bool operator() (const T& x, const T& y) const {
		return x > y;
	}

};

template <class T> struct smaller : std::binary_function <T, T, bool> {

	bool operator() (const T& x, const T& y) const {
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

class Weight {

public:
	int u, v;
	double weight;

	Weight(int u, double weight) {
		this->u = u;
		this->weight = weight;
	}

	Weight(int u, int v, double weight) {
		this->u = u; 
		this->v = v;
		this->weight = weight;
	}

	bool operator>(const Weight& e) const {
		return (*this).weight > e.weight;
	}

	bool operator<(const Weight& e) const {
		return (*this).weight < e.weight;
	}

};

std::vector<std::priority_queue<Weight, std::vector<Weight>, greater<Weight>>> createQueues(int** graph) {

	std::vector<std::priority_queue<Weight, std::vector<Weight>, greater<Weight>>> queues;

	for (int i = 0; i < VRTCS; i++) {
		queues.push_back(std::priority_queue<Weight, std::vector<Weight>, greater<Weight>>());
	}

	for (int row = 0; row < VRTCS; row++) {
		for (int column = 0; column < VRTCS; column++) {
			if (graph[row][column] != 0)
				queues[row].push(Weight(row, column, graph[row][column]));
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

// Controlleert op de kleinste waarde in cost[] en geeft daarvan een indexnummer terug.
int DijkstraAlgoritme::minDistance(int cost[], bool sptSet[]) {

	int min = INT_MAX;
	int min_index = 0;

	for (int v = 0; v < VRTCS; v++) {
		if (sptSet[v] == false && cost[v] <= min) {
			min = cost[v], min_index = v;
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

	for (int i = 0; i < LOOP; i++) {
		queues.push(std::pair<int, int>(cost[i], i));
	}

	std::cout << "A path from " << start << " to " << end << ": ";

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

	for (int i = 0; i < tmp1.size(); i++) {
		std::cout << tmp1[i] << " ";
	}

	for (int i = 0; i < tmp2.size(); i++) {
		std::cout << tmp2[i] << " ";
	}

	std::cout << "" << std::endl;

}

/*
*	Het beschreven algoritme van Dijkstra's algoritme met priority queue uitwerken
*/

void DijkstraAlgoritme::getShortestPathPriorityQueue(std::vector<std::pair<int, int>> list[VRTCS], int s) {

	// Print de graph in terminal.
	printPriorityQueueInput(list);

	// Stap 1: Priority_queue wordt aangemaakt. De priority_queue sorteert op de kleinste waarde.
	std::priority_queue<Weight, std::vector<Weight>, smaller<Weight>> queues;

	// Stap 2: Er worden twee array's aangemaakt. VRTCS staat voor de aantal vertices.
	// cost[VRTCS] voor het toevoegen van de vertices.
	// parent[VRTCS] voor het toevoegen van de uitkomst voor de minimale afstand.
	int cost[VRTCS];
	int parent[VRTCS];

	int u, v, w;
	int count = 0;

	// Stap 3: Op basis van de grootte van de constante VRTCS, wordt aan elk element een INT_MAX toegewezen.
	// INT_MAX is de maximale integer waarden.
	for (int i = 0; i < VRTCS; i++) {
		cost[i] = INT_MAX;
		parent[i] = INT_MAX;
	}

	// Stap 4: 0 en -1 wordt d.m.v. de start waarden s aan cost[s] en parent[s] toegewezen.
	cost[s] = 0;
	parent[s] = -1;

	// Voegt een weight toe aan de priority_queue.
	queues.push(Weight(s, cost[s]));

	/* 
		De opzet van stap 1 t/m 4 ziet er dus als volgt uit.
	
		cost[s]		parent[s]		priority_queue<>
		0			-1				Weight(0, cost[0])		
		INT_MAX		INT_MAX
		INT_MAX		INT_MAX
		INT_MAX		INT_MAX
		INT_MAX		INT_MAX
		INT_MAX		INT_MAX
		INT_MAX		INT_MAX
		INT_MAX		INT_MAX
		INT_MAX		INT_MAX
	*/

	/////////////////////////////////////////////////////////////////

	// Zolang de priority_queue niet leeg is blijft het loepen.
	while (!queues.empty()) {

		count++;
		std::cout << "--------------------------------------------------------------" << std::endl;
		std::cout << "Nr.: " << count << std::endl;
		// Haalt de minimale afstand op uit de priority_queue en wijst dit toe aan u.
		u = queues.top().u;
		std::cout << "Stap 1: De minimale afstand is: " << u << std::endl;

		// Verwijdert het eerste element uit de priority_queue.
		queues.pop();

		for (int i = 0; i < list[u].size(); i++) {

			// Haalt de vertex en weight op uit de list[u][i].
			v = list[u][i].first; // 0
			w = list[u][i].second; // 4

			// Controleert of cost[v] groter is dan cost[u] opgeteld met de weight uit list[u][i].second.
			if (cost[v] > cost[u] + w) {
				std::cout << "Stap 2: Als vertex " << v << " groter is dan " << u + w << "(minimale afstand + weight)" << std::endl;
				// Telt cost[u] en de weight met elkaar op en voegt dit toe aan cost[v].
				queues.push(Weight(v, cost[v] = cost[u] + w));
				std::cout << "Stap 3: Telt de minimale afstand en weight met elkaar op, en voegt dit toe aan cost op index nr.: " << v << std::endl;
				// Voegt de minimale afstand toe aan de parent.
				parent[v] = u;
				std::cout << "Stap 4: Voegt de minimale afstand " << u << " aan de parent op index nr.: " << v << std::endl;
			}

		}

	}

	std::cout << "" << std::endl;

	// Print de uitkomst in terminal.
	printOutput(cost, parent);

}

/*
*	Opdracht: 25.3 alternatieve implementatie met adjecency matrix
*	Opdracht: 25.12
*/

void DijkstraAlgoritme::getShortestPathGraph(int** graph, int start, int end) {

	// Print de graph in terminal.
	printGraphInput(graph);

	// Stap 1: Graph wordt gegeven als een pointer to pointer. Waarbij de loopings en parallelle lijnen worden verwijdert.
	int** g = removeParallel(removeLoopings(graph));

	// Stap 2: Er worden drie array's aangemaakt en een constante wordt er aan toegewezen. VRTCS staat voor de aantal vertices.
	// cost[VRTCS] voor het toevoegen van de vertices.
	// parent[VRTCS] voor het toevoegen van de uitkomst voor de minimale afstand.
	// spt[VRTCS] wordt gebruikt als controle voor het update van de shortest pad.
	int cost[VRTCS];
	int parent[VRTCS];
	bool spt[VRTCS];

	int count = 0;

	// Stap 3: Op basis van de grootte van de constante VRTCS, wordt aan elk element een INT_MAX aan toegewezen.
	// INT_MAX is de maximale integer waarden.
	for (int i = 0; i < VRTCS; i++) {
		cost[i] = INT_MAX;
		parent[i] = INT_MAX;
		spt[i] = false;
	}

	// Stap 4: 0 en -1 wordt d.m.v. de start waarden aan cost en parent toegewezen.
	cost[start] = 0;
	parent[start] = -1;

	/*
		De opzet van stap 1 t/m 4 ziet er dus als volgt uit.

		cost[s]		parent[s]		spt[i]
		0			-1				false
		INT_MAX		INT_MAX			false
		INT_MAX		INT_MAX			false
		INT_MAX		INT_MAX			false
		INT_MAX		INT_MAX			false
		INT_MAX		INT_MAX			false
		INT_MAX		INT_MAX			false
		INT_MAX		INT_MAX			false
		INT_MAX		INT_MAX			false
	*/

	/////////////////////////////////////////////////////////////////

	for (int i = 0; i < LOOP - 1; i++) {

		count++;
		std::cout << "--------------------------------------------------------------" << std::endl;
		std::cout << "Nr.: " << count << std::endl;

		// Stap 5: Berekent de minimale afstand en wijst de indexnummer toe aan u.
		int u = minDistance(cost, spt);
		std::cout << "Stap 1: De minimale afstand is: " << u << std::endl;

		// Markeert de vertex waarmee de minimale afstand is berekend.
		spt[u] = true;

		for (int v = 0; v < LOOP; v++) {

			// Stap 6: Update cost[v] alleen als het niet in sptSet[v] bevindt.
			// spt[v] moet dus false zijn om te kunnen update.
			if (spt[v] == false) {

				// Controleert of de weight in de graph en de cost geen maximale interger waarden hebben.
				if (g[u][v] && cost[u] != INT_MAX) {

					// Controleert of cost[v] groter is dan cost[u] opgeteld met de weight uit de graph.
					if (cost[v] > cost[u] + g[u][v]) {
						std::cout << "Stap 2: Als vertex " << v << " groter is dan " << cost[u] + g[u][v] << "(minimale afstand + weight)" << std::endl;
						// Stap 7: Telt cost[u] en de weight uit de graph met elkaar op en voegt dit toe aan cost[v]
						cost[v] = cost[u] + g[u][v];
						std::cout << "Stap 3: Telt de minimale afstand en weight met elkaar op, en voegt dit toe aan cost op index nr.: " << v << std::endl;
						// Voegt de minimale afstand toe aan de parent
						parent[v] = u;
						std::cout << "Stap 4: Voegt de minimale afstand " << u << " aan de parent op index nr.: " << v << std::endl;
					}

					// Onderbreekt de for loop als de eind vertex is bereikt.
					if (v == end) {
						break;
					}

				}

			}

		}
	}

	std::cout << "" << std::endl;

	// Als de eind waarde gelijk is aan 0 dan wordt enkel de printOutput methode aangeroepen.
	if (end == 0) {
		// Print de uitkomst in terminal.
		printOutput(cost, parent);
	} else {
		// Print de uitkomst in terminal.
		printOutput(cost, parent);
		printOutputBetweenVertices(cost, start, end);
		std::cout << "" << std::endl;
	}
}

/*
*	Opdracht: 25.10 alternatieve uitwerking van Dijkstra's algoritme
*/

void DijkstraAlgoritme::getAlternativeShortestPathGraph(int** graph, int s) {

	// Print de graph in terminal.
	printGraphInput(graph);

	// Stap 1: PriorityQueue wordt aangemaakt. Waarbij de loopings en parallelle lijnen worden verwijdert.
	std::vector<std::priority_queue<Weight, std::vector<Weight>,
		greater<Weight>>> queues = createQueues(removeParallel(removeLoopings(graph)));

	// Stap 2: Er worden twee array's en één vector aangemaakt en een constante wordt er aan toegewezen. VRTCS staat voor de aantal vertices.
	// cost[VRTCS] voor het toevoegen van de vertices.
	// parent[VRTCS] voor het toevoegen van de uitkomst voor de minimale afstand.
	// spt[VRTCS] wordt gebruikt als controle voor het update van de shortest pad.
	std::vector<int> T;
	int parent[VRTCS];
	int cost[VRTCS];

	int count = 0;

	// Stap 3: Op basis van de grootte van de constante VRTCS, wordt aan elk element een INT_MAX aan toegewezen.
	// INT_MAX is de maximale integer waarden.
	for (int i = 0; i < VRTCS; i++) {
		cost[i] = INT_MAX;
		parent[i] = INT_MAX;
	}

	// Stap 4: 0 en -1 wordt d.m.v. de start waarden s aan cost en parent toegewezen. Ook wordt s aan de vector toegevoegd.
	T.push_back(s);
	parent[s] = -1;
	cost[s] = 0;

	/*
		De opzet van stap 1 t/m 4 ziet er dus als volgt uit.

		cost[s]		parent[s]		vector<int> T
		0			-1				0
		INT_MAX		INT_MAX			
		INT_MAX		INT_MAX			
		INT_MAX		INT_MAX			
		INT_MAX		INT_MAX			
		INT_MAX		INT_MAX			
		INT_MAX		INT_MAX			
		INT_MAX		INT_MAX			
		INT_MAX		INT_MAX			
	*/

	/////////////////////////////////////////////////////////////////

	// Zolang T kleiner is dan de constante VRTCS blijft de while lus lopen.
	while (T.size() < VRTCS)
	{
		count++;
		std::cout << "--------------------------------------------------------------" << std::endl;
		std::cout << "Nr.: " << count << std::endl;

		// Initialiseert v met -1 en geeft sc de maximale integer waarde.
		int v = -1;
		int sc = INT_MAX;

		// Stap 5: Itereert over lijst T.
		for (int i = 0; i < T.size(); i++)
		{
			int u = T[i];
			std::cout << "Stap 1: De minimale afstand is: " << u << std::endl;

			// Als de priorityqueue niet leeg is en T bevat de zelfde waarde als het hoogste object in de queue.
			// Dan wordt het hoogste object dat in de priorityqueue staat verwijderd.
			while (!queues[u].empty() && contains(T, queues[u].top().v)) {
				queues[u].pop();
			}

			// Als de priorityqueue leeg is, springt die naar het einde van de for loop.
			if (queues[u].empty()) {
				continue;
			}

			// Het object dat het hoogste in de priorityqueue staat wordt toegwezen aan Weight e.
			Weight e = queues[u].top();

			// Stap 6: Telt cost[u] en de weight met elkaar op en controleert of het kleiner is dan sc.
			if (cost[u] + e.weight < sc) {
				std::cout << "Stap 2: Als vertex " << i << " groter is dan " << cost[u] + e.weight << "(minimale afstand + weight)" << std::endl;
				v = e.v;
				// Telt cost[u] en de weight met elkaar op en voegt dit toe aan sc.
				sc = cost[u] + e.weight;
				std::cout << "Stap 3: Telt de minimale afstand en weight met elkaar op, en voegt dit toe aan sc: " << sc << std::endl;
				// Voegt de minimale afstand toe aan de parent.
				parent[v] = u;
				std::cout << "Stap 4: Voegt de minimale afstand " << u << " aan de parent op index nr.: " << v << std::endl;
			}
		}

		cost[v] = sc;
		T.push_back(v);
	}

	std::cout << "" << std::endl;

	// Print de uitkomst in terminal.
	printOutput(cost, parent);

}