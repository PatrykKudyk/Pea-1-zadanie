#include "Heap.h"
#include <iostream>


using namespace std;

void Heap::push(int val)
{
	int *pom = new int[size + 1];
	for (int i = 0; i < size; i++)
		pom[i] = arr[i];

	if (size == 0)
		delete arr;
	else
		delete[] arr;
	arr = pom;

	int i = size;
	int j = (i - 1) / 2;
	while (i > 0 && arr[j] < val)
	{
		arr[i] = arr[j];
		i = j;
		j = (i - 1) / 2;
	}
	arr[i] = val;
	size++;
}

void Heap::pop()
{
	if (size == 1)
	{
		int *pom = new int;
		delete[] arr;
		arr = pom;
		size = 0;
	}
	else
	{
		arr[0] = arr[size - 1]; // ustawiam wartosc pierwszego elementu na wartosc ostatniego
		int *pom = new int[size - 1];
		for (int i = 0; i < size - 1; i++)
			pom[i] = arr[i];
		delete[] arr;
		arr = pom;
		size--;
	}

	if (size - 1)
	{
		int v = arr[0];
		int i = 0, j = 1;
		while (j < size)
		{
			if (j + 1 < size && arr[j + 1] > arr[j])
				j++;
			if (v >= arr[j])
				break;
			arr[i] = arr[j];
			i = j;
			j = 2 * j + 1;
		}
		arr[i] = v;
	}
	system("cls");
}

bool Heap::isEmpty()
{
	if (size == 0)
		return true;
	
	return false;
}

int Heap::getRoot()
{
	return arr[0];
}

void Heap::clearHeap()
{
	if (size > 0)
	{
		delete[] arr;
		arr = nullptr;
		size = 0;
	}
	else
		return;
}

Heap::Heap()
{
}

Heap::~Heap()
{
	clearHeap();
}
