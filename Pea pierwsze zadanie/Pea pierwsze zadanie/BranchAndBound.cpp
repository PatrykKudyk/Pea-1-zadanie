#include "BranchAndBound.h"
#include <vector>
#include <algorithm>



BranchAndBound::BranchAndBound(Graph givenGraph)
{
	graph = givenGraph;
}


BranchAndBound::~BranchAndBound()
{
}
/*
bool BranchAndBound::compareByCost(const bAndB& a, const bAndB& b)
{
	return a.data.reduction < b.data.reduction;
}

void BranchAndBound::calculatingPath(int startVert)
{
	hamilton result;	//tworze obiekt struktury, do przechowywania wynikow

						//----------------TWORZE GRAF POMOCNICZY------------//
	short int **tempGraph = new short int *[vertices];
	for (int i = 0; i < vertices; i++)
		tempGraph[i] = new short int[vertices];
	//----------------TWORZE GRAF POMOCNICZY------------//


	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++)
		{
			if (i == j)
				tempGraph[i][j] = SHRT_MAX;			//przypisuje wartosci maksymalne na przekatnej macierzy sasiedztwa
			else
				tempGraph[i][j] = graph[i][j];		//"klonowanie" macierzy sasiedztwa do tymczaseowej macierzy
		}

	//-------------------------------------MINIMALIZACJA DRÓG--------------------------------//

	int mainReduction = 0;		//zmienna przechowujaca wartosc redukcji podstawowej

								//--------------WIERSZE------------------//
	for (int i = 0; i < vertices; i++)		//przechodzenie po wszystkich wierszach
	{
		short minValue = SHRT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
		for (int j = 0; j < vertices; j++)			//przechodzenie po wszystkich kolumnach
			if (i != j)			//mijanie przekatnej macierzy
			{
				if (tempGraph[i][j] == 0)		//jesli któraœ komórka jest równa 0, to warunek spe³niony, mo¿na zrezygnowaæ z dalszego sprawdzania
				{
					minValue = 0;		//ustawienie minimalnej wartosci na 0
					break;				//porzucenie dalszego sprawdzania
				}
				minValue = min(minValue, tempGraph[i][j]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
			}
		for (int j = 0; j < vertices; j++)		//przechodzenie po wrzystkich kolumnach
			if (i != j)			//mijanie przekatnej macierzy
				tempGraph[i][j] -= minValue;	//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimaln¹
		mainReduction += minValue;
	}
	//--------------WIERSZE------------------//


	//--------------KOLUMNY------------------//
	for (int i = 0; i < vertices; i++)		//iteracja po kolumnach
	{
		short minValue = SHRT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
		for (int j = 0; j < vertices; j++)		//iteracja po wierszach
			if (i != j)				//mijanie przekatnej macierzy
			{
				if (tempGraph[j][i] == 0)		//jesli któraœ komórka jest równa 0, to warunek spe³niony, mo¿na zrezygnowaæ z dalszego sprawdzania
				{
					minValue = 0;		//ustawienie minimalnej wartosci na 0
					break;				//porzucenie dalszego sprawdzania
				}
				minValue = min(minValue, tempGraph[j][i]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
			}

		for (int j = 0; j < vertices; j++)		//przechodzenie po wrzystkich wierszach
			if (i != j)			//mijanie przekatnej macierzy
				tempGraph[j][i] -= minValue;	//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimaln¹
		mainReduction += minValue;
	}
	//--------------KOLUMNY------------------//


	//------------------------------------------MINIMALIZACJA DRÓG-----------------------------------//

	bool *visited = new bool[vertices];
	for (int i = 0; i < vertices; i++)
		visited = false;
	visited[startVert] = true;
	vector<bAndB> vector;
	bAndB temp;
	temp.data.reduction = mainReduction;
	temp.data.graph = tempGraph;
	temp.vertexNumber = startVert;
	vector.push_back(temp);

	do
	{

		for (int i = 0; i < vertices; i++)
			if (!visited[i])
			{

			}
		sort(vector.begin(), vector.end(), compareByCost);

	} while ();


	//-----------------USUWANIE OBIEKTÓW--------------------//
	delete[] visited;
	for (int i = 0; i < vertices; i++)
		delete[] tempGraph[i];
	delete[] tempGraph;
	//-----------------USUWANIE OBIEKTÓW--------------------//

	return result;	//zwracam obiekt z wynikami (kosztem œcie¿ki i sam¹ œcie¿k¹)
}

short** BranchAndBound::copyGraph(int** graph, int size)
{
	short int **newGraph = new short int*[size];
	for (int i = 0; i < size; i++)
		newGraph[i] = new short int[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			newGraph[i][j] = graph[i][j];

	return newGraph;
}

check BranchAndBound::reducing(short** graph, int startVert, int endVert)
{
	check result;
	result.reduction = 0;

	for (int i = 0; i < vertices; i++)
	{
		graph[startVert][i] = SHRT_MAX;
		graph[i][endVert] = SHRT_MAX;
	}
	graph[endVert][startVert] = SHRT_MAX;





	//--------------WIERSZE------------------//
	for (int i = 0; i < vertices; i++)		//przechodzenie po wszystkich wierszach
	{
		short minValue = SHRT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
		for (int j = 0; j < vertices; j++)			//przechodzenie po wszystkich kolumnach
			if (i != j)			//mijanie przekatnej macierzy
			{
				if (graph[i][j] == 0)		//jesli któraœ komórka jest równa 0, to warunek spe³niony, mo¿na zrezygnowaæ z dalszego sprawdzania
				{
					minValue = 0;		//ustawienie minimalnej wartosci na 0
					break;				//porzucenie dalszego sprawdzania
				}
				minValue = min(minValue, graph[i][j]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
			}
		for (int j = 0; j < vertices; j++)		//przechodzenie po wrzystkich kolumnach
			if (i != j)			//mijanie przekatnej macierzy
				graph[i][j] -= minValue;	//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimaln¹
		result.reduction += minValue;
	}
	//--------------WIERSZE------------------//


	//--------------KOLUMNY------------------//
	for (int i = 0; i < vertices; i++)		//iteracja po kolumnach
	{
		short minValue = SHRT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
		for (int j = 0; j < vertices; j++)		//iteracja po wierszach
			if (i != j)				//mijanie przekatnej macierzy
			{
				if (graph[j][i] == 0)		//jesli któraœ komórka jest równa 0, to warunek spe³niony, mo¿na zrezygnowaæ z dalszego sprawdzania
				{
					minValue = 0;		//ustawienie minimalnej wartosci na 0
					break;				//porzucenie dalszego sprawdzania
				}
				minValue = min(minValue, graph[j][i]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
			}

		for (int j = 0; j < vertices; j++)		//przechodzenie po wrzystkich wierszach
			if (i != j)			//mijanie przekatnej macierzy
				graph[j][i] -= minValue;	//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimaln¹
		result.reduction += minValue;
	}
	return result;
}

*/

std::vector<int> BranchAndBound::getPath()
{
	return path;
}

void BranchAndBound::setPath(std::vector<int> gPath)
{
	path = gPath;
}

int BranchAndBound::getPathCost()
{
	return pathCost;
}

void BranchAndBound::setPathCost(int gPathCost)
{
	pathCost = gPathCost;
}

Graph BranchAndBound::getGraph()
{
	return graph;
}

void BranchAndBound::setGraph(Graph &givenGraph)
{
	graph.setVertices(givenGraph.getVertices());
	graph.setGraphFrag(givenGraph);
}
