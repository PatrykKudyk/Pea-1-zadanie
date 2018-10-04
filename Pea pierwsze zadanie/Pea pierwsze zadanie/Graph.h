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
	void clear();
	void display();
};

