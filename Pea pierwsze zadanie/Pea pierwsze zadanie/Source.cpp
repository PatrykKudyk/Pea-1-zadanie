#include <iostream>
#include "Menu.h"
#include <ctime>
#include "BranchAndBound.h"
#include "BruteForce.h"
#include <fstream>
#include "TimeMeasure.h"
#include <vector>

using namespace std;

//void generacjaDanych(int N);

int main()
{
	srand(time(NULL));
	Menu menu; //Tworze sobie obiektklasy menu, z którego potem steruje programem
	menu.mainMenu();
	/*TimeMeasure pomiary;
	Graph graf;
	vector<double>czasyBrute;
	vector<double>czasyBranch;
	
	int N = 6;
	for (int i = 0; i < 100; i++)
	{
		BruteForce brute;
		BranchAndBound branch;
		generacjaDanych(N);
		graf.createGiven("daneDoTestow.txt");
		brute.setGraph(graf);
		branch.setGraph(graf);
		pomiary.startCounting();
		brute.calculatingPath(0);
		czasyBrute.push_back(pomiary.getCounter());
		pomiary.startCounting();
		branch.calculatingPath(0);
		czasyBranch.push_back(pomiary.getCounter());
		cout << N << " - Wielkosc    " << i << " - Zrobione" << endl;
	}
	pomiary.saveToFile(czasyBrute, "bruteForce6.txt");
	pomiary.saveToFile(czasyBranch, "branchAndBound6.txt");
	czasyBrute.clear();
	czasyBranch.clear();
	
	N = 7;
	for (int i = 0; i < 100; i++)
	{
		BruteForce brute;
		BranchAndBound branch;
		generacjaDanych(N);
		graf.createGiven("daneDoTestow.txt");
		brute.setGraph(graf);
		branch.setGraph(graf);
		pomiary.startCounting();
		brute.calculatingPath(0);
		czasyBrute.push_back(pomiary.getCounter());
		pomiary.startCounting();
		branch.calculatingPath(0);
		czasyBranch.push_back(pomiary.getCounter());
		cout << N << " - Wielkosc    " << i << " - Zrobione" << endl;
	}
	pomiary.saveToFile(czasyBrute, "bruteForce7.txt");
	pomiary.saveToFile(czasyBranch, "branchAndBound7.txt");
	czasyBrute.clear();
	czasyBranch.clear();

	N = 8;
	for (int i = 0; i < 100; i++)
	{
		BruteForce brute;
		BranchAndBound branch;
		generacjaDanych(N);
		graf.createGiven("daneDoTestow.txt");
		brute.setGraph(graf);
		branch.setGraph(graf);
		pomiary.startCounting();
		brute.calculatingPath(0);
		czasyBrute.push_back(pomiary.getCounter());
		pomiary.startCounting();
		branch.calculatingPath(0);
		czasyBranch.push_back(pomiary.getCounter());
		cout << N << " - Wielkosc    " << i << " - Zrobione" << endl;
	}
	pomiary.saveToFile(czasyBrute, "bruteForce8.txt");
	pomiary.saveToFile(czasyBranch, "branchAndBound8.txt");
	czasyBrute.clear();
	czasyBranch.clear();

	N = 9;
	for (int i = 0; i < 100; i++)
	{
		BruteForce brute;
		BranchAndBound branch;
		generacjaDanych(N);
		graf.createGiven("daneDoTestow.txt");
		brute.setGraph(graf);
		branch.setGraph(graf);
		pomiary.startCounting();
		brute.calculatingPath(0);
		czasyBrute.push_back(pomiary.getCounter());
		pomiary.startCounting();
		branch.calculatingPath(0);
		czasyBranch.push_back(pomiary.getCounter());
		cout << N << " - Wielkosc    " << i << " - Zrobione" << endl;
	}
	pomiary.saveToFile(czasyBrute, "bruteForce9.txt");
	pomiary.saveToFile(czasyBranch, "branchAndBound9.txt");
	czasyBrute.clear();
	czasyBranch.clear();

	N = 10;
	for (int i = 0; i < 100; i++)
	{
		BruteForce brute;
		BranchAndBound branch;
		generacjaDanych(N);
		graf.createGiven("daneDoTestow.txt");
		brute.setGraph(graf);
		branch.setGraph(graf);
		pomiary.startCounting();
		brute.calculatingPath(0);
		czasyBrute.push_back(pomiary.getCounter());
		pomiary.startCounting();
		branch.calculatingPath(0);
		czasyBranch.push_back(pomiary.getCounter());
		cout << N << " - Wielkosc    " << i << " - Zrobione" << endl;
	}
	pomiary.saveToFile(czasyBrute, "bruteForce10.txt");
	pomiary.saveToFile(czasyBranch, "branchAndBound10.txt");
	czasyBrute.clear();
	czasyBranch.clear();

	N = 11;
	for (int i = 0; i < 100; i++)
	{
		BruteForce brute;
		BranchAndBound branch;
		generacjaDanych(N);
		graf.createGiven("daneDoTestow.txt");
		brute.setGraph(graf);
		branch.setGraph(graf);
		pomiary.startCounting();
		brute.calculatingPath(0);
		czasyBrute.push_back(pomiary.getCounter());
		pomiary.startCounting();
		branch.calculatingPath(0);
		czasyBranch.push_back(pomiary.getCounter());
		cout << N << " - Wielkosc    " << i << " - Zrobione" << endl;
	}
	pomiary.saveToFile(czasyBrute, "bruteForce11.txt");
	pomiary.saveToFile(czasyBranch, "branchAndBound11.txt");
	czasyBrute.clear();
	czasyBranch.clear();

	N = 12;
	for (int i = 0; i < 100; i++)
	{
		BruteForce brute;
		BranchAndBound branch;
		generacjaDanych(N);
		graf.createGiven("daneDoTestow.txt");
		brute.setGraph(graf);
		branch.setGraph(graf);
		pomiary.startCounting();
		brute.calculatingPath(0);
		czasyBrute.push_back(pomiary.getCounter());
		pomiary.startCounting();
		branch.calculatingPath(0);
		czasyBranch.push_back(pomiary.getCounter());
		cout << N << " - Wielkosc    " << i << " - Zrobione" << endl;
	}
	pomiary.saveToFile(czasyBrute, "bruteForce12.txt");
	pomiary.saveToFile(czasyBranch, "branchAndBound12.txt");
	czasyBrute.clear();
	czasyBranch.clear();

	cout << "Wszystkie testy wykonane kapitanie! Powodzonka ze sprawozdaniem! :D" << endl;
	cin.get();
	cin.get();*/
	exit(EXIT_SUCCESS);
}

/*
void generacjaDanych(int N)
{
	fstream plik;
	plik.open("daneDoTestow.txt", ios::out | ios::trunc);
	if (plik.is_open())
	{
		plik << N << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				plik << rand() % 100 + 1 << " ";
			}
			plik << endl;
		}
		plik.close();
	}
}*/