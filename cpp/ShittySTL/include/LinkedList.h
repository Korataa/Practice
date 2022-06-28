#pragma once

#include <iostream>

class Node
{
public:
	int data;
	Node* next;
	Node()
	{
		data = 0;
		next = nullptr;
	}
	Node(int data) : data(data), next(nullptr) { }
};

class LinkedList
{
public:
	LinkedList()
	{
		head = nullptr;
		size = 0;
	}

	~LinkedList()
	{
		Node* last = head;
		while (last->next != nullptr)
		{
			Node* temp = last;
			last = last->next;
			delete temp;

		}

		size = 0;
	}

	//insert a new node at the fornt of linked list
	void prepend(int newData)
	{
		Node* newNode = new Node(newData);
		newNode->next = head;
		head = newNode;
		
		size++;
	}

	//inserts new data after prevNode
	void insertAfter(Node* prevNode, int newData)
	{
		if (!prevNode)
		{
			std::cout << "node is null or messed up somehow: " << std::endl;
			return;
		}

		Node* newNode = new Node(newData);
		newNode->next = prevNode->next;
		prevNode->next = newNode;

		size++;
	}

	void insertAt(int index, int newData)
	{
		Node* newNode = new Node(newData);
		
		//check if index is 0 and if it is, just call prepend
		if (index == 0)
		{
			prepend(newData);
			return;
		}

		Node* last = head->next;
		int i = 1;
		while (i < index)
		{
			//throw exception if index is out of range, or if something weird happened
			if (!last)
			{
				throw std::out_of_range("index is out of range");
			}

			last = last->next;
			++i;
		}

		newNode->next = last->next;
		last->next = newNode;

		size++;
	}

	//inserts data at the end of the linked list
	void append(int newData)
	{
		Node* newNode = new Node(newData);

		//check if linked list is empty or not
		if (head == nullptr)
		{
			head = newNode;

			size++;
			return;
		}

		//This is going at the end so we can set it to nothing
		newNode->next = nullptr;

		Node* last = head;
		while (last->next != nullptr)
		{
			last = last->next;
		}

		//we are now at the last node, or we should be
		last->next = newNode;

		size++;
		return;
	}

	void printList()
	{
		std::cout << "head-> " << head->data;
		Node* last = head;
		while (last->next != nullptr)
		{
			last = last->next;
			std::cout << " next-> " << last->data;
		}
	}

	int getSize()
	{
		return size;
	}
	
private:
	Node* head;
	int size;
};