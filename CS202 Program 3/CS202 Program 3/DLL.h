//NAME: Carson Hansen
//FILE NAME: DLL.h
//PURPOSE: Define the DLL and DLL array. These will store the monsters abilities
#pragma once
#include"Ability.h"
#include<string>

class PassiveAbility;
class Monster;
class Ability;
class DLL
{
public:
	DLL(void);
	~DLL(void);
	DLL& operator = (const DLL& obj);
	int Add(Ability& toAdd, Monster& monster);
	int Display(void);
	int Count(void);
	int DisplayNumbered(void);
	int Destroy(void);
	bool IsEmpty(void);
	Ability* GetIndex(int index);
	int Copy(DLL& source);
	int RemovePassiveEffects(Monster& monster);
private:
	int RemovePassiveEffects(PassiveAbility*& mHead, Monster& monster);
	bool IsTheSame(Ability* mHead, Ability* toCompare);
	int Copy(Ability* mHead, Ability*& dest, Ability*& prev);
	int DisplayNumbered(Ability* mHead, int index);
	int Count(Ability* mHead);
	Ability* GetIndex(Ability* mHead, int index, int currentIndex);
	int Display(Ability* mHead);
	int Destroy(Ability*& mHead);
	Ability* mHead;
};

class DLLArray
{
public:
	DLLArray& operator = (const DLLArray& obj);
	DLLArray(void);
	~DLLArray(void);
	int Add(Ability& toAdd, Monster& monster);
	int Display(void);
	int DisplayActiveByNumber(void);
	int Copy(DLLArray& source);
	Ability* GetActiveAbility(int index);
	Ability* GetPassiveAbility(int index);
	int Count(void);
	int Destroy(void);
	int DisplayActiveAbilities(void);
	int RemovePassiveEffects(Monster& monster);
private:
	int DisplayActiveAbilities(DLL** mHead);
	int Destroy(DLL**& mHead, int& index);
	int Copy(DLL** source, DLL**& dest, int index);
	int Count(DLL** mHead);
	int DisplayActiveByNumber(DLL** mHead);
	int Display(DLL** mHead, int index);
	DLL** mHead;
};