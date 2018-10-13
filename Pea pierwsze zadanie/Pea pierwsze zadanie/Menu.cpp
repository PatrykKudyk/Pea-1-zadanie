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
			<< "[3] Znalezc najkrotszy cykl metoda BruteForce." << endl
			<< "[4] " << endl
			<< "[5] " << endl
			<< "[6] Wyjdz z programu." << endl;
		cin >> choise;
		switch (choise)
		{
		case 1:
			system("cls");
			graph.createGiven(getFileName()); //wczytanie grafu, a przy okazji wprowadzenie nazwy pliku
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
			system("cls");
			graph.bruteForce(getNumber());
			graph.displayHamilton();
			cin.get();
			cin.get();
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

string Menu::getFileName()
{
	string name;	//tworzy zmienna klasy string
	cout << "Podaj nazwe pliku : ";
	cin >> name;	//pobiera nazwe od uzytkownika
	name = name + ".txt"; //zmieniam nazwe pliku na taka obslugiwana przez program
	return name;	//zwraca podana przez uzytkownika nazwe
}

int Menu::getNumber()
{
	int choise;
	cout << "Z ktorego wierzcholka chcesz wyruszyc?" << endl
		<< "[1] Z wybranego." << endl
		<< "[2] Z losowego." << endl;
	cin >> choise;
	switch(choise)
	{
	case 1:
		return getNumber(graph.getVerticle());
	case 2:
		return (rand() % graph.getVerticle());
	default:
		break;
	}
	return 0;
}

int Menu::getNumber(int vert)
{
	int number;
	cout << endl << "Podaj wierzcholek startowy z zakresu: [0, " << vert - 1 << "]" << endl;
	cin >> number;
	return number;
}
