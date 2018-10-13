#pragma once
#include <string>
#include "List.h"

class Graph
{
	int verticle; // ilosc wierzcholkow grafu
	short int **graph; //wskaünik na tablice wskaünikÛw
	List verticleList; //stos do obs≥ugi bruteForce'a
	List hamiltonCycle;
	int startVert;
public:
	Graph();
	~Graph();
	void createGiven(std::string name);
	void bruteForce(int vert);
	void hamilton(int vert, bool * &visited, int cost, int costMin);
	void clear();
	void graphReset();
	void display();
	void displayHamilton();
	int getVerticle(); //pobiera ilosc wierzcholkow
};

