//NAME:Carson Hansen
//PURPOSE:Hold all of the functions for the BST
//FILE NAME: BST.cpp
#include "BST.h"
#include<string.h>
#include<iostream>
using namespace std;

//BST constrcutor
BST::BST()
	:mRoot(nullptr)
{
}

//BST destructor
BST::~BST()
{
	DestroyTree(mRoot);
}

//Wrapper function to destroy the tree
int BST::DestroyTree()
{
	if (!mRoot)
		return 0;
	return DestroyTree(mRoot);
}

//Recursive function to delete all of the nodes in the tree. Returns the number of nodes removed
int BST::DestroyTree(Node*& mRoot)
{
	int removed = 0;
	if (mRoot)
	{
		removed += DestroyTree(mRoot->mLeft);
		removed += DestroyTree(mRoot->mRight);

		if (mRoot->mData)
			delete mRoot->mData;
		if (mRoot)
			delete mRoot;

		mRoot = nullptr;
		++removed;
	}

	return removed;
}

//Wrapper function to get a monster by its level.
//Returns the montser by pointer if it was found, nullptr if it was not
Monster* BST::GetByLevel(int level)
{
	return GetByLevel(mRoot, level);
}

//Recursive function to get a monster by its level
//Returns the monster if one was found, nullptr if it was not
Monster* BST::GetByLevel(Node*& mRoot, int level)
{
	if (!mRoot)
		return nullptr;
	if (mRoot->mData->GetLevel() == level)
		return mRoot->mData;
	GetByLevel(mRoot->mLeft, level);
	if (mRoot->mData->GetLevel() == level)
		return mRoot->mData;
	GetByLevel(mRoot->mRight, level);
}

//Wrapper function to return the height of the tree.
//Return 0 if the tree is empty.
int BST::GetHeight()
{
	if (!mRoot)
		return 0;
	return GetHeight(mRoot);
}

//Recursivly returns the height of the tree 
int BST::GetHeight(Node* mRoot)
{
	int leftHeight = 0;
	int rightHeight = 0;
	if (!mRoot)
		return 0;
	else
	{
		leftHeight = GetHeight(mRoot->mLeft) + 1;
		rightHeight = GetHeight(mRoot->mRight) + 1;
	}

	if (leftHeight > rightHeight)
		return leftHeight;
	else
		return rightHeight;
}

//Check if the BST is empty. Returns true if root is null,
//false if head is not null.
bool BST::IsEmpty()
{
	if (mRoot)
		return false;
	return true;
}

//Wrapper function to get a monster by its name.
//Returns the monster if it was found, null if it was not
Monster* BST::Get(string& toFind)
{
	if(!mRoot)
		return nullptr;
	if (mRoot->mData->GetName() == toFind)
		return mRoot->mData;
	else if (mRoot->mData->GetName() < toFind)
		return Get(mRoot->mRight, toFind);
	else
		return Get(mRoot->mLeft, toFind);
}

//Recurssive function to find a monster by its name.
//Returns the monster by pointer if it was found, null if it was not
Monster* BST::Get(Node*& mRoot, string& toFind)
{
	if (!mRoot)
		return nullptr;
	if (mRoot->mData->GetName() == toFind)
		return mRoot->mData;
	else if (mRoot->mData->GetName() < toFind)
		return Get(mRoot->mRight, toFind);
	else
		return Get(mRoot->mLeft, toFind);
}

//Wrapper function that checks to see if a string type existes in the tree
//If it is in the tree it will return true, otherwise will return false
bool BST::IsInTree(string& toFind)
{
	if (!mRoot)
		return false;
	if (mRoot->mData->GetName() == toFind)
		return mRoot->mData;
	else if (mRoot->mData->GetName() < toFind)
		return Get(mRoot->mRight, toFind);
	else
		return Get(mRoot->mLeft, toFind);
}

//Recursive function to see it a monster is in the tree by checking its name.
//Returns true if a monster in the tree has the same name, false if it does not
bool BST::IsInTree(Node* mRoot, string& toFind)
{
	if (!mRoot)
		return false;
	if (mRoot->mData->GetName() == toFind)
		return true;
	else if (mRoot->mData->GetName() < toFind)
		return Get(mRoot->mRight, toFind);
	else
		return Get(mRoot->mLeft, toFind);
}

//Wrapper function to get the data the user wants to add.
//Returns 1 when the data is added
int BST::Add(Monster& toAdd)
{
	return Add(mRoot,toAdd);
}

//Recursive function to add a monster to the bst.
int BST::Add(Node*& mRoot, Monster& toAdd)
{
	if (!mRoot)
	{
		//check what kind of monster is being added
		Monster* newMonster;
		Vampire* vamp = dynamic_cast<Vampire*>(&toAdd);
		Werewolf* were = dynamic_cast<Werewolf*>(&toAdd);
		Undead* undead = dynamic_cast<Undead*>(&toAdd);
		Treant* treant = dynamic_cast<Treant*>(&toAdd);

		if (vamp)
			newMonster = new Vampire(*vamp);
		else if (were)
			newMonster = new Werewolf(*were);
		else if (undead)
			newMonster = new Undead(*undead);
		else if (treant)
			newMonster = new Treant(*treant);
		else
			return 0;

		mRoot = new Node();
		mRoot->mData = newMonster;
		*mRoot->mData = toAdd;
		mRoot->mRight = nullptr;
		mRoot->mLeft = nullptr;
		
		return 1;
	}

	if (mRoot->mData->GetName() < toAdd.GetName())
		Add(mRoot->mRight, toAdd);
	else
		Add(mRoot->mLeft, toAdd); 

	return 1;
}

//Wrapper function to remove all songs by artist name
//based on the char* passed in as an argument.
//Returns the number of songs removed
int BST::Remove(string& toRemove)
{
	if (!mRoot)
		return 0;
	else
		return Remove(mRoot, toRemove);
}

//Recursive function to remove a monster by the name.
//Returns the 1 if a monster was removed, 0 if it was not
int BST::Remove(Node*& mRoot, string& toRemove)
{
	int removed = 0;
	if (!mRoot)
		return removed;

	if (mRoot->mData->GetName() == toRemove)
	{
		if (!mRoot->mLeft && !mRoot->mRight)
		{
			if(mRoot->mData)
				delete mRoot->mData;
			if(mRoot)
				delete mRoot;
			mRoot = nullptr;
			++removed;
		}
		else if (mRoot->mRight && !mRoot->mLeft)
		{
			if(mRoot->mData)
				delete mRoot->mData;
			Node* temp = mRoot->mRight;
			if(mRoot)
				delete mRoot;
			mRoot = nullptr;
			mRoot = temp;
			++removed;
		}
		else if (mRoot->mLeft && !mRoot->mRight)
		{
			Node* temp = mRoot->mLeft;
			if(mRoot->mData)
				delete mRoot->mData;
			if(mRoot)
				delete mRoot;
			mRoot = nullptr;
			mRoot = temp;
			++removed;
		}
		else
		{
			Node* current = mRoot->mRight;
			if (!current->mLeft)
			{
				mRoot->mData = current->mData;
				Node* temp = current->mRight;
				mRoot->mRight = temp;
				if(current->mData)
					delete current->mData;
				if(current)
					delete current;
				current = nullptr;
				++removed;
			}
			else
			{
				Node* parent = current;

				while (current->mLeft)
				{
					parent = current;
					current = current->mLeft;
				}

				mRoot->mData = current->mData;
				Node* temp = current->mRight;
				parent->mLeft = temp;
				if(current->mData)
					delete current->mData;
				if(current)
					delete current;
				current = nullptr;
				++removed;
			}
		}
		return removed;
	}
	else if (mRoot->mData->GetName() < toRemove)
		removed += Remove(mRoot->mRight, toRemove);
	else
		removed += Remove(mRoot->mLeft, toRemove);
	return removed;
}

//Wrapper function to display all data in the tree.
//Return 0 if the tree is empty, or the number of monsters
//that were displayed
int BST::Display()
{
	if (!mRoot)
		return 0;
	return Display(mRoot);
}

//Recursive display all data that is in the tree. Return the number of
//nodes displayed
int BST::Display(Node* mRoot)
{
	int total = 0;
	if (!mRoot)
		return 0;
	else
		++total;

	total += Display(mRoot->mLeft);
	mRoot->mData->display();
	total += Display(mRoot->mRight);

	return total;
}