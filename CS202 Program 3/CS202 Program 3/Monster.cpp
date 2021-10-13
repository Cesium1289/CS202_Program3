//NAME:Carson Hansen
//FILE NAME:Monster.cpp
//PURPOSE: Implement the functions the monster and its derived classes have
#include "Monster.h"
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<math.h>
#include<iomanip>
#include<cstring>
using namespace std;

//Overloaded = for the monster
Monster& Monster::operator=(const Monster& obj)
{
	if (*this == obj)
		return *this;
	
	if (mAbilities)
	{
		delete mAbilities;
		mAbilities = nullptr;
	}

	mAbilities = new DLLArray();
	*mAbilities = *obj.mAbilities;
	mName = obj.mName;
	mMonsterType = obj.mMonsterType;
	mStats = obj.mStats;
	mGold = obj.mGold;
	mLevel = obj.mLevel;
	return *this;
}

//Overloaded != to compare the name, monster type, gold, and level. Does not comapare the stats since they are floats
bool Monster::operator!=(const Monster& obj) const
{
	return !((mName == obj.mName) && (mMonsterType == obj.mMonsterType)  &&
		(mGold == obj.mGold) && (mLevel == obj.mLevel));
}

//overloaded == to compare the name, monster type, gold, and level. Does not comapare the stats since they are floats
bool Monster::operator==(const Monster& obj) const
{
	//Not checking if stats are the same since they are floats!
	return ((mName == obj.mName) && (mMonsterType == obj.mMonsterType) && (mLevel == obj.mLevel));
}

//Default monster constructor
Monster::Monster(void)
	:mName(""), mMonsterType(""), mLevel(1), mGold(0)
{
	mAbilities = new DLLArray();
	rollStats();
	intializeAbilities();
}

//Arguemented mosnter constructor
Monster::Monster(string& name, string& monsterType, float health, float armor, float damage, int level, int gold)
	:Monster(name, monsterType, health, armor, damage, level)
{
	mGold = gold;
}

//Arguemented mosnter constructor
Monster::Monster(string& name, string& monsterType, float health, float armor, float damage, int level)
	:mLevel(level), mGold(0)
{
	mName = name;
	mMonsterType = monsterType;
	mStats = { health,armor,damage };
	mAbilities = new DLLArray();
	intializeAbilities();
}

//Argumented monster constuctor
Monster::Monster(const char name[], const char monsterType[], float health, float armor, float damage, int level)
{
	mName = name;
	mMonsterType = monsterType;
	mStats = { health,armor,damage };
	mLevel = level;
	mAbilities = new DLLArray();
	intializeAbilities();
}

//Monster copy constructor
Monster::Monster(const Monster& obj)
{
	if (mAbilities)
		delete mAbilities;

	mName = obj.mName;
	mMonsterType = obj.mMonsterType;
	mStats = obj.mStats;
	mLevel = obj.mLevel;
	mGold = obj.mGold;

	mAbilities = new DLLArray();
	mAbilities->Copy(*obj.mAbilities);
}

//Destructor for monster
Monster::~Monster(void)
{
	if (mAbilities)
		delete mAbilities;
	mAbilities = nullptr;
}

//Display all the information about a monster
int Monster::display(void)
{
	cout << "Name: " << mName << endl;
	cout << "Mosnter: " << mMonsterType << endl;
	cout << "Gold: " << mGold << endl;
	cout << "Level: " << mLevel << endl;
	mStats.Display();
	cout << "-_-_-_-_-_-_-\n";
	return 1;
}

//Displays the name of the monster. Returns 1 if successful or 0 if not successful
int Monster::displayName(void)
{
	cout << mName;
	return 1;
}

//Display the active abilities the monster has
//returns the number of abilities it has
int Monster::displayActiveAbilities(void)
{
	if (!mAbilities)
		return 0;
	return mAbilities->DisplayActiveAbilities();
}

//Allow the user to pick an ability to use against a monster
//This will return the damage they dealt
float Monster::useAbility(Monster& toAttack)
{
	int numAbility = 0;
	int abilityToUse = 0;
	float damageDealt = 0;
	Ability* ability;

	cout << "Select an ability to use\n";
	numAbility = mAbilities->DisplayActiveByNumber();

	//check if there are any abilties to use
	if (numAbility == 0)
		return 0;
	cin >> abilityToUse; cin.ignore(256, '\n');

	//validate input
	while (cin.fail() || abilityToUse < 1 || abilityToUse > numAbility)
	{
		cin.clear();
		cout << "Enter a valid ability to use\n";
		cin >> abilityToUse; cin.ignore(256, '\n');
	}

	//reduce the ability to use by one to match the index of where it is located in the ability DLL
	--abilityToUse;

	//get the ability the user wants
	ability = mAbilities->GetActiveAbility(abilityToUse);

	//check if abilty selected is valid
	if (!ability)
		cout << "There was an error getting that ability...\n";
	else
		damageDealt = ability->UseAbility(*this, toAttack);

	return damageDealt;
}

//Used by the enemy monster to randomly pick an ability to use when attacking the player.
//This will return the damage they dealt
float Monster::useRandomAbility(Monster& toAttack)
{
	int numbAbilities = 0;
	int maxRand = 0;
	int abilityToUse;
	float damageDealt =0;
	Ability* ability;

	//set the max rand by checking how many abilities it has
	maxRand = mAbilities->Count();
	abilityToUse = rand() % (maxRand - 1 + 1) + 1;
	--abilityToUse;

	//call the use ability function and pass it the index of the ability as well as the attacker and defender data
	//and set the damageDealt to the damage it returns
	ability = mAbilities->GetActiveAbility(abilityToUse);
	if (!ability)
		cout << "Error getting that ability!\n";
	else
		damageDealt = ability->UseAbility(*this, toAttack);
	
	return damageDealt;
}

//Wrapper function that adds an ability to the monsters ability list
int Monster::addAbility(Ability& toAdd)
{
	return mAbilities->Add(toAdd, *this);
}

//Wrapper function that checks if player is dead. Returns false if player has more than
//0 health false, it it is <0 or =0
bool Monster::isAlive(void)
{
	return mStats.IsAlive();
}

//Displays the player monster and the monster that they are attacking, in a formated way
int Monster::displayBattle(Monster& attacking)
{
	cout << left << setw(20) << mName << left << setw(30) << "Name" << left << setw(20) << attacking.mName << endl;
	cout << left << setw(20) << mMonsterType << left << setw(30) << "Monster" << left << setw(20) << attacking.mMonsterType << endl;

	//call the stats display function
	mStats.DisplayBattle(attacking.GetDamage(), attacking.GetArmor(), attacking.GetCurrentHealth(), attacking.GetMaxHealth());
	cout << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n";
	return 1;
}

//Copy the stats from one monster to another. This is used before combat
//to ensure the stats return to the correct state after combat is over.
int Monster::copyStats(const Monster& toCopy)
{
	mStats = toCopy.mStats;
	return 1;
}

//Remove gold from the user
int Monster::removeGold(int gold)
{
	//check if monster has enough gold to remove
	if (gold>mGold)
		return 0;
	mGold -= gold;
	return mGold;
}

//Returns the level of the monster
int Monster::GetLevel()
{
	return mLevel;
}

//Sets the current health of the monster to its max health.
//This is used after the monster is done with a battle bash
void Monster::SetCurrentHealthToMax()
{
	mStats.SetCurrentHealthToMax();
}

//Returns the name of the monster
string& Monster::GetName()
{
	return mName;
}

//Used to initalize the stats of a monster when it is first created
int Monster::rollStats(void)
{
	int armor = 0;
	int health = 0;
	int damage = 0;
	health = rand() % (500 - 400 + 1) + 400;
	armor = rand() % (100 - 80 + 1) + 80;
	damage = rand() % (90 - 75 + 1) + 75;
	mStats.AdjustStatFlat(static_cast<float>(armor),"Armor");
	mStats.AdjustStatFlat(static_cast<float>(health), "Max Health");
	mStats.AdjustStatFlat(static_cast<float>(health), "Current Health");
	mStats.AdjustStatFlat(static_cast<float>(damage), "Damage");
	return 1;
}

//When a player kills a monster they level up, which will
//increase their stats
int Monster::levelUp(void)
{
	mStats.AdjustStatFlat(10, "Current Health");
	mStats.AdjustStatFlat(10, "Max Health");
	mStats.AdjustStatFlat(10, "Damage");
	mStats.AdjustStatFlat(10, "Armor");
	mGold += mLevel * 75;
	++mLevel;
	return 1;
}

//Wrapper function to adjust a monsters stat by a flat amount.
//Returns the amount the stat was changed
float Monster::AdjustStatFlat(float amount, string& stat)
{
	return mStats.AdjustStatFlat(amount,stat);
}

//Wrapper function to adjust a monsters stat by a flat amount.
//Returns the amount the stat was changed
float Monster::AdjustStatFlat(float amount, const char stat[])
{
	return mStats.AdjustStatFlat(amount,stat);
}

//Wrapper function to adjust a monsters stat by a percent amount.
//Returns the amount the stat was changed
float Monster::AdjustStatPercent(float percent, string& stat)
{
	return mStats.AdjustStatPercent(percent,stat);
}

//Wrapper function to adjust a monsters stat by a percent amount.
//Returns the amount the stat was changed
float Monster::AdjustStatPercent(float percent, const char stat[])
{
	return mStats.AdjustStatPercent(percent,stat);
}

//Wrapper function that removes all the passive effects a monster has
//Used at the end of a battle bash
int Monster::RemovePassiveEffects()
{
	return mAbilities->RemovePassiveEffects(*this);
}

//Checks to see if a monster is below a certain health percentage.
//Will return true if it is below the percent that is passed in as
//an argument
bool Monster::HealthBelowPercent(float percent)
{
	return mStats.HealthBelowPercent(percent);
}

//Returns the max health of the mosnter
float Monster::GetMaxHealth(void)
{
	return mStats.GetMaxHealth();
}

//Returns the current health of the monster
float Monster::GetCurrentHealth(void)
{
	return mStats.GetCurrentHealth();
}

//Returns the amount of armor the monster has
float Monster::GetArmor(void)
{
	return mStats.GetArmor();
}

//Returns the amount of damage the monster has
float Monster::GetDamage(void)
{
	return mStats.GetDamage();
}

//Gives the default monster the melee attack
int Monster::intializeAbilities(void)
{
	MeleeAttack ma;
	mAbilities->Add(ma, *this);
	return 1;
}

//Default vampire constructor
Vampire::Vampire(void)
	:Monster()
{
	intializeAbilities();
}

//Vampire string constructor
Vampire::Vampire(string& name)
	: Monster()
{
	mName =name;
	mMonsterType = "Vampire";
	intializeAbilities();
}

//Vampire args constructor
Vampire::Vampire(string& name, string& monsterType, float health, float armor, float damage, int level)
	: Monster(name, monsterType, health, armor, damage, level)
{
	intializeAbilities();
}

//Vampire args constructor
Vampire::Vampire(const char name[], const char monsterType[], float health, float armor, float damage, int level)
	:Monster(name,monsterType,health,armor,damage,level)
{
	intializeAbilities();
}

//Vampire destructor
Vampire::~Vampire(void)
{
}

//Initalize the vampire abilities
int Vampire::intializeAbilities(void)
{
	SoulShatter ss;
	DrainEssence de;
	DeathsCaress dc;
	mAbilities->Add(ss, *this);
	mAbilities->Add(de, *this);
	mAbilities->Add(dc, *this);
	return 1;
}

//Treant default constructor
Treant::Treant(void)
	:Monster()
{
	intializeAbilities();
}

//Treant const char* constructor
Treant::Treant(string& name)
	: Monster()
{
	mName = name;
	mMonsterType = "Treant";
	intializeAbilities();
}

//Treant arg constructor
Treant::Treant(string& name, string& monsterType, float health, float armor, float damage, int level)
	:Monster(name, monsterType, health, armor, damage, level)
{
	intializeAbilities();
}

//Treant arg constructor
Treant::Treant(const char name[], const char monsterType[], float health, float armor, float damage, int level)
	:Monster(name, monsterType, health, armor, damage, level)
{
	intializeAbilities();
}

//Treant destructor
Treant::~Treant(void)
{
}

//Initalize the treant abilities
int Treant::intializeAbilities(void)
{
	Stomp s;
	EntanglingRoots et;
	DreadfulRoar dr;
	Slam sl;
	mAbilities->Add(s, *this);
	mAbilities->Add(et, *this);
	mAbilities->Add(dr, *this);
	mAbilities->Add(sl, *this);
	return 1;
}

//Werewolf default constructor
Werewolf::Werewolf(void)
	:Monster()
{
	intializeAbilities();
}

//Werewolf const string constructor
Werewolf::Werewolf(string& name)
	: Monster()
{
	mName = name;
	mMonsterType = "Werewolf";
	intializeAbilities();
}

//Werewolf arg constructor
Werewolf::Werewolf(string& name, string& monsterType, float health, float armor, float damage, int level)
	:Monster(name, monsterType, health, armor, damage, level)
{
	intializeAbilities();
}

//Werewolf arg constructor
Werewolf::Werewolf(const char name[], const char monsterType[], float health, float armor, float damage, int level)
	:Monster(name, monsterType, health, armor, damage, level)
{
	intializeAbilities();
}

//Werewolf destructor
Werewolf::~Werewolf(void)
{

}

//Intialize the werewolf abilities
int Werewolf::intializeAbilities(void)
{
	FeralFrenzy ff;
	ChargingBash cb;
	Berserk b;
	ShreddingSwipe ss;
	mAbilities->Add(ff, *this);
	mAbilities->Add(cb, *this);
	mAbilities->Add(b, *this);
	mAbilities->Add(ss, *this);
	return 1;
}

//Undead constructor
Undead::Undead(void)
	:Monster()
{
	intializeAbilities();
}

//Undead string constructor
Undead::Undead(string& name)
	: Monster()
{
	mName = name;
	mMonsterType = "Undead";
	intializeAbilities();
}

//Undead arg constructor
Undead::Undead(string& name, string& monsterType, float health, float armor, float damage, int level)
	: Monster(name, monsterType, health, armor, damage, level)
{
	intializeAbilities();
}

//Undead arg constructor
Undead::Undead(const char name[], const char monsterType[], float health, float armor, float damage, int level)
	: Monster(name, monsterType, health, armor, damage, level)
{
	intializeAbilities();
}

//Undead destructor
Undead::~Undead(void)
{
}

//Intitalize the abilities of an undead monster
int Undead::intializeAbilities(void)
{
	InfectiousBite ib;
	ConcussiveBlow cb;
	CrushArmor ca;
	SacrificeLimb sl;
	mAbilities->Add(ib, *this);
	mAbilities->Add(cb, *this);
	mAbilities->Add(ca, *this);
	mAbilities->Add(sl, *this);
	return 1;
}
