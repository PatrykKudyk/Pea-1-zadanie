#pragma once
#include <string>
#include "List.h"

class Graph
{
	int verticle; // ilosc wierzcholkow grafu
	short int **graph; //wskaünik na tablice wskaünikÛw
public:
	Graph();
	~Graph();
	void createGiven(std::string name);
	int bruteForce(int startVert);
	void clear();
	void graphReset();
	void display();
	void displayHamilton(int cost);
	int getVerticle(); //pobiera ilosc wierzcholkow
};

