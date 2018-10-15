#include "Graph.h"
#include <iostream>
#include <fstream> //biblioteka do "obs³ugi" plików
#include <vector>
#include <algorithm>

using namespace std;

Graph::Graph()
{
	verticle = 0;
}

Graph::~Graph()
{
	clear();
}

void Graph::createGiven(string name)
{
	ifstream plik; //tworze plik
	int counter = 0; // inicjuje licznik, który u³atwi wpisywanie danych (bêdzie liczy³ wiersze)
	plik.open(name, ios::in); //otwieram plik
	if (plik.good() == true)	//sprawdzam, czy plik otworzyl sie poprawnie
	{
		graphReset(); //resetuje graf
		plik >> verticle;
		graph = new short int *[verticle];	//tworze tablice wskaznikow, ktorej wielkosc jest rowna ilosci wierzcholkow
		for (int i = 0; i < verticle; i++)	//tworze wiersze w tablicy wskaznikow, wiersze dlugosci odpowiadajacej ilosci wierzcholkow
			graph[i] = new short int[verticle];

		for (int i = 0; i < verticle; i++)
			for (int j = 0; j < verticle; j++)
				graph[i][j] = 0;		//przypisuje wszystkim komorkom wartosc poczatkowa 0

		while (!plik.eof())
		{
			for (int i = 0; i < verticle; i++)
				plik >> graph[counter][i];	// w pêtli przypisuje wartoœci po kolei do wiersza oznaczonego jako "counter"

			counter++;	//zwiêkszam numer wiersza
			if (counter >= verticle)  //warunek przekroczenia ilosci danych, jesli plik z danymi by³by Ÿle podany
				break;
		}
	}
	else
	{
		system("cls");
		cout << "Nie udalo sie otworzyc pliku." << endl;
		cin.get();
		cin.get();
		graphReset(); //resetuje graf
	}
	plik.close();	 // zamykam plik
}

brtForce Graph::bruteForce(int startVert)
{
	brtForce result;	//
	result.pathCost = INT_MAX;
	vector<int> vertex;
	for (int i = 0; i < verticle; i++)
		if (i != startVert)
			vertex.push_back(i);
	vector<int> path;
	do
	{
		path.push_back(startVert);
		int currentPathWeight = 0;
		int k = startVert;
		for(int i = 0; i < vertex.size(); i++)
		{
			currentPathWeight += graph[k][vertex[i]];
			k = vertex[i];
			path.push_back(k);
		}
		currentPathWeight += graph[k][startVert];
		path.push_back(startVert);
		if (currentPathWeight < result.pathCost)
		{
			result.pathCost = currentPathWeight;
			result.path = path;
		}
		else
			path.clear();

	} while (next_permutation(vertex.begin(), vertex.end()));


	return result;
}

void Graph::clear()
{
	for (int i = 0; i < verticle; i++)
		delete[] graph[i];
	delete[] graph;
}

void Graph::graphReset()
{
	if (verticle != 0) //sprawdzam, czy istnieje ju¿ jakiœ graf. Jeœli tak to go usuwam i dopiero wczytuje nowy
	{
		clear(); //czyszczenie grafu
		short int **temp1 = nullptr; // tworze wskaznik na nowy graf
		graph = temp1; //przypisuje wskaznik 
		verticle = 0; //zeruje liczbe wierzcholkow
	}
}

void Graph::display()
{
	if (verticle > 0) {
		cout << "Wczytany graf posiada " << verticle << " wierzcholkow, a jego reprezentacja jest nastepujaca:" << endl << endl;

		for (int i = 0; i < verticle; i++)
		{
			if (i == 0)
			{
				cout << "\t";
				for (int m = 0; m < verticle; m++)
					cout << m << "\t";	//wypisuje numery wierzcholkow w pierwszym wierszu
				cout << "<--- numery wierzcholkow" << endl;
				for (int ilosc = 0; ilosc < (verticle * 8) + 2; ilosc++)	//wypisanie wiersza skladajacego sie z ciagu: "----(...)--"
					cout << "-";
				cout << endl;
			}
			cout << i << "\t"; // wypisanie numeru wiersza w pierwszej kolumnie
			for (int j = 0; j < verticle; j++)
				cout << graph[i][j] << "\t";					//wypisywanie wartosci z macierzy

			cout << endl;
			if (i % 2 == 1)
				for (int ilosc = 0; ilosc < (verticle * 8) + 2; ilosc++)		//co drugi wiersz oddzielony jest ciagiem: "----(...)--"
					cout << "-";
			else
				for (int ilosc = 0; ilosc < (verticle * 8) + 2; ilosc++)	//co drugi wiersz oddzielony jest ciagiem: "~~~~(...)~~"
					cout << "~";
			cout << endl;
		}
		cout << "^\n|\n|\nwierzcholki" << endl;
	}
	else
		cout << "Graf nie posiada wierzcholkow, wiec nie mozna go wyswietlic." << endl;
}

void Graph::displayHamilton(brtForce result)
{
	if(verticle != 0)
	{
		cout << "Minimalny koszt hamiltona dla grafu to :" << endl;
		for (int i = 0; i < result.path.size(); i++)
		{
			if (i != 0)
				cout << " - ";
			cout << result.path[i];
		}
		cout << endl << endl << "Waga tego cyklu to : " << result.pathCost << endl;
	}
	else
		cout << "Graf nie posiada wierzcholkow! Nie posiada tez cyklu hamiltona.";
}

int Graph::getVerticle()
{
	return verticle;
}


//NEXTPERMUTATION -  STL'owe
//do B&B wziac sobie najlepiej best first albo wg³¹b przeszukiwanie grafu


//przeszukiwanie grafu w g³¹b i potem obliczanie wag i jezeli najlepsza/najszybsza droga to wynik ustawiamy jako najlepszy
//i potem po wszystkim go wyswietlamy
//jakies inorder czy cos
