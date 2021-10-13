#include "Stats.h"
#include <iomanip>
using namespace std;

//Stats constructor
Stats::Stats(void)
{
    InitalizeStats();
}

//Stats arg constructor
Stats::Stats(float health, float armor, float damage)
    :mMaxHealth(health), mCurrentHealth(health), mArmor(armor), mDamage(damage)
{
}

//Stats destructor
Stats::~Stats()
{
}

//Stats copy constructor
Stats::Stats(const Stats& obj)
{
    *this = obj;
}

//Overloaded = operator
Stats& Stats::operator=(const Stats& obj)
{
    mMaxHealth = obj.mMaxHealth;
    mCurrentHealth = obj.mCurrentHealth;
    mArmor = obj.mArmor;
    mDamage = obj.mDamage;
    return *this;
}

//Overloaded == 
bool Stats::operator==(const Stats& obj) const
{
    return (mCurrentHealth == obj.mCurrentHealth && mMaxHealth == obj.mMaxHealth && 
        mArmor == obj.mArmor && mDamage == obj.mDamage);
}

//Sets the stats to a default 0 value
void Stats::InitalizeStats()
{
    mCurrentHealth = 0.0f;
    mMaxHealth = 0.0f;
    mArmor = 0.0f;
    mDamage = 0.0f;
}

//Adjusts a stat by the flat amount that is passed in
float Stats::AdjustStatFlat(float amount, string& stat)
{
    if (stat == "Current Health")
    {
        amount = roundf(amount * 100) / 100;
        mCurrentHealth += amount;

        if (mCurrentHealth > mMaxHealth)
            mCurrentHealth = mMaxHealth;
        if (mCurrentHealth < 0)
            mCurrentHealth = 0.0f;
        return amount;
    }
    else if (stat == "Max Health")
    {
        amount = roundf(amount * 100) / 100;
        mMaxHealth += amount;

        if (mMaxHealth < 0)
            mMaxHealth = 0.0f;
        return amount;
    }
    else if (stat == "Health")
    {
        amount = roundf(amount * 100) / 100;
        mCurrentHealth += amount;
        mMaxHealth += amount;

        if (mCurrentHealth < 0)
            mCurrentHealth = 0.0f;
        if (mMaxHealth < 0)
            mMaxHealth = 0.0f;
        return amount;
    }
    else if (stat == "Damage")
    {
        amount = roundf(amount * 100) / 100;
        mDamage += amount;
        return amount;
    }
    else if (stat == "Armor")
    {
        amount = roundf(amount * 100) / 100;
        mArmor += amount;
        return amount;
    }
    else
        return -1;
}

//Helper function to adjust the amount of flat stat that should be given
float Stats::AdjustStatFlat(float amount, const char stat[])
{
    string s = stat;
    return AdjustStatFlat(amount,s);
}

//Adjusts a stat by the percent amount that is passed in
float Stats::AdjustStatPercent(float percent, string& stat)
{
    float adjusted = 0;
    if (stat == "Current Health")
    {
        adjusted = mCurrentHealth * percent;
        mCurrentHealth += adjusted;
        if (mCurrentHealth < 0)
            mCurrentHealth == 0.0f;
        return adjusted;
    }
    else if (stat == "Max Health")
    {
        adjusted = mMaxHealth * percent;
        mMaxHealth += adjusted;

        if (mMaxHealth < 0)
            mMaxHealth = 0.0f;
        if (mMaxHealth < mCurrentHealth)
            mMaxHealth = mCurrentHealth;
        return adjusted;
    }
    else if (stat == "Health")
    {
        adjusted = mMaxHealth * percent;
        mCurrentHealth += adjusted;
        mMaxHealth += adjusted;

        if (mCurrentHealth < 0)
            mCurrentHealth = 0.0f;
        if (mMaxHealth < 0)
            mMaxHealth = 0.0f;
        return adjusted;
    }
    else if (stat == "Damage")
    {
        adjusted = mDamage * percent;
        mDamage += adjusted;
        return adjusted;
    }
    else if (stat == "Armor")
    {
        adjusted = mArmor * percent;
        mArmor += adjusted;
        return adjusted;
    }
    else
        return -1;
}

//Helper function to adjust the amount of flat stat that should be given
float Stats::AdjustStatPercent(float amount, const char stat[])
{
    string s = stat;
    return AdjustStatPercent(amount,s);
}

//Displays the stats of that is apart of the class. Also display stat values that are passed in
//as arguments
int Stats::DisplayBattle(float damage, float armor, float currentHealth, float maxHealth)
{
    cout << left << setw(20) << mDamage << left << setw(30) << "Damage" << left << setw(20) << damage << endl;
    cout << left << setw(20) << mArmor << left << setw(30) << "Armor" << left << setw(20) << armor << endl;
    cout << mCurrentHealth << "/" << mMaxHealth << right << setw(19) << "Health" << right << setw(27) << currentHealth << "/" << maxHealth << endl;
    return 1;
}

//Checks if the current health is below a certain percentage of the max health.
//Returns true if it is, false if it is not
bool Stats::HealthBelowPercent(float percent)
{
    float currentHealthPercent = mCurrentHealth / mMaxHealth;
    if (currentHealthPercent <= percent)
        return true;
    return false;
}

//Sets the current health to the max health
void Stats::SetCurrentHealthToMax()
{
    mCurrentHealth = mMaxHealth;
}

//Returns the max health
float Stats::GetMaxHealth(void)
{
    return mMaxHealth;
}

//Returns the current health
float Stats::GetCurrentHealth(void)
{
    return mCurrentHealth;
}

//Returns the armor
float Stats::GetArmor(void)
{
    return mArmor;
}

//Returns the damage
float Stats::GetDamage(void)
{
    return mDamage;
}

//Displays the damage, health, and armor
void Stats::Display(void)
{
    cout << "Damage: " << mDamage << endl;
    cout << "Health: " << mCurrentHealth << "/" << mMaxHealth << endl;
    cout << "Armor: " << mArmor << endl;
}

//Checks if the current health is above 0.0f.
//Returns true if it is, false if it is not
bool Stats::IsAlive()
{
    return mCurrentHealth >0.0f;
}