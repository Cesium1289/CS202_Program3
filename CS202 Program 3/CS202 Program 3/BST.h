//NAME: Carson Hansen
//PURPOSE: Define a BST
//FILE NAME: BST.h
#include "Monster.h"
#include<string.h>

class BST
{
public:
	BST(void);
	~BST(void);
	int DestroyTree(void);
	int Add(Monster& toAdd);
	int Display(void);
	int Remove(string& toRemove);
	int GetHeight(void);
	bool IsEmpty(void);
	Monster* Get(string& toFind);
	bool IsInTree(string& toFind);
	Monster* GetByLevel(int level);
	
private:

	struct  Node
	{
		Node* mRight;
		Node* mLeft;
		Monster* mData;
	};
	Node* mRoot;

	//functions
	Monster* GetByLevel(Node*& mRoot, int level);
	int DestroyTree(Node* &mRoot);
	Monster* Get(Node*& mRoot, string& toFind);
	int Remove(Node*& mRoot, string& toRemove);
	int Add(Node*& mRoot, Monster& toAdd);
	int Display(Node* mRoot);
	int GetHeight(Node* mRoot);
	bool IsInTree(Node* mRoot, string& toFind);
};

