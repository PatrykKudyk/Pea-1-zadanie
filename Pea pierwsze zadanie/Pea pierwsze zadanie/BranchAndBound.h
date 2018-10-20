#pragma once
#include <vector>
#include "Graph.h"

struct check
{
	short int **graph;
	int reduction;
};

struct bAndB
{
	int vertexNumber;
	check data;
};

class BranchAndBound
{
	Graph graph;
	std::vector<int> path;	//vector, który przechowuje kolejne wierzcholki po ktorych przechodzi algorytm
	int pathCost;	//zmienna, ktora przechowuje najnizszy koszt

public:
	BranchAndBound(Graph givenGraph);
	~BranchAndBound();
	bool compareByCost(const bAndB &a, const bAndB &b);
	void calculatingPath(int startVert);
	short int** copyGraph(int**graph, int size);
	check reducing(short int** graph, int startVert, int endVert);
};

