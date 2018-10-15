#pragma once
#include <vector>

struct brtForce	//tworze strukture do przechowywania wynikow dzialania metody bruteForce
{
	std::vector<int> path;	//vector, który przechowuje kolejne wierzcholki po ktorych przechodzi algorytm
	int pathCost;	//zmienna, ktora przechowuje najnizszy koszt
};

class Graph
{
	int vertices; // ilosc wierzcholkow grafu
	short int **graph; //wskaŸnik na tablice wskaŸników
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

