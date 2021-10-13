//NAME:Carson Hansen
//FILE NAME:Ability.cpp
//PURPOSE:Implement and define the various differnt passive and active abilities the monsters have
#include "Ability.h"
#include<iostream>
#include<math.h>
using namespace std;

//Overloaded == for ability
bool Ability::operator==(const Ability& obj)
{
    return (mID == obj.mID);
}

//Default Ability constructor
Ability::Ability(void)
    :mDescription(""), mAbilityName(""), mNext(nullptr), mPrevious(nullptr), mID(0)
{
}

//Ability copy constructor
Ability::Ability(const Ability& obj)
{
    mAbilityName = obj.mAbilityName;
    mDescription = obj.mDescription;
    mNext = obj.mNext;
    mPrevious = obj.mPrevious;
    mID = obj.mID;
}

//Ability destructor
Ability::~Ability(void)
{
}

//Display ability name and description
int Ability::display(void)
{
    cout << "Ability name: " << mAbilityName << endl;
    cout << "Descrption: " << mDescription << endl;
    cout << "Ability ID: " << mID << endl;
    cout << "-_-_-_-_-_-_-_-_-\n";
    return 1;
}

//Display the name of the abilty;
int Ability::displayName(void)
{
    cout << mAbilityName << endl;
    return 1;
}

//Stub of the virutal UseAbility
float Ability::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    return 0.0f;
}

//Check if one ability shares the same id
bool Ability::sameAbilityId(Ability& toCompare)
{
    return this->mID == toCompare.mID;
}

//Compare if the ability id is the same as the int id being passed in
//in as an argument. Return true if they are the same. False if they are not
bool Ability::sameAbilityId(int id)
{
    if (mID == id)
        return true;
    return false;
}

//Sets the next ability to point to
void Ability::setNext(Ability* next)
{
    mNext = next;
}

//Set the previous ability to point to
void Ability::setPreviuos(Ability* prev)
{
    mPrevious = prev;
}

//Returns the next ability
Ability*& Ability::getNext(void)
{
    return mNext;
}

//Returns the previous ability
Ability*& Ability::getPrevious(void)
{
    return mPrevious;
}

//Calculate the amount of damage to deal based on the attackers damage, ability damage modifier
//and the attacker's armor. Returns the amount of damage the ability should deal
float ActiveAbility::DealDamage(Monster& attacker, Monster& beingAttacked)
{
    float damageDone = 0.0f;
    float mitagatedPercentage = 0.0f;
    float damageMitagated = 0.0f;

    float attackerDamage = attacker.GetDamage() * mDamageMod;

    //calculate the amount of armor the target has after apply the % of armor the ability is ignoring
    float beingAttackedArmor = beingAttacked.GetArmor() -  (beingAttacked.GetArmor() * mArmorPercentageIgnored);
    
    //calculate the percentage of damage the target should be taking after using their armor value
    float percentDamageNotMitagated = 100 / (100 + beingAttackedArmor);

    //calculate the damage done by multiplying the attackers damage by the percent of damage that is not mitigated
    damageDone = attackerDamage * percentDamageNotMitagated;

    //round the float to 2 decimal places to show a cleaner number
    damageDone = roundf(damageDone * 100) / 100;

    return damageDone;
}

//Passive ability constructor
PassiveAbility::PassiveAbility(void)
    :mArmorPercentChanged(0.0f), mDamagePercenChanged(0.0f), mHealthPercentChanged(0.0f),mAmountOfArmorGiven(0.0f),mAmountOfDamageGiven(0.0f),mAmountOfHealthGiven(0.0f)
{
}

//Passive abilitity destructor
PassiveAbility::~PassiveAbility(void)
{
}


//Virtual stub of the passiveAbility UseAbility
float PassiveAbility::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    return 0.0f;
}

//Virtual stub of the passiveAbility UseAbility
float PassiveAbility::UseAbility(Monster& monster)
{
    return 0;
}

//Return each monster's stats to their inital value by subtracting
//the amount of each stat that was given by the passive ability
void PassiveAbility::RemovePassiveEffect(Monster& monster)
{
    monster.AdjustStatFlat(-mAmountOfHealthGiven, "Health");
    monster.AdjustStatFlat(-mAmountOfArmorGiven, "Armor");
    monster.AdjustStatFlat(-mAmountOfDamageGiven, "Damage");
}

//Active ability default constructor
ActiveAbility::ActiveAbility(void)
    :mHealthPercentageThresholdToUse(100.0f),mArmorPercentageIgnored(0.0f),mHealUserPercentOfDamage(0.0f),
    mReduceUserHealthByDamagepercent(0.0f),mDamageMod(0.0f)
{
}

//Active ability destructor
ActiveAbility::~ActiveAbility(void)
{
}

//Virtual stub of activeAbility UseAbility
float ActiveAbility::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    return 0.0f;
}

//InspiringPressence constructor
InspiringPresence::InspiringPresence(void)
    :PassiveAbility()
{
    mHealthPercentChanged = .4f;
    mAbilityName = "Inspiring Pressence";
    mDescription = "When fighting in a graveyard, you call upon fallen allies to aid you in combat granting 40% increased health";
    mID = 1;
}

//InspiringPressence destructor
InspiringPresence::~InspiringPresence(void)
{
}

//Implementation of the InspiringPresence UseAbility
float InspiringPresence::UseAbility(Monster& monster)
{
    //set the amount of health given
    mAmountOfHealthGiven = monster.AdjustStatPercent(mHealthPercentChanged, "Health");
    cout << mAbilityName <<" increased " <<  monster.GetName() << "'s health by " << mAmountOfHealthGiven <<"!" << endl;

    return 1;
}

//FortifiedBark default constructor
FortifiedBark::FortifiedBark(void)
    :PassiveAbility()
{
    mHealthPercentChanged = .1f;
    mArmorPercentChanged = .3f;
    mAbilityName = "Fortified Bark";
    mDescription = "When fighing in the forest, your bark thickens granting you 30% increased armor and 10% more health";
    mID = 2;
}

//FortifiedBark destructor
FortifiedBark::~FortifiedBark(void)
{
}

//Implementation of the FortifedBark  UseAbility
float FortifiedBark::UseAbility(Monster& monster)
{
    //set the amount of health and armor given
    mAmountOfArmorGiven = monster.AdjustStatPercent(mArmorPercentChanged, "Armor");
    mAmountOfHealthGiven = monster.AdjustStatPercent(mHealthPercentChanged, "Health");
    cout <<mAbilityName <<" increased " << monster.GetName() << "'s health by " << mAmountOfHealthGiven << " and armor by " << mAmountOfArmorGiven <<"!" << endl;

    return 1;
}

//SoothingDarkness constructor
SoothingDarkness::SoothingDarkness(void)
    :PassiveAbility()
{
    mHealthPercentChanged = .15f;
    mArmorPercentChanged = .15f;
    mDamagePercenChanged = .15f;
    mAbilityName = "Soothing Darkness";
    mDescription = "When fighing during the cover of night, your vampiric senses grow stronger granting you 15% armor, health, and damage";
    mID = 3;
}

//SoothingDarkness destructor
SoothingDarkness::~SoothingDarkness(void)
{
}

//Implementation of the SoothingDarkness UseAbility
float SoothingDarkness::UseAbility(Monster& monster)
{
    //set the amount of each stat given
    mAmountOfArmorGiven = monster.AdjustStatPercent(mArmorPercentChanged, "Armor");
    mAmountOfDamageGiven = monster.AdjustStatPercent(mDamagePercenChanged, "Damage");
    mAmountOfHealthGiven = monster.AdjustStatPercent(mHealthPercentChanged, "Health");
    cout << mAbilityName <<" increased " << monster.GetName() << "'s health by " << mAmountOfHealthGiven << ", armor by " << mAmountOfArmorGiven << " and damage by " << mAmountOfDamageGiven <<"!" << endl;

    return 1;
}

//BloodFrenzy constructor
BloodFrenzy::BloodFrenzy(void)
    :PassiveAbility()
{
    mDamagePercenChanged = .3f;
    mAbilityName = "Blood Frenzy";
    mDescription = "When a full moon is active, you go into a blood rage increasing your damage by 30%";
    mID = 4;
}

//BloodFrenzy destructor
BloodFrenzy::~BloodFrenzy(void)
{
}

//Implementation of the BloodFrenzy UseAbility
float BloodFrenzy::UseAbility(Monster& monster)
{
    //set the amount of damage given
    mAmountOfDamageGiven = monster.AdjustStatPercent(mDamagePercenChanged, "Damage");
    cout << mAbilityName <<" increased " <<  monster.GetName() << "'s damage by " << mAmountOfDamageGiven << "!" << endl;

    return 1;
}

//MeleeAttack constructor
MeleeAttack::MeleeAttack(void)
    :ActiveAbility()
{
    mDamageMod = 1.0;
    mAbilityName = "Melee Attack";
    mDescription = "Strike you opponent with a quick strike dealing 100% damage";
    mID = 5;
}

//MeleeAttack destructor
MeleeAttack::~MeleeAttack(void)
{
}

//Implementation of the MeleeAttack UseAbility
float MeleeAttack::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    //calculate the amount of damage melee attack should deal
    float damageDealt = DealDamage(attacker, beingAttacked);

    //subtract beingAttacked health by amount of damage dealt
    beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
    cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;

    return damageDealt;
}

//FeralFrenzy default constructor
FeralFrenzy::FeralFrenzy(void)
    :ActiveAbility()
{
    mDamageMod = 1.1f;
    mArmorPercentageIgnored = .2f;
    mAbilityName = "Feral Frenzy";
    mDescription = "Rip into your enemies flesh, dealing 110% damage that ignores 20% of your targets armor";
    mID = 6;
}

//FeralFrenzy destructor
FeralFrenzy::~FeralFrenzy(void)
{
}

//Implementation of the FeralFrenzy UseAbility
float FeralFrenzy::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    //calculate damage of ability
    float damageDealt = DealDamage(attacker, beingAttacked);

    //reduce the health of the monster being attacked
    beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
    cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;

    return damageDealt;
}

//CharingBash constructor
ChargingBash::ChargingBash(void)
{
    mDamageMod = 1.7f;
    mAbilityName = "Charing Bash";
    mDescription = "Charge at your enemy, dealing 170% of your damage";
    mID = 7;
}

//ChargingBash destructor
ChargingBash::~ChargingBash(void)
{
}

//Implementation of the ChargingBash UseAbility
float ChargingBash::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    //calculate amount of damage to deal
    float damageDealt = DealDamage(attacker, beingAttacked);

    //reduce the health of the monster being attacked
    beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
    cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;

    return damageDealt;
}

//SoulShatter constructor
SoulShatter::SoulShatter(void)
{
    mDamageMod = 1.20f;
   // mArmorIgnorePercent = .2f;
    mAbilityName = "Soul Shatter";
    mDescription = "Deal 120% of your damage, ignoring 20% of the targets armor";
    mID = 8;
}

//SoulShatter destructor
SoulShatter::~SoulShatter(void)
{
}

//Implementation of the SouldShatter UseAbility
float SoulShatter::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    //calculate amount of damage to deal
    float damageDealt = DealDamage(attacker, beingAttacked);

    //reduce the amount of health the monster being attacked has
    beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
    cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;

    return damageDealt;
}

//DrainEssence constructor
DrainEssence::DrainEssence(void)
{
    mDamageMod = 0.9f;
    mHealUserPercentOfDamage = .1f;
   // mPercentHealForDamageDealt = .1f;
    mAbilityName = "Drain Essence";
    mDescription = "Deal 90% of your damage and heal for 10% of the damage dealt";
    mID = 9;
}

//DrainEssence destructor
DrainEssence::~DrainEssence(void)
{
}

//Implementation of the DrainEssence UseAbility
float DrainEssence::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    //calculate amount of damage to deal
    float damageDealt = DealDamage(attacker, beingAttacked);

    //reduce being monster being attacked health
    beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
    cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;

    //Increase the attackers health based on the damage dealt
    float healthHealed = attacker.AdjustStatFlat(damageDealt * mHealUserPercentOfDamage, "Current Health");
    cout << attacker.GetName() << " healed for " << healthHealed << "!" << endl;

    return damageDealt;
}

//DeathsCaress constructor
DeathsCaress::DeathsCaress(void)
{
    mDamageMod = 2.5f;
    mHealthPercentageThresholdToUse = .3f;
    mAbilityName = "Death's Caress";
    mDescription = "Deal 250% of your damage if your target is below 30% health";
    mID = 10;
}

//DeathsCaress destructor
DeathsCaress::~DeathsCaress(void)
{
}


//Implementation of the DeathsCaress UseAbility
float DeathsCaress::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    float damageDealt = -1;

    //check if beingAttacked health is below the health % threshold to use the ability
    if (beingAttacked.HealthBelowPercent(mHealthPercentageThresholdToUse))
    {
        //calculate amount of damage to deal
        damageDealt = DealDamage(attacker, beingAttacked);

        //reduce being attacked monster's health
        beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
        cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;
    }
    return damageDealt;
}

//InfectiousBite constructor
InfectiousBite::InfectiousBite(void)
{
    mDamageMod = 1.3f;
    mHealUserPercentOfDamage = .07f;
    mAbilityName = "Infectious Bite";
    mDescription = "Deal 130% of your damage and heal for 7% of the damage dealt";
    mID = 11;
}

//InfectiousBite destructor
InfectiousBite::~InfectiousBite(void)
{
}

//Implementation of the InfectiousBite UseAbility
float InfectiousBite::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    //calculate amount of damage to deal
    float damageDealt = DealDamage(attacker, beingAttacked);
    beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
    cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;

    //Increase the attackers health based on the damage dealt
    float healthHealed = attacker.AdjustStatFlat(damageDealt * mHealUserPercentOfDamage, "Current Health");
    cout << attacker.GetName() << " healed for " << healthHealed << "!" << endl;

    return damageDealt;
}

//ConcussiveBlow constructor
ConcussiveBlow::ConcussiveBlow(void)
{
    mDamageMod = 1.7f;
    mAbilityName = "Concussive Blow";
    mDescription = "Strike the target with a hard hitting blow, dealing 170% of your damage";
    mID = 12;
}

//ConcussiveBlow destructor
ConcussiveBlow::~ConcussiveBlow(void)
{
}

//Implementation of the ConcusiveBlow UseAbility
float ConcussiveBlow::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    //calculate amount of damage to deal
    float damageDealt = DealDamage(attacker, beingAttacked);

    //reduce enemy monster health
    beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
    cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;

    return damageDealt;
}

//CrushArmor constructor
CrushArmor::CrushArmor(void)
{
    mDamageMod = .5f;
    mAbilityName = "Crush Armor";
    mDescription = "Deal 50% of your damage and reduce your targets armor by 15%";
    mID = 13;
}

//CrushArmor destructor
CrushArmor::~CrushArmor(void)
{
}


//Implementation of the CrushArmor UseAbility
float CrushArmor::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    CrushedArmor crushedArmor;

    //calculate amount of damage to deal
    float damageDealt = DealDamage(attacker, beingAttacked);

    //reduce enemy monster health
    beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
    cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;

    //add CrushedArmor passive to the target
    float armorReduced = beingAttacked.addAbility(crushedArmor);
    return damageDealt;
}

//SacrificeLimb construsctor
SacrificeLimb::SacrificeLimb(void)
{
    mDamageMod = 1.9f;
    mAbilityName = "Sacrific Limb";
    mDescription ="Rip off one off your appendages, throwing it at the target for 190% damage, but lose 10% of your health";
    mID = 14;
}

//SacrificeLimb destructor
SacrificeLimb::~SacrificeLimb(void)
{
}

//Implementation of the SacrificeLimb UseAbility
float SacrificeLimb::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    //calculate amount of damage to deal
    float damageDealt = DealDamage(attacker, beingAttacked);

    //reduce enemy monster health
    beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
    cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;

    //Reduce the users health based on the health percent lost
    float healthLost = attacker.AdjustStatPercent(-.1, "Current Health");
    cout << attacker.GetName() << " lost " << -healthLost << " health!" << endl;
    return damageDealt;
}

//Berserk constructor
Berserk::Berserk(void)
{
    mAbilityName = "Berserk";
    mDescription = "Sacrifice your max health and armor by 10% to gain 18% damage";
    mID = 15;
}

//Berserk destructor
Berserk::~Berserk(void)
{
}

//Implementation of the Berserk UseAbility
float Berserk::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    Rage rage;

    //apply the rage passive ability to monster using the ability
    attacker.addAbility(rage);
    return 1.0f;
}

//ShreddingSwipe constructor
ShreddingSwipe::ShreddingSwipe(void)
{
    mDamageMod = .6f;
    mAbilityName = "Shredding Swipe";
    mDescription = "Shred your enemies armor, dealing 60% damage, and reducing their armor by 20%";
    mID = 16;
}

//ShreddingSwipe destuctor
ShreddingSwipe::~ShreddingSwipe(void)
{
}

//Implementation of the ShreddingSwipe UseAbility
float ShreddingSwipe::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    ShreddedArmor shreddedArmor;

    //calculate amount of damage to deal
    float damageDealt = DealDamage(attacker, beingAttacked);

    //reduce enemy monster health
    beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
    cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;

    //apply shreddedArmor passive to the monster being attacked
    beingAttacked.addAbility(shreddedArmor);
    
    return damageDealt;
}

//Stomp constructor
Stomp::Stomp(void)
{
    mDamageMod = 1.2f;
    mAbilityName = "Stomp";
    mDescription = "Stomp the ground dealing 120% damage to your target";
    mID = 17;
}

//Stomp destructor
Stomp::~Stomp(void)
{
}

//Implementation of the Stomp UseAbility
float Stomp::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    //calculate amount of damage to deal
    float damageDealt = DealDamage(attacker, beingAttacked);

    //reduce enemy monster health
    beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
    cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;

    return damageDealt;
}

//EntanglingRoots constructor
EntanglingRoots::EntanglingRoots(void)
{
    mDamageMod = 1.2f;
    mHealUserPercentOfDamage = .1f;
    mAbilityName = "Entangling Roots";
    mDescription = "Grip your target with roots, dealing 120% damage and leach 10% of the damage dealt";
    mID = 18;
}

//EntanglingRoots destructor
EntanglingRoots::~EntanglingRoots(void)
{
}

//Implementation of the EntanglingRoots UseAbility
float EntanglingRoots::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    //calculate damage to deal
    float damageDealt = DealDamage(attacker, beingAttacked);

    //reduce enemy monster health
    beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
    cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;

    //increase the attackers health based on the damage dealt
    float healthLost = attacker.AdjustStatFlat(damageDealt * mHealUserPercentOfDamage, "Current Health");
    cout << attacker.GetName() << " lost " << healthLost << " health!" << endl;
    return damageDealt;
}

//DreadfulRoar constructor
DreadfulRoar::DreadfulRoar(void)
{
    mDamageMod = .5f;
    mAbilityName = "Dreadful Roar";
    mDescription = "Relase a dreadful roar, dealing 50% damage and reducing the target's armor by 15%";
    mID = 19;
}

//DreadfulRoar destructor
DreadfulRoar::~DreadfulRoar(void)
{
}


//Implementation of the DreadfulRoat UseAbility
float DreadfulRoar::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    Demoralized demoralized;

    //calculate damage to deal
    float damageDealt = DealDamage(attacker, beingAttacked);

    //reduce being attacked health
    beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
    cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;

    //apply the demoralized passive ability to the monster being attacked
    beingAttacked.addAbility(demoralized);

    return damageDealt;
}

//Slam constructor
Slam::Slam(void)
{
    mDamageMod = 1.5f;
    mArmorPercentageIgnored = .15f;
    mAbilityName = "Slam";
    mDescription = "Slam the target with a branch dealing 150% of your damage, and ignoring 15% of their armor";
    mID = 20;
}

//Slam destructor
Slam::~Slam(void)
{
}

//Implementation of the Slam UseAbility
float Slam::UseAbility(Monster& attacker, Monster& beingAttacked)
{
    //calculate the amount of damage to deal
    float damageDealt = DealDamage(attacker, beingAttacked);

    //apply the damage to the monster being attacked
    beingAttacked.AdjustStatFlat(-damageDealt, "Current Health");
    cout << attacker.GetName() << " used " << mAbilityName << " dealing " << damageDealt << " damage!" << endl;

    return damageDealt;
}

//CrushedArmor constructor
CrushedArmor::CrushedArmor()
    :PassiveAbility()
{
    mAbilityName = "Crushed Armor";
    mDescription = "Sunder the enemey's armor, reducing it by 15%";
    mID = 21;
    mArmorPercentChanged = .15f;
}

//CrushedArmor destructor
CrushedArmor::~CrushedArmor()
{
}

//Implementation of the CrushedArmor UseAbility
float CrushedArmor::UseAbility(Monster& monster)
{
    //calculate teh amount of armor to take away
    float armorReduced = monster.GetArmor() * mArmorPercentChanged;

    //store amount of armor taken away and take away the armor from the monster
    mAmountOfArmorGiven = monster.AdjustStatFlat(-armorReduced, "Armor");
    cout << monster.GetName() << "'s armor has been reduced by " << -mAmountOfArmorGiven << "!" << endl;

    return armorReduced;
}

//Rage constructor
Rage::Rage()
    :PassiveAbility()
{
    mAbilityName = "Rage";
    mDescription = "Reduce your health and armor to increase your damage";
    mID = 22;
    mHealthPercentChanged = .1f;
    mArmorPercentChanged = .1f;
    mDamagePercenChanged = .18f;
}

//Rage destructor
Rage::~Rage()
{
}

//Implementation of the Rage UseAbility
float Rage::UseAbility(Monster& monster)
{

    //calculate the amount of stats to give and take away
    float healthReduced = monster.GetMaxHealth() * mHealthPercentChanged;
    float armorReduced = monster.GetArmor() * mArmorPercentChanged;
    float damageIncreased = monster.GetDamage() * mDamagePercenChanged;

    //set the amount of stats given and taken away
    mAmountOfHealthGiven = monster.AdjustStatFlat(-healthReduced, "Health");
    mAmountOfArmorGiven = monster.AdjustStatFlat(-armorReduced, "Armor");
    mAmountOfDamageGiven = monster.AdjustStatFlat(damageIncreased, "Damage");
    cout << monster.GetName() << " lost " << healthReduced << " health, but gained " << damageIncreased << " damage!" << endl;
    
    return 1.0f;
}

//ShreddedArmor constructor
ShreddedArmor::ShreddedArmor()
    :PassiveAbility()
{
    mAbilityName = "Shredded Armor";
    mDescription = "Reduce your targets armor by 20%";
    mID = 23;
    mArmorPercentChanged = .2f;
}

//ShreddedArmor destructor
ShreddedArmor::~ShreddedArmor()
{
}

//Implementation of the ShreddedArmor UseAbility
float ShreddedArmor::UseAbility(Monster& monster)
{
    //calculate the amount of armor that will be taken away
    float armorReduced = monster.GetArmor() * mArmorPercentChanged;

    //reduce the percent of armor and set the amount of armor reduced
    mAmountOfArmorGiven = monster.AdjustStatFlat(-armorReduced, "Armor");
    cout << monster.GetName() << "'s armor has been reduced by " << armorReduced << "! " << endl;
    
    return 1.0f;
}

//Demoralized constuctor
Demoralized::Demoralized()
    :PassiveAbility()
{
    mAbilityName = "Demoralized";
    mDescription = "Demoralize your opponent reducing their armor by %15";
    mID = 24;
    mArmorPercentChanged = .15f;
}

//Demoralized destructor
Demoralized::~Demoralized()
{
}

//Implementation of the Demoralized UseAbility
float Demoralized::UseAbility(Monster& monster)
{
    //calculate the amount of armor that will be taken away
    float armorReduced = monster.GetArmor() * mArmorPercentChanged;
    
    //reduce the percent of armor and set the amount of armor reduced
    mAmountOfArmorGiven = monster.AdjustStatFlat(-armorReduced, "Armor");
    cout << monster.GetName() << "'s armor has been reduced by " << armorReduced << "! " << endl;
    return 1.0f;
}