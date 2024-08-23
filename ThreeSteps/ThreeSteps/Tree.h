#pragma once
#include <iostream>
#define SIZE 100
class Tree
{
public:

	Tree();

	~Tree();

	void addNode(int newNodeNumber, int parentNodeNumber);

	void setRoot(int number);

	void print();
	void printThreeSteps(int num);
	void addConnect(int v1, int v2);

	void delNode(int nodeNumber);
private:
	struct Node;

	Node* getNodeByNumber(int number, Node* current);
	void printInner(Node* current);
	void printThreeStepsInner(Node* current);

	struct Node
	{
		Node(int _number, Node* _parent = 0) : number(_number), parent(_parent), childCount(0), parentsCount(0)
		{}

		~Node()
		{
			for (int i = 0; i < childCount; ++i)
			{
				if (children[i] != nullptr)
				{
					delete children[i];
					children[i] = nullptr;
				}
			}
		}

		void addChild(Node* newChild)
		{
			children[childCount++] = newChild;
		}


		void addParent(Node* newParent)
		{
			parents[parentsCount++] = newParent;
		}


		void delChild(Node* child);

		int number;
		Node* children[SIZE];
		int childCount;

		Node* parent;

		Node* parents[2 * SIZE];
		int parentsCount;

	};


	Node* root;
};