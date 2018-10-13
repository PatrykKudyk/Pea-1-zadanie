#include "List.h"
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

void List::push(int data)
{
	Node *p = new Node;
	p->data = data;
	if(head)
		p->next = head;
	else
		p->next = nullptr;
	head = p;
	size++;
}

void List::pull()
{
	if(head != nullptr)
	{
		Node *p = new Node;
		p = head;
		if (p->next != nullptr)
		{
			head = p->next;
			delete p;
		}
		size--;
	}
}

void List::clearList()
{
	Node *p = head;

	while (p)
	{
		Node *next = p->next;
		free(p);
		p = next;
	}
	size = 0;
	head = nullptr;
}

Node* List::getHead()
{
	return head;
}

int List::getSize()
{
	return size;
}

List::List()
{
	head = nullptr;
	size = 0;
}

List::~List()
{
	clearList();
}
