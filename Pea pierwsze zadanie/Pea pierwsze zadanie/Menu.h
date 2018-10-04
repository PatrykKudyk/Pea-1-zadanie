#pragma once
#include "Graph.h"

class Menu
{
	Graph graph; //Obiekt klasy Menu bêdzie zawiera³ atrybut klasy Graf, który jest po prostu przedstawieniem grafu w postaci macierzy s¹siedztwa
public:
	Menu();
	~Menu();
	void mainMenu(); //menu g³ówne programu
};

