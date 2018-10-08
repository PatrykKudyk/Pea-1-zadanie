#pragma once
#include <string>

class Graph
{
	int verticle; // ilosc wierzcholkow grafu
	short int **graph;
public:
	Graph();
	~Graph();
	void createGiven(std::string name);
	int* bruteForce(int vert);
	int* bruteForceFinder(int * vertQued, bool * vertUsed, int vert);
	void clear();
	void graphReset();
	void display();
	int getVerticle(); //pobiera ilosc wierzcholkow
};

