//NAME:Carson Hansen
//FILE NAME:Monster.h
//PURPOSE:Define the various monster classes
#pragma once
#include"DLL.h"
#include"Ability.h"
#include"Stats.h"
#include<string.h>
using std::string;

class Ability;
class DLLArray;

class Monster
{
public:
	Monster& operator = (const Monster& obj);
	bool operator !=(const Monster& obj)const;
	bool operator == (const Monster& obj)const;
	Monster(void);
	Monster(string& name, string& monsterType, float health, float armor, float damage, int level, int gold);
	Monster(string& name, string& monsterType, float health, float armor, float damage, int level);
	Monster(const char name[], const char monsterType[], float health, float armor, float damage, int level);
	Monster(const Monster& obj);
	virtual ~Monster(void);
	int display(void);
	int displayName(void);
	int displayActiveAbilities(void);
	float useAbility(Monster& toAttack);
	float useRandomAbility(Monster& toAttack);
	int addAbility(Ability& toAdd);
	bool isAlive(void);
	int displayBattle(Monster& attacking);
	int removeGold(int gold);
	void SetCurrentHealthToMax(void);
	int rollStats(void);
	int copyStats(const Monster& toCopy);
	int levelUp(void);
	float AdjustStatFlat(float amount, string& stat);
	float AdjustStatFlat(float amount, const char[]);
	float AdjustStatPercent(float percent, string& stat);
	float AdjustStatPercent(float percent, const char[]);
	int RemovePassiveEffects(void);
	bool HealthBelowPercent(float percent);

	//getters
	float GetMaxHealth(void);
	float GetCurrentHealth(void);
	float GetArmor(void);
	float GetDamage(void);
	string& GetName(void);
	int GetLevel(void);

protected:
	virtual int intializeAbilities(void);
	string mName;
	string mMonsterType;
	Stats mStats;
	int mGold;
	int mLevel;
	DLLArray* mAbilities;
};

class Vampire : public Monster
{
public:
	Vampire(void);
	Vampire(string& name);
	Vampire(string& name, string& monsterType, float health, float armor, float damage, int level);
	Vampire(const char name[], const char monsterType[], float health, float armor, float damage, int level);
	~Vampire(void);
private:
	int intializeAbilities(void);
};

class Treant : public Monster
{
public:
	Treant(void);
	Treant(string& name);
	Treant(string& name, string& monsterType, float health, float armor, float damage, int level);
	Treant(const char name[], const char monsterType[], float health, float armor, float damage, int level);
	~Treant(void);
private:
	int intializeAbilities(void);
};

class Werewolf : public Monster
{
public:
	Werewolf(void);
	Werewolf(string& name);
	Werewolf(string& name, string& monsterType, float health, float armor, float damage, int level);
	Werewolf(const char name[], const char monsterType[], float health, float armor, float damage, int level);
	~Werewolf(void);
private:
	int intializeAbilities();
};

class Undead : public Monster
{
public:
	Undead(void);
	Undead(string& name);
	Undead(string& name, string& monsterType, float health, float armor, float damage, int level);
	Undead(const char name[], const char monsterType[], float health, float armor, float damage, int level);
	~Undead(void);
private:
	int intializeAbilities();
};