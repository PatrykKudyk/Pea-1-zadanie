#include "BruteForce.h"
#include <vector>
#include <algorithm>



BruteForce::BruteForce()
{
}

BruteForce::~BruteForce()
{
}

void BruteForce::calculatingPath(int startVert)
{
	pathCost = INT_MAX;	//ustawiam minimalny koszt przejscia na maksymalny, ktory jest dostepny w int'cie tak, aby potem mozna bylo znaleŸæ najkrotszy przez porównywanie
	std::vector<int> vertex; //tworze vektor intów o nazwie vertex, w ktorym bêdê przechowywa³ wszystkie wierzcholki poza startowym
	std::vector<int> path;	//tworze vektor intow o nazwie path, do przechowywania kolejnych wierzcholkow dla chwilowej sciezki
	for (int i = 0; i < graph.getVertices(); i++)
		if (i != startVert)
			vertex.push_back(i);	//wrzucam do wektora wszystkie wierzcholki poza startowym, ¿eby unikn¹æ pêtli

	do
	{
		path.push_back(startVert);	//startowy wierzcholek ustawiam jako pierwszy
		int currentPathWeight = 0;	//ustawiam poczatkowy koszt przejscia jako zero, bo dopiero startujemy
		int k = startVert;	//tworze zmienna k, ktora bedzie wskazywala chwilowo rozpatrywany wierzcholek
		for (int i = 0; i < vertex.size(); i++)
		{
			currentPathWeight += graph.getGraph()[k][vertex[i]];	//dodaje do aktualnej wagi drogi wagê kolejnego przejscia
			k = vertex[i];	//przypisuje zmiennej "k" numer kolejnego wierzcholka
			path.push_back(k);	//dodaje kolejny wierzcholek do vektora je przechowuj¹cego
		}
		currentPathWeight += graph.getGraph()[k][startVert];	//uaktualniam ca³kowity koszt drogi o przejœcie z przedostatniego wierzcho³ka do wierzcho³ka startowego
		path.push_back(startVert);	//dodaje ostatni wierzcholek drogi przejœæ, którym jest wierzcho³ek startowy
		if (currentPathWeight < pathCost)	//sprawdzam czy koszt drogi, ktora wlasnie byla sprawdzana jest mniejszy od (póki co) najmniejszej
		{
			pathCost = currentPathWeight;	//uaktualniam najnizszy koszt przechowywany w strukturze
			this->path = path;	//uaktualniam drogê, która jest przechowywana w strukturze
		}
		else
			path.clear(); // jeœli koszt nie jest ni¿szy, to czyszczê vector z kolejnymi wierzcho³kami, ¿eby móc rozpatrywaæ now¹ drogê

	} while (next_permutation(vertex.begin(), vertex.end()));	//pêtla, która koñczy siê dopiero po sprawdzeniu wszystkich mo¿liwych permutacji dróg
}

std::vector<int> BruteForce::getPath()
{
	return path;
}

void BruteForce::setPath(std::vector<int> gPath)
{
	path = gPath;
}

int BruteForce::getPathCost()
{
	return pathCost;
}

void BruteForce::setPathCost(int gPathCost)
{
	pathCost = gPathCost;
}

Graph BruteForce::getGraph()
{
	return graph;
}

void BruteForce::setGraph(Graph &givenGraph)
{
	graph.setVertices(givenGraph.getVertices());
	graph.setGraphFrag(givenGraph);
}
