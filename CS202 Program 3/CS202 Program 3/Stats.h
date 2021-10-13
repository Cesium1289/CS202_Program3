#pragma once
#include<iostream>
#include<string.h>
using std::string;

class Stats
{
public:
	Stats& operator = (const Stats& obj);
	bool operator ==(const Stats& obj)const;
	Stats(void);
	Stats(float health, float armor, float damage);
	~Stats(void);
	Stats(const Stats& obj);
	float AdjustStatFlat(float amount, string& stat);
	float AdjustStatFlat(float amount, const char stat[]);
	float AdjustStatPercent(float amount, string& stat);
	float AdjustStatPercent(float amount, const char stat[]);
	int DisplayBattle(float damage, float armor, float currentHealth, float maxHealth);
	bool HealthBelowPercent(float percent);
	void SetCurrentHealthToMax();
	void Display(void);
	bool IsAlive(void);

	//getters
	float GetMaxHealth(void);
	float GetCurrentHealth(void);
	float GetArmor(void);
	float GetDamage(void);

private:
	void InitalizeStats(void);
	float mCurrentHealth;
	float mMaxHealth;
	float mDamage;
	float mArmor;
};

