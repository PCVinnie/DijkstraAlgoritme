#ifndef WEIGHTEDEDGE_H
#define WEIGHTEDEDGE_H
#include "Edge.h"

class WeightedEdge : public Edge {

public:
	double weight; // The weight on edge (u, v) 

	// Create a weighted edge on (u, v) 
	WeightedEdge(int u, int v, double weight) : Edge(u, v) {
		this->weight = weight;
	}

	// Compare edges based on weights 
	bool operator<(const WeightedEdge& edge) const {
		return (*this).weight < edge.weight;
	}

	bool operator<=(const WeightedEdge& edge) const {
		return (*this).weight <= edge.weight;
	}

	bool operator>(const WeightedEdge& edge) const {
		return (*this).weight > edge.weight;
	}

	bool operator>=(const WeightedEdge& edge) const {
		return (*this).weight >= edge.weight;
	}

	bool operator==(const WeightedEdge& edge) const {
		return (*this).weight == edge.weight;
	}

	bool operator!=(const WeightedEdge& edge) const {
		return (*this).weight != edge.weight;
	}

};

#endif