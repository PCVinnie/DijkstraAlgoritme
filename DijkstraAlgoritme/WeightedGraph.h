#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

#include "Graph.h"
#include "WeightedEdge.h"
#include "ShortestPathTree.h"
#include <queue> // for priority_queue

template <class T> struct greater : binary_function <T, T, bool> {
	bool operator() (const T& x, const T& y) const { return x>y; }
};

template <typename T>
class WeightedGraph : public Graph<T>
{
public:
	/** Construct an empty graph */
	WeightedGraph();

	/** Construct a graph from vertices and edges objects */
	WeightedGraph(vector<T> vertices, vector<WeightedEdge> &edges);

	/** Construct a graph with vertices 0, 1, ..., n-1 and
	*  edges in a vector */
	WeightedGraph(int numberOfVertices, vector<WeightedEdge> &edges);

	/** Print all edges in the weighted tree */
	void WeightedGraph<T>::printWeightedEdges();

	/** Find single-source shortest paths */
	ShortestPathTree getShortestPath(int sourceVertex);

private:
	/** Priority adjacency lists on edge weights */
	vector<priority_queue<WeightedEdge, vector<WeightedEdge>, greater<WeightedEdge> > > queues;

	/** Create adjacency lists as in an unweighted graph */
	void createAdjacencyLists(int numberOfVertices, vector<WeightedEdge> &edges);

	/** Create a vector of priority queues */
	void createQueues(int numberOfVertices, vector<WeightedEdge> &edges);

	/** Return true if v is in vector T */
	bool contains(vector<int> &T, int v);
};

//const int INFINITY = 2147483647;

template <typename T>
WeightedGraph<T>::WeightedGraph()
{
}

template <typename T>
WeightedGraph<T>::WeightedGraph(vector<T> vertices, vector<WeightedEdge> &edges)
{
	// vertices is defined as protected in the Graph class
	this->vertices = vertices;

	// Create the adjacency list neighbors for the Graph class
	createAdjacencyLists(vertices.size(), edges);

	// Create the adjacency priority queues for weighted graph
	createQueues(vertices.size(), edges);
}

template <typename T>
WeightedGraph<T>::WeightedGraph(int numberOfVertices, vector<WeightedEdge> &edges)
{
	// vertices is defined as protected in the Graph class
	for (int i = 0; i < numberOfVertices; i++)
		vertices.push_back(i); // vertices is {0, 1, 2, ..., n-1}

							   // Create the adjacency list neighbors for the Graph class
	createAdjacencyLists(numberOfVertices, edges);

	// Create the adjacency priority queues for weighted graph
	createQueues(numberOfVertices, edges);
}

template <typename T>
void WeightedGraph<T>::createAdjacencyLists(int numberOfVertices, vector<WeightedEdge> &edges)
{
	// neighbors is defined as protected in the Graph class
	for (int i = 0; i < numberOfVertices; i++)
	{
		neighbors.push_back(vector<int>(0));
	}

	for (int i = 0; i < edges.size(); i++)
	{
		int u = edges[i].u;
		int v = edges[i].v;
		neighbors[u].push_back(v);
	}
}

template <typename T>
void WeightedGraph<T>::createQueues(int numberOfVertices, vector<WeightedEdge> &edges)
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		queues.push_back(priority_queue<WeightedEdge,
			vector<WeightedEdge>, greater<WeightedEdge> >());
	}

	for (int i = 0; i < edges.size(); i++)
	{
		int u = edges[i].u;
		int v = edges[i].v;
		int weight = edges[i].weight;
		queues[u].push(WeightedEdge(u, v, weight));
	}
}

template <typename T>
void WeightedGraph<T>::printWeightedEdges()
{
	for (int i = 0; i < queues.size(); i++)
	{
		// Display all edges adjacent to vertex with index i
		cout << "Vertex " << i << ": ";

		// Get a copy of queues[i], so to keep original queue intact
		priority_queue<WeightedEdge, vector<WeightedEdge>,
			greater<WeightedEdge> > pQueue = queues[i];
		while (!pQueue.empty())
		{
			WeightedEdge edge = pQueue.top();
			pQueue.pop();
			cout << "(" << edge.u << ", " << edge.v << ", "
				<< edge.weight << ") ";
		}
		cout << endl;
	}
}

template <typename T>
bool WeightedGraph<T>::contains(vector<int> &T, int v)
{
	for (int i = 0; i < T.size(); i++)
	{
		if (T[i] == v) return true;
	}

	return false;
}

template <typename T>
ShortestPathTree WeightedGraph<T>::getShortestPath(int sourceVertex)
{
	bool isInt[10];

	// T stores the vertices whose path found so far
	vector<int> T;
	// T initially contains the sourceVertex;
	T.push_back(sourceVertex);

	// vertices is defined in the Graph class
	int numberOfVertices = vertices.size();

	// parent[v] stores the previous vertex of v in the path
	vector<int> parent(numberOfVertices);
	parent[sourceVertex] = -1; // The parent of source is set to -1

							   // costs[v] stores the cost of the path from v to the source
	vector<int> costs(numberOfVertices);
	for (int i = 0; i < costs.size(); i++)
	{
		costs[i] = INT_MAX; // Initial cost set to infinity
	}

	costs[sourceVertex] = 0; // Cost of source is 0

							 // Clone the queue, so as to keep the original queue intact
	vector<priority_queue<WeightedEdge, vector<WeightedEdge>,
		greater<WeightedEdge> > > queues = this->queues;



	// Expand verticesFound
	while (T.size() < numberOfVertices)
	{
		int v = -1; // Vertex to be determined
		int smallestCost = INT_MAX; // Set to infinity
		for (int i = 0; i < T.size(); i++)
		{
			int u = T[i];
			while (!queues[u].empty() && contains(T, queues[u].top().v))
				queues[u].pop(); // Remove the vertex in verticesFound

			if (queues[u].empty())
				continue; // Consider the next vertex in T

			WeightedEdge e = queues[u].top();
			if (costs[u] + e.weight < smallestCost)
			{
				v = e.v;
				smallestCost = costs[u] + e.weight;
				// If v is added to the tree, u will be its parent
				parent[v] = u;
			}
		} // End of for

		T.push_back(v); // Add a new vertex to the set
		costs[v] = smallestCost;
	} // End of while

	

	  // Create a ShortestPathTree
	return ShortestPathTree(sourceVertex, parent, T, costs);
}

/*

template<typename V>
ShortestPathTree WeightedGraph<V>::getShortestPath(int sourceVertex) {

	// T stores the vertices whose path found so far
	vector<int> T;

	// 
	bool isInt[9];

	// parent[v] stores the previous vertex of v in the path
	vector<int> parent(getSize());

	parent[sourceVertex] = -1; // The parent of source is set to -1

							   // cost[v] stores the cost of the path from v to the source
	vector<double> cost(getSize());

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
		isInt[u] = true; // Voegt true aan isInt[u]

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

*/

#endif

