#include "Menu.h"
#include <iostream>

using namespace std;


Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::mainMenu()
{
	bool dzialanie = true;
	int wybor;
	do {
		system("cls");
		cout << "[1] Wczytaj dane z pliku." << endl
			<< "[2] Wyswietl dane." << endl
			<< "[3] " << endl
			<< "[4] " << endl
			<< "[5] " << endl
			<< "[6] " << endl;
		cin >> wybor;
		switch (wybor)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			break;
		}
	} while (dzialanie);
}
