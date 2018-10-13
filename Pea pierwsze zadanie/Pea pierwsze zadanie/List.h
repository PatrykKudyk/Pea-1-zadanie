#pragma once

struct Node
{
	Node *next;
	int data;
};

class List
{
	int size;
	Node *head;
public:
	void push(int data);
	void pull();
	void clearList();
	Node* getHead();
	List();
	~List();
};