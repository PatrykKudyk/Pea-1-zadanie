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
	bool progWork = true;	//zmienna logiczna, ktora odpowiada za dzialanie badz wylaczenie programu
	int choise;	//numer, ktory wprowadza uzytkownik w momencie wyboru
	string name; // nazwa pliku do wczytania
	do {
		system("cls");
		cout << "[1] Wczytaj dane z pliku." << endl
			<< "[2] Wyswietl dane." << endl
			<< "[3] " << endl
			<< "[4] " << endl
			<< "[5] " << endl
			<< "[6] Wyjdz z programu." << endl;
		cin >> choise;
		switch (choise)
		{
		case 1:
			system("cls");
			name = fileName();
			graph.createGiven(name); //wczytanie grafu
			system("cls");
			graph.display();	//wyswietlenie grafu
			cin.get();			//zabezpieczenie przez zniknieciem danych z konsoli
			cin.get();
			break;
		case 2:
			system("cls");
			graph.display();
			cin.get();
			cin.get();
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			progWork = false;
			break;
		default:
			break;
		}
	} while (progWork);
}

string Menu::fileName()
{
	string name;
	cout << "Podaj nazwe pliku : ";
	cin >> name;
	return name;
}
