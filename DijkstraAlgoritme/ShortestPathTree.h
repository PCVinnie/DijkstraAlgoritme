#ifndef SHORTESTPATHTREE_H
#define SHORTESTPATHTREE_H

#include "Tree.h"
#include <vector>

class ShortestPathTree : public Tree
{
public:
	/** Create an empty ShortestPathTree */
	ShortestPathTree() { }

	/** Construct a tree with root, parent, searchOrders, * and cost */
	ShortestPathTree(int root, std::vector<int> parent, std::vector<int> searchOrders, std::vector<int> costs) : Tree(root, parent, searchOrders) {
		this->costs = costs;
	}

	/** Return the cost for the path from the source to vertex v. */
	int getCost(int v) {
		return costs[v];
	}

private:
	std::vector<int> costs;
};
#endif
