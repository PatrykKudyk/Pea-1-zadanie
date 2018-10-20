#pragma once
#include <vector>
#include "Graph.h"



struct bAndB
{
	int vertexNumber;
	short int **graph;
	int reduction;
	bool *visited;
};

class BranchAndBound
{
	Graph graph;
	std::vector<int> path;	//vector, który przechowuje kolejne wierzcholki po ktorych przechodzi algorytm
	int pathCost;	//zmienna, ktora przechowuje najnizszy koszt

public:
	BranchAndBound();
	~BranchAndBound();
	bool compareByCost(const bAndB &a, const bAndB &b);
	void calculatingPath(int startVert);
	bAndB matrixStartReduction(short** graph, int verticles, int startVert);
	short int** copyGraph(short**graph, int size);
	bool* copyVisited(bool*visited, int size);
	bAndB reducing(bAndB given, int startVert, int endVert, bAndB firstReduction);
	bool isVisitedLeft(bool* visited, int size);
	std::vector<int> getPath();
	void setPath(std::vector<int> gPath);
	int getPathCost();
	void setPathCost(int gPathCost);
	Graph getGraph();
	void setGraph(Graph &givenGraph);
};

