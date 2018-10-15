#pragma once
#include <string>
#include "List.h"

class Graph
{
	int verticle; // ilosc wierzcholkow grafu
	short int **graph; //wska�nik na tablice wska�nik�w
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

