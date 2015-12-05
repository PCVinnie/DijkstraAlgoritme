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

	// T stores the vertices whose path found so far
	vector<int> T;

	// 
	//const int s = getSize();
	//bool isInt[s];

	// parent[v] stores the previous vertex of v in the path
	vector<int> parent(getSize());

	parent[sourceVertex] = -1; // The parent of source is set to -1

							   // cost[v] stores the cost of the path from v to the source
	vector<int> cost(getSize());

	for (unsigned i = 0; i < cost.size(); i++) {
		cost[i] = INT_MAX; // Initial cost set to infinity
	}

	cost[sourceVertex] = 0; // Cost of source is 0

							// Expand T
	while (T.size() < getSize()) {

		// Find smallest cost v in V - T 
		int u = -1; // Vertex to be determined

		double currentMinCost = INT_MAX;

		for (int i = 0; i < getSize(); i++) {

			if (find(T.begin(), T.end(), i) == T.end() && cost[i] < currentMinCost) {

				currentMinCost = cost[i];
				u = i;

			}
		}

		if (u == -1) break;

		T.push_back(u); // Add a new vertex to T
		//isInt[u] = true; // Voegt true aan isInt[u]

		// Adjust cost[v] for v that is adjacent to u and v in V - T
		for (Edge* e : neighbors[u]) {

			if (find(T.begin(), T.end(), e->v) == T.end() && cost[e->v] > cost[u] + static_cast<WeightedEdge*>(e)->weight) {
				cost[e->v] = cost[u] + static_cast<WeightedEdge*>(e)->weight;
				parent[e->v] = u;
			}

		}

	} // End of while

	  // Create a ShortestPathTree
	return ShortestPathTree(sourceVertex, parent, T, cost);

}

#endif

