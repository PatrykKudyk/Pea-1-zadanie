#pragma once
#include <xstring>

class Graph
{
	int vertices; // ilosc wierzcholkow grafu
	short int **graph; //wskaünik na tablice wskaünikÛw
public:
	Graph();
	~Graph();
	void createGiven(std::string name);
	void clear();
	void graphReset();
	void display();
	int getVertices(); //pobiera ilosc wierzcholkow
	void setVertices(int value);
	short int** getGraph();
	void setGraphFrag(Graph &obj);
};

