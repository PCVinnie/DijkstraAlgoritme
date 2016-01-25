#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H
#include "Graph.h"
#include "WeightedEdge.h" // Defined in Listing 25.1 
#include "ShortestPathTree.h" // Defined in Listing 25.8 

template<typename V>
class WeightedGraph : public Graph<V>
{

public:
	// Construct an empty graph 
	WeightedGraph();

	// Construct a graph from vertices and edges objects 
	WeightedGraph(vector<V>& vertices, vector<WeightedEdge>& edges);

	// Construct a graph with vertices 0, 1, ..., n-1 and
	// edges in a vector 
	WeightedGraph(int numberOfVertices, vector<WeightedEdge>& edges);

	// Print all edges in the weighted tree 
	void WeightedGraph<V>::printWeightedEdges();

	// Add a weighted edge 
	bool addEdge(int u, int v, double w);

	// Find single-source shortest paths 
	ShortestPathTree getShortestPath(int sourceVertex);

};

template<typename V>
WeightedGraph<V>::WeightedGraph() { }

template<typename V>
WeightedGraph<V>::WeightedGraph(vector<V>& vertices, vector<WeightedEdge>& edges) {

	// Add vertices to the graph
	for (unsigned i = 0; i < vertices.size(); i++) {
		addVertex(vertices[i]);
	}

	// Add edges to the graph
	for (unsigned i = 0; i < edges.size(); i++) {
		addEdge(edges[i].u, edges[i].v, edges[i].weight);
	}

}

template<typename V>
WeightedGraph<V>::WeightedGraph(int numberOfVertices, vector<WeightedEdge>& edges) {

	// Add vertices to the graph
	for (int i = 0; i < numberOfVertices; i++)
		addVertex(i); // vertices is {0, 1, 2, ..., n-1}

	// Add edges to the graph
	for (unsigned i = 0; i < edges.size(); i++) {
		addEdge(edges[i].u, edges[i].v, edges[i].weight);
	}

}

template<typename V>
void WeightedGraph<V>::printWeightedEdges() {

	for (int i = 0; i < getSize(); i++) {

		// Display all edges adjacent to vertex with index i
		cout << "Vertex " << getVertex(i) << "(" << i << "): ";

		// Display all weighted edges
		for (Edge* e : neighbors[i]) {
			cout << "(" << e->u << ", " << e->v << ", " << static_cast<WeightedEdge*>(e)->weight << ") ";
		}
		cout << endl;
	}

}

template<typename V>
bool WeightedGraph<V>::addEdge(int u, int v, double w) {

	return createEdge(new WeightedEdge(u, v, w));

}

template<typename V>
ShortestPathTree WeightedGraph<V>::getShortestPath(int sourceVertex) {

	// Stap 1: Er worden drie vectoren en één array aangemaakt. 
	// vector<int> T slaat de vertices op waarvan het pad is gevonden.
	// bool isInt[] wordt gebruikt als controle voor het update van de minimale afstand.
	// parent[v] wordt de uitkomst van de minimale afstand aan toegevoegd.
	// cost[v] voor het toevoegen van de vertices.
	vector<int> T;
	bool isInt[18];
	vector<int> parent(getSize());
	vector<int> cost(getSize());

	// Stap 2: Op basis van de grootte van cost.size(), wordt aan elk element een INT_MAX toegewezen.
	// INT_MAX is de maximale integer waarden.
	for (unsigned i = 0; i < cost.size(); i++) {
		cost[i] = INT_MAX;
	}

	// Stap 3: 0 en -1 wordt d.m.v. de start waarden sourceVertex aan cost en parent toegewezen.
	cost[sourceVertex] = 0;
	parent[sourceVertex] = -1;

	/*
		De opzet van stap 1 t/m 3 ziet er dus als volgt uit:

		vector<int> T	bool isInt[18]	vector<int> parent	vector<int> cost
										-1					0
															INT_MAX
															INT_MAX
															INT_MAX
															INT_MAX
															INT_MAX
															INT_MAX
															INT_MAX
															INT_MAX
															INT_MAX
															INT_MAX
															INT_MAX
	
	*/

	/////////////////////////////////////////////////////////////////

	// Zolang T kleiner is dan getSize() blijft de while lus lopen.
	while (T.size() < getSize()) {

		// Initialiseert u met -1.
		int u = -1;

		/*
		Stap 1: Berekent de minimale afstand en geeft hiervoor een indexnummer terug.
				Als de minimale afstand is berekent, wordt op basis van het indexnummer in de isInt array een true toegevoegd.
				De isInt array houdt bij of de minimale afstand is berekent van een bepaalde vertex.
		*/
		double currentMinCost = INT_MAX;
		for (int i = 0; i < getSize(); i++) {
			if (isInt[u] == isInt[i] && cost[i] < currentMinCost) {
				currentMinCost = cost[i];
				u = i;
			}
		}

		// Stap 2: Controlleert of u niet -1 is. Zo ja dan wordt de lus onderbroken.
		if (u == -1) break;

		// Stap 3: Er wordt een nieuwe vertex toegevoegd aan T en aan de array isInt wordt een true toegewezen.
		T.push_back(u);
		isInt[u] = true;

		for (Edge* e : neighbors[u]) {

			// Stap 4: Om daad werkelijk te controlleren wat de afstand van de bron tot een vertex is moet een berekening worden uitgevoerd. 
			// Mocht het eerste element van de cost array, opgeteld met het gewicht, kleiner zijn dan de voorgaande waarde of initialisatie waarde.
			// Big-O-notatie: isInt[u] == true
			if (isInt[u] == true && cost[e->v] > cost[u] + static_cast<WeightedEdge*>(e)->weight) {

				// Stap 5: Dan wordt de eerste waarde met de weight opgeteld en toegevoegd aan de cost array.
				cost[e->v] = cost[u] + static_cast<WeightedEdge*>(e)->weight;

				// Stap 6: Ook wordt de minimale afstand aan de parent array toegevoegd.
				parent[e->v] = u;
			}

		}

	} 

	// Stap 7: Creëert de ShortestPathTree
	return ShortestPathTree(sourceVertex, parent, T, cost);

	/*

	Stap 1: Berekent de minimale afstand en geeft hiervoor een indexnummer terug.
			Als de minimale afstand is berekent, wordt op basis van het indexnummer in de isInt array een true toegevoegd.
			De isInt array houdt bij of de minimale afstand is berekent van een bepaalde vertex.
	Stap 2: Controlleert of u niet -1 is. Zo ja dan wordt de lus onderbroken.
	Stap 3: Er wordt een nieuwe vertex toegevoegd aan T en aan de array isInt wordt een true toegewezen (Zie stap 1).
	Stap 4: Om daad werkelijk te controlleren wat de afstand van de bron tot een vertex is moet een berekening worden uitgevoerd.
			Mocht het eerste element van de cost array, opgeteld met het gewicht, kleiner zijn dan de voorgaande waarde of initialisatie waarde.
	Stap 5: Dan wordt de eerste waarde met de weight opgeteld en toegevoegd aan de cost array.
	Stap 6: Ook wordt de kleinste afstand aan de parent array toegevoegd.
	Stap 7: Creëert de ShortestPathTree

	Dus: eerst het initialiseren van de arrays en vectoren. Daarna het berekenen van de minimale afstand en tot slot het berekenen van de bron tot de vertices.

	*/

}

#endif

