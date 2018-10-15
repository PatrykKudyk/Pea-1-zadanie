#include "Graph.h"
#include <iostream>
#include <fstream> //biblioteka do "obs�ugi" plik�w
#include <vector>
#include <algorithm>

using namespace std;

Graph::Graph()
{
	vertices = 0;
}

Graph::~Graph()
{
	clear();
}

void Graph::createGiven(string name)
{
	ifstream plik; //tworze plik
	int counter = 0; // inicjuje licznik, kt�ry u�atwi wpisywanie danych (b�dzie liczy� wiersze)
	plik.open(name, ios::in); //otwieram plik
	if (plik.good() == true)	//sprawdzam, czy plik otworzyl sie poprawnie
	{
		graphReset(); //resetuje graf
		plik >> vertices;
		graph = new short int *[vertices];	//tworze tablice wskaznikow, ktorej wielkosc jest rowna ilosci wierzcholkow
		for (int i = 0; i < vertices; i++)	//tworze wiersze w tablicy wskaznikow, wiersze dlugosci odpowiadajacej ilosci wierzcholkow
			graph[i] = new short int[vertices];

		for (int i = 0; i < vertices; i++)
			for (int j = 0; j < vertices; j++)
				graph[i][j] = 0;		//przypisuje wszystkim komorkom wartosc poczatkowa 0

		while (!plik.eof())
		{
			for (int i = 0; i < vertices; i++)
				plik >> graph[counter][i];	// w p�tli przypisuje warto�ci po kolei do wiersza oznaczonego jako "counter"

			counter++;	//zwi�kszam numer wiersza
			if (counter >= vertices)  //warunek przekroczenia ilosci danych, jesli plik z danymi by�by �le podany
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
	brtForce result;	//tworze zmienna lokalna przy uzyciu struktury brtForce
	result.pathCost = INT_MAX;	//ustawiam minimalny koszt przejscia na maksymalny, ktory jest dostepny w int'cie tak, aby potem mozna bylo znale�� najkrotszy przez por�wnywanie
	vector<int> vertex; //tworze vektor int�w o nazwie vertex, w ktorym b�d� przechowywa� wszystkie wierzcholki poza startowym
	vector<int> path;	//tworze vektor intow o nazwie path, do przechowywania kolejnych wierzcholkow dla chwilowej sciezki
	for (int i = 0; i < vertices; i++)
		if (i != startVert)	
			vertex.push_back(i);	//wrzucam do wektora wszystkie wierzcholki poza startowym, �eby unikn�� p�tli
	
	do
	{
		path.push_back(startVert);	//startowy wierzcholek ustawiam jako pierwszy
		int currentPathWeight = 0;	//ustawiam poczatkowy koszt przejscia jako zero, bo dopiero startujemy
		int k = startVert;	//tworze zmienna k, ktora bedzie wskazywala chwilowo rozpatrywany wierzcholek
		for(int i = 0; i < vertex.size(); i++)
		{
			currentPathWeight += graph[k][vertex[i]];	//dodaje do aktualnej wagi drogi wag� kolejnego przejscia
			k = vertex[i];	//przypisuje zmiennej "k" numer kolejnego wierzcholka
			path.push_back(k);	//dodaje kolejny wierzcholek do vektora je przechowuj�cego
		}
		currentPathWeight += graph[k][startVert];	//uaktualniam ca�kowity koszt drogi o przej�cie z przedostatniego wierzcho�ka do wierzcho�ka startowego
		path.push_back(startVert);	//dodaje ostatni wierzcholek drogi przej��, kt�rym jest wierzcho�ek startowy
		if (currentPathWeight < result.pathCost)	//sprawdzam czy koszt drogi, ktora wlasnie byla sprawdzana jest mniejszy od (p�ki co) najmniejszej
		{
			result.pathCost = currentPathWeight;	//uaktualniam najnizszy koszt przechowywany w strukturze
			result.path = path;	//uaktualniam drog�, kt�ra jest przechowywana w strukturze
		}
		else
			path.clear(); // je�li koszt nie jest ni�szy, to czyszcz� vector z kolejnymi wierzcho�kami, �eby m�c rozpatrywa� now� drog�

	} while (next_permutation(vertex.begin(), vertex.end()));	//p�tla, kt�ra ko�czy si� dopiero po sprawdzeniu wszystkich mo�liwych permutacji dr�g


	return result;	//zwracam struktur�, kt�ra przechowuje drog� o najni�szym koszcie oraz ten�e koszt
}

void Graph::clear()
{
	for (int i = 0; i < vertices; i++)
		delete[] graph[i];
	delete[] graph;
}

void Graph::graphReset()
{
	if (vertices != 0) //sprawdzam, czy istnieje ju� jaki� graf. Je�li tak to go usuwam i dopiero wczytuje nowy
	{
		clear(); //czyszczenie grafu
		short int **temp1 = nullptr; // tworze wskaznik na nowy graf
		graph = temp1; //przypisuje wskaznik 
		vertices = 0; //zeruje liczbe wierzcholkow
	}
}

void Graph::display()
{
	if (vertices > 0) {
		cout << "Wczytany graf posiada " << vertices << " wierzcholkow, a jego reprezentacja jest nastepujaca:" << endl << endl;

		for (int i = 0; i < vertices; i++)
		{
			if (i == 0)
			{
				cout << "\t";
				for (int m = 0; m < vertices; m++)
					cout << m << "\t";	//wypisuje numery wierzcholkow w pierwszym wierszu
				cout << "<--- numery wierzcholkow" << endl;
				for (int ilosc = 0; ilosc < (vertices * 8) + 2; ilosc++)	//wypisanie wiersza skladajacego sie z ciagu: "----(...)--"
					cout << "-";
				cout << endl;
			}
			cout << i << "\t"; // wypisanie numeru wiersza w pierwszej kolumnie
			for (int j = 0; j < vertices; j++)
				cout << graph[i][j] << "\t";					//wypisywanie wartosci z macierzy

			cout << endl;
			if (i % 2 == 1)
				for (int ilosc = 0; ilosc < (vertices * 8) + 2; ilosc++)		//co drugi wiersz oddzielony jest ciagiem: "----(...)--"
					cout << "-";
			else
				for (int ilosc = 0; ilosc < (vertices * 8) + 2; ilosc++)	//co drugi wiersz oddzielony jest ciagiem: "~~~~(...)~~"
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
	if(vertices != 0)	//sprawdzenie czy graf nie jest pusty
	{
		cout << "Minimalny koszt hamiltona dla grafu to :" << endl;
		for (int i = 0; i < result.path.size(); i++)
		{
			if (i != 0)
				cout << " - ";
			cout << result.path[i];	//wypisanie kolejnych wierzcholkow przejscia
		}
		cout << endl << endl << "Waga tego cyklu to : " << result.pathCost << endl;	//wyswietlenie kosztu najtanszego przejscia
	}
	else
		cout << "Graf nie posiada wierzcholkow! Nie posiada tez cyklu hamiltona.";
}

int Graph::getVerticle()
{
	return vertices;
}



//do B&B wziac sobie najlepiej best first albo wg��b przeszukiwanie grafu

