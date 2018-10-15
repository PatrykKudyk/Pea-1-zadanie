#pragma once
#include <vector>

struct brtForce	//tworze strukture do przechowywania wynikow dzialania metody bruteForce
{
	std::vector<int> path;
	int pathCost;
};

class Graph
{
	int verticle; // ilosc wierzcholkow grafu
	short int **graph; //wskaünik na tablice wskaünikÛw
public:
	Graph();
	~Graph();
	void createGiven(std::string name);
	brtForce bruteForce(int startVert);
	void clear();
	void graphReset();
	void display();
	void displayHamilton(brtForce result);
	int getVerticle(); //pobiera ilosc wierzcholkow
};

