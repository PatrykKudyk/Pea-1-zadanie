#include "BranchAndBound.h"
#include <vector>
#include <algorithm>
#include <iostream>



BranchAndBound::BranchAndBound()
{
}

BranchAndBound::~BranchAndBound()
{
}

void BranchAndBound::calculatingPath(int startVert)
{
	bAndB firstReduction;
	std::vector<bAndB> vector;

	firstReduction = matrixStartReduction(this->graph.getGraph(), this->graph.getVertices(), startVert);

	std::cout << "Zredukowany graf : " << std::endl;
	for(int i = 0; i < graph.getVertices(); i++)
	{
		for (int j = 0; j < graph.getVertices(); j++)
			std::cout << firstReduction.graph[i][j] << "\t";
		std::cout << std::endl;
	}
	std::cin.get();
	std::cin.get();


	vector.push_back(firstReduction);
	bAndB temp = vector.front();
	int index = 0;
	bool loopOn = true;
	do
	{
		vector.erase(vector.begin() + index);
		for (int i = 0; i < graph.getVertices(); i++)
			if (!temp.visited[i])
			{
				bAndB temp2 = reducing(temp, temp.vertexNumber, i, firstReduction);
				vector.push_back(temp2);
			}
		//-------ZNALEZIENIE NAJMNIEJSZEGO-------//
		int minRed = INT_MAX;
		for (int i = 0; i < vector.size(); i++)
			if (vector[i].reduction < minRed)
			{
				index = i;
				minRed = vector[i].reduction;
			}
		
		//---------------------------------------//
		temp = vector[index];

		std::cout << "Zredukowany graf : " << std::endl;
		for (int i = 0; i < graph.getVertices(); i++)
		{
			for (int j = 0; j < graph.getVertices(); j++)
				std::cout << temp.graph[i][j] << "\t";
			std::cout << std::endl;
		}
		std::cin.get();
		std::cin.get();

		pathCost = temp.reduction;
		loopOn = isVisitedLeft(temp.visited, graph.getVertices());
		//	std::sort(vector.begin(), vector.end(), compareByCost);
		//	std::sort(vector.rbegin(), vector.rend());
	} while (loopOn);


}

bAndB BranchAndBound::matrixStartReduction(short** graph, int verticles, int startVert)
{
	bAndB result;
	result.vertexNumber = NULL;

	result.graph = copyGraph(graph, verticles);

	result.reduction = 0;		//zmienna przechowujaca wartosc redukcji podstawowej

								//--------------WIERSZE------------------//
	for (int i = 0; i < verticles; i++)		//przechodzenie po wszystkich wierszach
	{
		short minValue = SHRT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
		for (int j = 0; j < verticles; j++)			//przechodzenie po wszystkich kolumnach
			if (i != j)			//mijanie przekatnej macierzy
			{
				if (result.graph[i][j] == 0)		//jesli któraœ komórka jest równa 0, to warunek spe³niony, mo¿na zrezygnowaæ z dalszego sprawdzania
				{
					minValue = 0;		//ustawienie minimalnej wartosci na 0
					break;				//porzucenie dalszego sprawdzania
				}
				minValue = std::min(minValue, result.graph[i][j]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
			}
			else
				result.graph[i][j] = SHRT_MAX;
		for (int j = 0; j < verticles; j++)		//przechodzenie po wrzystkich kolumnach
			if (i != j)			//mijanie przekatnej macierzy
				if (minValue != SHRT_MAX)
					result.graph[i][j] -= minValue;	//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimaln¹
		if (minValue != SHRT_MAX)
			result.reduction += minValue;
	}
	//--------------WIERSZE------------------//


	//--------------KOLUMNY------------------//
	for (int i = 0; i < verticles; i++)		//iteracja po kolumnach
	{
		short minValue = SHRT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
		for (int j = 0; j < verticles; j++)		//iteracja po wierszach
			if (i != j)				//mijanie przekatnej macierzy
			{
				if (result.graph[j][i] == 0)		//jesli któraœ komórka jest równa 0, to warunek spe³niony, mo¿na zrezygnowaæ z dalszego sprawdzania
				{
					minValue = 0;		//ustawienie minimalnej wartosci na 0
					break;				//porzucenie dalszego sprawdzania
				}
				minValue = std::min(minValue, result.graph[j][i]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
			}
			else
				result.graph[i][j] = SHRT_MAX;
		for (int j = 0; j < verticles; j++)		//przechodzenie po wrzystkich wierszach
			if (i != j)			//mijanie przekatnej macierzy
				if (minValue != SHRT_MAX)
					result.graph[j][i] -= minValue;	//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimaln¹
		if (minValue != SHRT_MAX)
			result.reduction += minValue;	}
	//--------------KOLUMNY------------------//

	result.visited = new bool[verticles];
	for (int i = 0; i < verticles; i++)
		result.visited[i] = false;
	result.visited[startVert] = true;

	result.vertexNumber = startVert;

	return result;
}

short** BranchAndBound::copyGraph(short** graph, int size)
{
	short int **newGraph = new short int*[size];
	for (int i = 0; i < size; i++)
		newGraph[i] = new short int[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			newGraph[i][j] = graph[i][j];

	return newGraph;
}

bool* BranchAndBound::copyVisited(bool* visited, int size)
{
	bool *newVisited = new bool[size];
	for (int i = 0; i < size; i++)
		newVisited[i] = visited[i];
	return newVisited;
}

bAndB BranchAndBound::reducing(bAndB given, int startVert, int endVert, bAndB firstReduction)
{
	bAndB result;
	result.reduction = 0;
	result.graph = copyGraph(given.graph, graph.getVertices());
	result.visited = copyVisited(given.visited, graph.getVertices());
	result.visited[endVert] = true;
	result.vertexNumber = endVert;

	for (int i = 0; i < graph.getVertices(); i++)
	{
		result.graph[startVert][i] = SHRT_MAX;
		result.graph[i][endVert] = SHRT_MAX;
	}
	result.graph[endVert][startVert] = SHRT_MAX;

	//--------------WIERSZE------------------//
	for (int i = 0; i < graph.getVertices(); i++)		//przechodzenie po wszystkich wierszach
	{
		short minValue = SHRT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
		for (int j = 0; j < graph.getVertices(); j++)			//przechodzenie po wszystkich kolumnach
			if (i != j)			//mijanie przekatnej macierzy
			{
				if (result.graph[i][j] == 0)		//jesli któraœ komórka jest równa 0, to warunek spe³niony, mo¿na zrezygnowaæ z dalszego sprawdzania
				{
					minValue = 0;		//ustawienie minimalnej wartosci na 0
					break;				//porzucenie dalszego sprawdzania
				}
				minValue = std::min(minValue, result.graph[i][j]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
			}
		for (int j = 0; j < graph.getVertices(); j++)		//przechodzenie po wrzystkich kolumnach
			if (i != j)			//mijanie przekatnej macierzy
				if(minValue != SHRT_MAX)
					result.graph[i][j] -= minValue;	//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimaln¹
		if(minValue != SHRT_MAX)
			result.reduction += minValue;
	}
	//--------------WIERSZE------------------//


	//--------------KOLUMNY------------------//
	for (int i = 0; i < graph.getVertices(); i++)		//iteracja po kolumnach
	{
		short minValue = SHRT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
		for (int j = 0; j < graph.getVertices(); j++)		//iteracja po wierszach
			if (i != j)				//mijanie przekatnej macierzy
			{
				if (result.graph[j][i] == 0)		//jesli któraœ komórka jest równa 0, to warunek spe³niony, mo¿na zrezygnowaæ z dalszego sprawdzania
				{
					minValue = 0;		//ustawienie minimalnej wartosci na 0
					break;				//porzucenie dalszego sprawdzania
				}
				minValue = std::min(minValue, result.graph[j][i]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
			}

		for (int j = 0; j < graph.getVertices(); j++)		//przechodzenie po wrzystkich wierszach
			if (i != j)			//mijanie przekatnej macierzy
				if (minValue != SHRT_MAX)
					result.graph[j][i] -= minValue;	//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimaln¹
		if (minValue != SHRT_MAX)
			result.reduction += minValue;
	}

	result.reduction += given.reduction;
	result.reduction += (int)firstReduction.graph[startVert][endVert];
	return result;
}

bool BranchAndBound::isVisitedLeft(bool* visited, int size)
{
	for (int i = 0; i < size; i++)
		if (visited[i] == false)
			return true;
	return false;
}

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
