#include "Graph.h"
#include <iostream>
#include <fstream> //biblioteka do "obs³ugi" plików

using namespace std;


Graph::Graph()
{
}


Graph::~Graph()
{
	clear();
}

void Graph::createGiven()
{
	ifstream plik; //tworze plik
	int licznik = 0, wp, wk, waga;
	if (verticle != 0) //sprawdzam, czy istnieje ju¿ jakiœ graf. Jeœli tak to go usuwam i dopiero wczytuje nowy
	{
		clear(); //czyszczenie grafu
		short int **temp1 = nullptr; // tworze wskaznik na nowy graf
		graph = temp1; //przypisuje wskaznik 
	}
	plik.open("podane.txt", ios::in); //otwieram plik
	plik >> verticle;
	graph = new short int *[verticle];	//tworze tablice wskaznikow, ktorej wielkosc jest rowna ilosci wierzcholkow
	for (int i = 0; i < verticle; i++)	//tworze wiersze w tablicy wskaznikow, wiersze dlugosci odpowiadajacej ilosci wierzcholkow
		graph[i] = new short int[verticle];
	
	for (int i = 0; i < verticle; i++)
		for (int j = 0; j < verticle; j++)
			graph[i][j] = 0;		//przypisuje wszystkim komorkom wartosc poczatkowa 0
	
	while (!plik.eof())
	{
		plik >> wp >> wk >> waga;
		grafS[wp][licznik] = 1;
		grafS[wk][licznik] = -1;
		grafNS[wp][licznik] = 1;
		grafNS[wk][licznik] = 1;
		wagi[licznik] = waga;
		licznik++;
	}
	plik.close();
}

void Graph::clear()
{
	for (int i = 0; i < verticle; i++)
		delete[] graph[i];
	delete[] graph;
}
