#pragma once
#include "Graph.h"

class Menu
{
	Graph graph; //Obiekt klasy Menu b�dzie zawiera� atrybut klasy Graf, kt�ry jest po prostu przedstawieniem grafu w postaci macierzy s�siedztwa
public:
	Menu();
	~Menu();
	void mainMenu(); //menu g��wne programu
};

