#pragma once
#include <vector>

struct hamilton	//tworze strukture do przechowywania wynikow algorytm�w (�cie�ka i jej koszt)
{
	std::vector<int> path;	//vector, kt�ry przechowuje kolejne wierzcholki po ktorych przechodzi algorytm
	int pathCost;	//zmienna, ktora przechowuje najnizszy koszt
};

struct check
{
	short int **graph;
	int reduction;
};

struct bAndB
{
	int vertexNumber;
	check data;
};



class Graph
{
	int vertices; // ilosc wierzcholkow grafu
	short int **graph; //wska�nik na tablice wska�nik�w
public:
	Graph();
	~Graph();
	void createGiven(std::string name);
	hamilton bruteForce(int startVert);
	hamilton branchAndBound(int startVert);
	short int** copyGraph(int**graph, int size);
	check reducing(short int** graph, int startVert, int endVert);
	void clear();
	void graphReset();
	void display();
	void displayHamilton(hamilton result);
	int getVertices(); //pobiera ilosc wierzcholkow
};

