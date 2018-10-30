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
	std::vector<bAndB> vector;	//tworze wektor do przechowywania wlasnych struktur
	bAndB firstReduction = matrixStartReduction(this->graph.getGraph(), this->graph.getVertices(), startVert);		//tworze strukture, w ktorej bêdê przechowywa³ pierwsza zredukowana macierz
	vector.push_back(firstReduction);	//dodaje do vektora "macierz pierwszej redukcji"
	bAndB temp = vector.front();	//tworze pomocnicza zmienn¹, w ktorej bêdê przechowywa³ chwilowo rozpatrywan¹ strukture
	int index = 0;		//tworze zmienna index, ktora bedzie przechowywac index "najlepszej" struktury z wektora
	bool loopOn = true;		//zmienna logiczna sprawdzajaca, czy znaleziono ju¿ œcie¿kê
	do
	{
		vector.erase(vector.begin() + index);	//usuwam z wektora strukture, któr¹ bêdê teraz rozpatrywa³ w pêtli
		for (int i = 0; i < graph.getVertices(); i++)	//iteruje po wszystkich wierzcho³kach
			if (!temp.visited[i])		//sprawdzam, czy wierzcholek byl juz odwiedzony wczesniej
			{
				bAndB temp2 = reducing(temp, temp.vertexNumber, i, startVert);		//tworze druga zmienna pomocnicza i przetwarzam j¹ funkcj¹ obliczaj¹c¹ redukcje
				vector.push_back(temp2);	//dodaje strukture do wektora
			}
		//-------ZNALEZIENIE NAJMNIEJSZEGO-------//
		int minRed = INT_MAX;	//ustawiam minimalna redukcje na nieskonczonosc
		index = NULL;		//zeruje index
		for (int i = 0; i < vector.size(); i++)		//iteruje po wszystkich wierzcholkach
			if (vector[i].reduction < minRed)		//sprawdzam czy redukcja chwilowej struktury jest mniejsza niz aktualna najmniejsza 
			{
				index = i;		//zapamietuje index tejze struktury w wektorze
				minRed = vector[i].reduction;	//aktualizuje najmniejsza redukcjê
			}
		//---------------------------------------//

		temp = vector[index];			//przypisuje zmiennej pomocniczej now¹ strukture, ktora znajduje sie w wektorze struktur pod indeksem "index"
		pathCost = temp.reduction;		//aktualizuje chwilowy najmniejszy koszt
		path = temp.path;				//aktualizuje chwilow¹ œcie¿kê hamiltona, dla chwilowego kosztu
		loopOn = isVisitedLeft(temp.visited, graph.getVertices());		//sprawdzam czy zosta³a ju¿ znaleziona œcie¿ka
	} while (loopOn);		//pêtla dziz³a dopóki nie zostanie znaleziona œcie¿ka

	path.push_back(startVert);	//dodaje do œcie¿ki ostatni wierzcho³ek, którym jest wierzcho³ek startowy
	do{
		for (int i = 0; i < graph.getVertices(); i++)
			delete[] vector[0].graph[i];
		delete[] vector[0].graph;
		delete vector[0].visited;
		vector.erase(vector.begin());
	} while (!vector.empty());
}

bAndB BranchAndBound::matrixStartReduction(short** graph, int verticles, int startVert)
{
	bAndB result;		//tworze obiekt struktury, ktory bedzie przechowywal wyniki
	result.graph = copyGraph(graph, verticles);	//kopiuje podany graf, zeby moc potem na nim dokonac redukcji ---- zapisuje go rowniez od razu w strukturze

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
				result.graph[i][j] = SHRT_MAX;			//ustawiam "nieskonczonosc" na przekatnej macierzy
		for (int j = 0; j < verticles; j++)		//przechodzenie po wrzystkich kolumnach
			if (i != j)			//mijanie przekatnej macierzy
				if (minValue != SHRT_MAX)	//sprawdzam, czy minimalna wartosc ulegla jakiejkolwiek zmianie
					if (result.graph[i][j] != SHRT_MAX)		//sprawdzam, czy dana komórka nie by³a ju¿ wczesniej zmieniana na nieskonczonosc
						result.graph[i][j] -= minValue;	//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimaln¹
		if (minValue != SHRT_MAX)			//sprawdzam, czy minimalna wartosc ulegla jakiejkolwiek zmianie
			result.reduction += minValue;	//uaktualniam calkowita redukcje
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
				result.graph[i][j] = SHRT_MAX;		//ustawiam "nieskonczonosc" na przekatnej macierzy
		for (int j = 0; j < verticles; j++)		//przechodzenie po wrzystkich wierszach
			if (i != j)			//mijanie przekatnej macierzy
				if (minValue != SHRT_MAX)		//sprawdzam, czy minimalna wartosc ulegla jakiejkolwiek zmianie
					if (result.graph[j][i] != SHRT_MAX)		//sprawdzam, czy dana komórka nie by³a ju¿ wczesniej zmieniana na nieskonczonosc
						result.graph[j][i] -= minValue;	//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimaln¹
		if (minValue != SHRT_MAX)		//sprawdzam, czy minimalna wartosc ulegla jakiejkolwiek zmianie
			result.reduction += minValue;	//uaktualniam calkowita redukcje
	}
	//--------------KOLUMNY------------------//

	result.visited = new bool[verticles];	//tworze dynamiczna tablice z lista odwiedzonych wierzcholkow
	for (int i = 0; i < verticles; i++)		
		result.visited[i] = false;			//ustawiam wszystkie wierzcholki jako nieodwiedzone
	result.visited[startVert] = true;		//ustawiam wierzcholek poczatkowy jako odwiedzony

	result.vertexNumber = startVert;		//ustawiam numer wierzcholka w ktorym jestem
	result.path.push_back(startVert);		//wstawiam aktualny wierzcholek do przechowywanej drogi
	return result;		//zwracam strukture z wynikami
}

short** BranchAndBound::copyGraph(short** graph, int size)
{
	short int **newGraph = new short int*[size];		//tworze nowy wskaznik na tablice wskaznikow
	for (int i = 0; i < size; i++)
		newGraph[i] = new short int[size];		//w kazdym wierszu tworze nowa tablice dynamiczna

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

bAndB BranchAndBound::reducing(bAndB given, int startVert, int endVert, int firstVertex)
{
	bAndB result;		//tworze strukture z wynikami
	result.reduction = 0;		//ustawiam redukcje na 0
	result.graph = copyGraph(given.graph, graph.getVertices());			//kopiuje do wynikow graf wejsciowy, aby moc go modyfikowac
	result.visited = copyVisited(given.visited, graph.getVertices());	//kopiuje liste odwiedzonych wierzcholkow
	result.visited[endVert] = true;		//ustawiam aktualny wierzcholek jako odwiedzony
	result.vertexNumber = endVert;		//ustawiam numer wierzcholka jako aktualny wierzcholek
	result.path = given.path;			//kopiuje droge ze struktury wejsciowej
	result.path.push_back(endVert);		//dodaje do drogi aktualny wierzcholek

	for (int i = 0; i < graph.getVertices(); i++)
	{
		result.graph[startVert][i] = SHRT_MAX;		//ustawiam wartoœci w wierszu wierzcholka z ktorego przechodze na nieskonczonosc
		result.graph[i][endVert] = SHRT_MAX;		//ustawiam wartosci w kolumnie wierzcholka do ktorego przechodze na nieskonczonosc
	}
	result.graph[endVert][firstVertex] = SHRT_MAX;	//ustawiam nieskonczonosc w komorce odpowiadajacej przejsciu z (wierzcholka do ktorego przechodze) do (wierzcholka startowego)

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
				if(minValue != SHRT_MAX)		//sprawdzam czy minimalna waga ulegla zmianie
					if(result.graph[i][j] != SHRT_MAX)		//sprawdzam, czy komorka nie jest juz rowna nieskonczonosci
						result.graph[i][j] -= minValue;		//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimaln¹
		if(minValue != SHRT_MAX)	//sprawdzam czy minimalna waga ulegla zmianie
			result.reduction += minValue;		//uaktualniam chwilowa redukcje
	}
	//--------------WIERSZE------------------//


	//--------------KOLUMNY------------------//
	for (int i = 0; i < graph.getVertices(); i++)		//iteracja po kolumnach
	{
		short minValue = SHRT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
		for (int j = 0; j < graph.getVertices(); j++)		//iteracja po wierszach
		{
			if (i != j)				//mijanie przekatnej macierzy
			{
				if (result.graph[j][i] == 0)		//jesli któraœ komórka jest równa 0, to warunek spe³niony, mo¿na zrezygnowaæ z dalszego sprawdzania
				{
					minValue = 0;		//ustawienie minimalnej wartosci na 0
					break;				//porzucenie dalszego sprawdzania
				}
				minValue = std::min(minValue, result.graph[j][i]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
			}
		}

		for (int j = 0; j < graph.getVertices(); j++)		//przechodzenie po wrzystkich wierszach
			if (i != j)			//mijanie przekatnej macierzy
				if (minValue != SHRT_MAX)		//sprawdzam czy minimalna waga ulegla zmianie
					if (result.graph[j][i] != SHRT_MAX)		//sprawdzam czy wartosc komórki nie wynosi nieskonczonosc
						result.graph[j][i] -= minValue;		//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimaln¹
		if (minValue != SHRT_MAX)		//sprawdzam czy minimalna waga ulegla zmianie
			result.reduction += minValue;		//uaktualniam chwilowa redukcje
	}

	result.reduction += given.reduction;		//uaktualniam redukcje o redukcje struktury wejsciowej
	result.reduction += (int)given.graph[startVert][endVert];	//uaktualniam redukcje o redukcje przejscia pomiedzy wierzcholkami w strukturze wejsciowej
	return result;		//zwracam strukture z wynikami
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
