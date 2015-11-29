#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Tree.h"
#include <vector>
#include <queue>

using namespace std;

template <typename T>
class Graph
{
public:
	/** Construct an empty graph */
	Graph();

	/** Construct a graph from vertices in a vector and
	* edges in 2-D array */
	Graph(vector<T> vertices, int edges[][2], int numberOfEdges);

	/** Construct a graph with vertices 0, 1, ..., n-1 and
	* edges in 2-D array */
	Graph(int numberOfVertices, int edges[][2], int numberOfEdges);

	/** Construct a graph from vertices and edges objects */
	Graph(vector<T> vertices, vector<Edge> edges);

	/** Construct a graph with vertices 0, 1, ..., n-1 and
	*  edges in a vector */
	Graph(int numberOfVertices, vector<Edge> edges);

	/** Return the number of vertices in the graph */
	int getSize() const;

	/** Return the degree for a specified vertex */
	int getDegree(int v) const;

	/** Return the vertex for the specified index */
	T getVertex(int index) const;

	/** Return the index for the specified vertex */
	int getIndex(T v) const;

	/** Return the vertices in the graph */
	vector<T> getVertices() const;

	/** Return the neighbors of vertex v */
	vector<int> getNeighbors(int v) const;

	/** Print the edges */
	void printEdges() const;

	/** Print the adjacency matrix */
	void printAdjacencyMatrix() const;

	/** Obtain a depth-first search tree */
	/** To be discussed in Section 24.7 */
	Tree dfs(int v) const;

	/** Starting bfs search from vertex v */
	/** To be discussed in Section 24.7 */
	Tree bfs(int v) const;

protected:
	vector<T> vertices; // Store vertices
	vector< vector<int> > neighbors; // Adjacency lists

private:
	/** Create adjacency lists for each vertex from an edge array */
	void createAdjacencyLists(int numberOfVertices, int edges[][2],
		int numberOfEdges);

	/** Create adjacency lists for each vertex from an Edge vector */
	void createAdjacencyLists(int numberOfVertices,
		vector<Edge> &edges);

	/** Recursive function for DFS search */
	void dfs(int v, vector<int> &parent,
		vector<int> &searchOrders, vector<bool> &isVisited) const;
};

template <typename T>
Graph<T>::Graph()
{
}

template <typename T>
Graph<T>::Graph(vector<T> vertices, int edges[][2],
	int numberOfEdges)
{
	this->vertices = vertices;
	createAdjacencyLists(vertices.size(), edges, numberOfEdges);
}

template <typename T>
Graph<T>::Graph(int numberOfVertices, int edges[][2],
	int numberOfEdges)
{
	for (int i = 0; i < numberOfVertices; i++)
		vertices.push_back(i); // vertices is {0, 1, 2, ..., n-1}

	createAdjacencyLists(numberOfVertices, edges, numberOfEdges);
}

template <typename T>
Graph<T>::Graph(vector<T> vertices, vector<Edge> edges)
{
	this->vertices = vertices;
	createAdjacencyLists(vertices.size(), edges);
}

template <typename T>
Graph<T>::Graph(int numberOfVertices, vector<Edge> edges)
{
	for (int i = 0; i < numberOfVertices; i++)
		vertices.push_back(i); // vertices is {0, 1, 2, ..., n-1}

	createAdjacencyLists(numberOfVertices, edges);
}

template <typename T>
void Graph<T>::createAdjacencyLists(int numberOfVertices,
	int edges[][2], int numberOfEdges)
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		neighbors.push_back(vector<int>(0));
	}

	for (int i = 0; i < numberOfEdges; i++)
	{
		int u = edges[i][0];
		int v = edges[i][1];
		neighbors[u].push_back(v);
	}
}

template <typename T>
void Graph<T>::createAdjacencyLists(int numberOfVertices,
	vector<Edge> &edges)
{
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
int Graph<T>::getSize() const
{
	return vertices.size();
}

template <typename T>
int Graph<T>::getDegree(int v) const
{
	return neighbors[v].size();
}

template <typename T>
T Graph<T>::getVertex(int index) const
{
	return vertices[index];
}

template <typename T>
int Graph<T>::getIndex(T v) const
{
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i] == v)
			return i;
	}

	return -1; // If vertex is not in the graph
}

template <typename T>
vector<T> Graph<T>::getVertices() const
{
	return vertices;
}

template <typename T>
vector<int> Graph<T>::getNeighbors(int v) const
{
	return neighbors[v];
}

template <typename T>
void Graph<T>::printEdges() const
{
	for (int u = 0; u < neighbors.size(); u++)
	{
		cout << "Vertex " << u << ": ";
		for (int j = 0; j < neighbors[u].size(); j++)
		{
			cout << "(" << u << ", " << neighbors[u][j] << ") ";
		}
		cout << endl;
	}
}

template <typename T>
void Graph<T>::printAdjacencyMatrix() const
{
	int size = vertices.size();
	// Use vector for 2-D array
	vector< vector<int> > adjacencyMatrix(size);

	// Initialize 2-D array for adjacency matrix
	for (int i = 0; i < size; i++)
	{
		adjacencyMatrix[i] = vector<int>(size);
	}

	for (int i = 0; i < neighbors.size(); i++)
	{
		for (int j = 0; j < neighbors[i].size(); j++)
		{
			int v = neighbors[i][j];
			adjacencyMatrix[i][v] = 1;
		}
	}

	for (int i = 0; i < adjacencyMatrix.size(); i++)
	{
		for (int j = 0; j < adjacencyMatrix[i].size(); j++)
		{
			cout << adjacencyMatrix[i][j] << " ";
		}

		cout << endl;
	}
}

template <typename T>
Tree Graph<T>::dfs(int v) const
{
	vector<int> searchOrders;
	vector<int> parent(vertices.size());
	for (int i = 0; i < vertices.size(); i++)
		parent[i] = -1; // Initialize parent[i] to -1

						// Mark visited vertices
	vector<bool> isVisited(vertices.size());
	for (int i = 0; i < vertices.size(); i++)
	{
		isVisited[i] = false;
	}

	// Recursively search
	dfs(v, parent, searchOrders, isVisited);

	// Return a search tree
	return Tree(v, parent, searchOrders);
}

template <typename T>
void Graph<T>::dfs(int v, vector<int> &parent,
	vector<int> &searchOrders, vector<bool> &isVisited) const
{
	// Store the visited vertex
	searchOrders.push_back(v);
	isVisited[v] = true; // Vertex v visited

	for (int j = 0; j < neighbors[v].size(); j++)
	{
		int i = neighbors[v][j];
		if (!isVisited[i])
		{
			parent[i] = v; // The parent of vertex i is v
			dfs(i, parent, searchOrders, isVisited); // Recursive search
		}
	}
}

template <typename T>
Tree Graph<T>::bfs(int v) const
{
	vector<int> searchOrders;
	vector<int> parent(vertices.size());
	for (int i = 0; i < vertices.size(); i++)
		parent[i] = -1; // Initialize parent[i] to -1

	queue<int> queue; // list used as a queue
	vector<bool> isVisited(vertices.size());
	queue.push(v); // Enqueue v
	isVisited[v] = true; // Mark it visited

	while (!queue.empty())
	{
		int u = queue.front(); // Get the top element
		queue.pop(); // remove the top element
		searchOrders.push_back(u); // u searched
		for (int j = 0; j < neighbors[u].size(); j++)
		{
			int w = neighbors[u][j];
			if (!isVisited[w])
			{
				queue.push(w); // Enqueue w
				parent[w] = u; // The parent of w is u
				isVisited[w] = true; // Mark it visited
			}
		}
	}

	return Tree(v, parent, searchOrders);
}

#endif
