#pragma once
#include "Graph.h"
#include <vector>

class BruteForce
{
	Graph graph;
	std::vector<int> path;	//vector, który przechowuje kolejne wierzcholki po ktorych przechodzi algorytm
	int pathCost;	//zmienna, ktora przechowuje najnizszy koszt

public:
	BruteForce();
	BruteForce(Graph givenGraph);
	~BruteForce();
	void calculatingPath(int startVert);
	std::vector<int> getPath();
	void setPath(std::vector<int> gPath);
	int getPathCost();
	void setPathCost(int gPathCost);
	Graph getGraph();
	void setGraph(Graph &givenGraph);
};