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
			graph.createGiven(fileName()); //wczytanie grafu, a przy okazji wprowadzenie nazwy pliku
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
	string name;	//tworzy zmienna klasy string
	cout << "Podaj nazwe pliku : ";
	cin >> name;	//pobiera nazwe od uzytkownika
	name = name + ".txt"; //zmieniam nazwe pliku na taka obslugiwana przez program
	return name;	//zwraca podana przez uzytkownika nazwe
}
