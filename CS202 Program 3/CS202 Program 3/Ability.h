//NAME: Carson Hansen
//FILE NAME: Abilitiy.h
//PURPOSE: Define the various ability classes the monsters will have
#pragma once
#include"Monster.h"
#include<string>
class Monster;
using std::string;

class Ability
{
public:
	bool operator == (const Ability& obj);
	Ability(void);
	Ability(const Ability& obj);
	virtual ~Ability(void);
	int display(void);
	int displayName(void);
	virtual float UseAbility(Monster& attacker, Monster& beingAttacked);
	bool sameAbilityId(Ability& toCompare);
	bool sameAbilityId(int id);
	void setNext(Ability* next);
	void setPreviuos(Ability* prev);
	Ability*& getNext(void);
	Ability*& getPrevious(void);
protected:
	Ability* mNext;
	Ability* mPrevious;
	string mAbilityName;
	string mDescription;
	int mID;
};

class PassiveAbility : public Ability
{
public:
	PassiveAbility(void);
	virtual ~PassiveAbility(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
	virtual float UseAbility(Monster& monster);
	void RemovePassiveEffect(Monster& monster);
protected:
	float mArmorPercentChanged;
	float mHealthPercentChanged;
	float mDamagePercenChanged;
	float mAmountOfArmorGiven;
	float mAmountOfHealthGiven;
	float mAmountOfDamageGiven;
};

class ActiveAbility : public Ability
{
public:
	ActiveAbility(void);
	virtual ~ActiveAbility(void);
	virtual float UseAbility(Monster& attacker, Monster& beingAttacked);
protected:
	float DealDamage(Monster& attacker, Monster& beingAttacked);
	float mHealthPercentageThresholdToUse;
	float mArmorPercentageIgnored;
	float mHealUserPercentOfDamage;
	float mReduceUserHealthByDamagepercent;
	float mDamageMod;
};

class InspiringPresence : public PassiveAbility
{
public:
	InspiringPresence(void);
	~InspiringPresence(void);
	float UseAbility(Monster& toBuff);
};

class FortifiedBark : public PassiveAbility
{
public:
	FortifiedBark(void);
	~FortifiedBark(void);
	float UseAbility(Monster& toBuff);
private:
};

class SoothingDarkness : public PassiveAbility
{
public:
	SoothingDarkness(void);
	~SoothingDarkness(void);
	float UseAbility(Monster& toBuff);
};

class BloodFrenzy : public PassiveAbility
{
public:
	BloodFrenzy(void);
	~BloodFrenzy(void);
	float UseAbility(Monster& toBuff);
};

class CrushedArmor : public PassiveAbility
{
public: 
	CrushedArmor(void);
	~CrushedArmor(void);
	float UseAbility(Monster& toBuff);
};

class Rage : public PassiveAbility
{
public:
	Rage(void);
	~Rage(void);
	float UseAbility(Monster& toBuff);
};

class ShreddedArmor : public PassiveAbility
{
public:
	ShreddedArmor(void);
	~ShreddedArmor(void);
	float UseAbility(Monster& toBuff);
};

class Demoralized : public PassiveAbility
{
public:
	Demoralized(void);
	~Demoralized(void);
	float UseAbility(Monster& toBuff);
};

class MeleeAttack : public ActiveAbility
{
public:
	MeleeAttack(void);
	~MeleeAttack(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
private:

};

class FeralFrenzy : public ActiveAbility
{
public:
	FeralFrenzy(void);
	~FeralFrenzy(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
};

class ChargingBash : public ActiveAbility
{
public:
	ChargingBash(void);
	~ChargingBash(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
};

class SoulShatter : public ActiveAbility
{
public:
	SoulShatter(void);
	~SoulShatter(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
private:

};

class DrainEssence : public ActiveAbility
{
public:
	DrainEssence(void);
	~DrainEssence(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
private:

};

class DeathsCaress : public ActiveAbility
{
public:
	DeathsCaress(void);
	~DeathsCaress(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
private:

};

class InfectiousBite : public ActiveAbility
{
public:
	InfectiousBite(void);
	~InfectiousBite(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
};

class ConcussiveBlow : public ActiveAbility
{
public:
	ConcussiveBlow(void);
	~ConcussiveBlow(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
};

class CrushArmor : public ActiveAbility
{
public:
	CrushArmor(void);
	~CrushArmor(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
};

class SacrificeLimb : public ActiveAbility
{
public:
	SacrificeLimb(void);
	~SacrificeLimb(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
};

class Berserk : public ActiveAbility
{
public:
	Berserk(void);
	~Berserk(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
};

class ShreddingSwipe : public ActiveAbility
{
public:
	ShreddingSwipe(void);
	~ShreddingSwipe(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
};

class Stomp : public ActiveAbility
{
public:
	Stomp(void);
	~Stomp(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
};

class EntanglingRoots : public ActiveAbility
{
public:
	EntanglingRoots(void);
	~EntanglingRoots(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
};

class DreadfulRoar : public ActiveAbility
{
public:
	DreadfulRoar(void);
	~DreadfulRoar(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
};

class Slam : public ActiveAbility
{
public:
	Slam(void);
	~Slam(void);
	float UseAbility(Monster& attacker, Monster& beingAttacked);
};





