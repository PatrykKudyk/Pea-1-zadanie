#pragma once
class Graph
{
	int verticle; // ilosc wierzcholkow grafu
	short int **graph;
public:
	Graph();
	~Graph();
	void createGiven();
	void clear();
};

