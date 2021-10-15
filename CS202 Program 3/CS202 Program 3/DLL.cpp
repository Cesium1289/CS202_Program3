//NAME:Carson Hansen
//FILE NAME:DLL.cpp
//PURPOSE:Implement the DLL and the DLL array
#include "DLL.h"
#include<iostream>
using namespace std;

//DLL default constructor
DLL::DLL(void)
    :mHead(nullptr)
{
}

//DLL destructor
DLL::~DLL(void)
{
    Destroy();
}

//Wrapper function to destroy the DLL. Returns the number of items removed
int DLL::Destroy(void)
{
    if (!mHead)
        return 0;
    return Destroy(mHead);
}

//Recursive function to destroy the DLL.
//Returns the number of items removed
int DLL::Destroy(Ability*& mHead)
{
    if (!mHead)
        return 0;
    Ability* temp;
    temp = mHead->getNext();
    
    delete mHead;
    mHead = nullptr;
    mHead = temp;
    return Destroy(mHead) + 1;
}

//Overloaded = for DLL
DLL& DLL::operator=(const DLL& obj)
{
    if (this == &obj)
        return *this;
    Destroy();
    Ability* temp = mHead;
    Copy(obj.mHead, mHead, temp);
    return *this;
}

//Wrapper function to copy the DLL
int DLL::Copy(DLL& source)
{
    Ability* prev = nullptr;
    if (!source.mHead)
        return 0;
    return Copy(source.mHead, mHead, prev);
}

//Recursive function to copy all of the abilities in the DLL
int DLL::Copy(Ability* source, Ability*& mHead, Ability*& prev)
{
    //check if there is an ability to copy
    if (!source)
        return 0;

    //compare the ability ID
    if (source->sameAbilityId(1))
        mHead = new InspiringPresence();
    else if (source->sameAbilityId(2))
        mHead = new FortifiedBark();
    else if (source->sameAbilityId(3))
        mHead = new SoothingDarkness();
    else if (source->sameAbilityId(4))
        mHead = new BloodFrenzy();
    else if (source->sameAbilityId(5))
        mHead = new MeleeAttack();
    else if (source->sameAbilityId(6))
        mHead = new FeralFrenzy();
    else if (source->sameAbilityId(7))
        mHead = new ChargingBash();
    else if (source->sameAbilityId(8))
        mHead = new SoulShatter();
    else if (source->sameAbilityId(9))
        mHead = new DrainEssence();
    else if (source->sameAbilityId(10))
        mHead = new DeathsCaress();
    else if (source->sameAbilityId(11))
        mHead = new InfectiousBite();
    else if (source->sameAbilityId(12))
        mHead = new ConcussiveBlow();
    else if (source->sameAbilityId(13))
        mHead = new CrushArmor();
    else if (source->sameAbilityId(14))
        mHead = new SacrificeLimb();
    else if (source->sameAbilityId(15))
        mHead = new Berserk();
    else if (source->sameAbilityId(16))
        mHead = new ShreddingSwipe();
    else if (source->sameAbilityId(17))
        mHead = new Stomp();
    else if (source->sameAbilityId(18))
        mHead = new EntanglingRoots();
    else if (source->sameAbilityId(19))
        mHead = new DreadfulRoar();
    else if (source->sameAbilityId(20))
        mHead = new Slam();

    //the ability being copied does not exist
    else
        return 0;

    mHead->setPreviuos(prev);
    prev = mHead;
    return Copy(source->getNext(), mHead->getNext(), prev) + 1;
}

//Wrapper function that will remove all the passive effects from a battle
int DLL::RemovePassiveEffects(Monster& monster)
{
    //dynamic cast a passiveAbility to head to see if head is a passiveAbility pointer
    PassiveAbility* passive = dynamic_cast<PassiveAbility*>(mHead);
   
    //check if the head node was a passive ability. If it was, remove
    //all passive effects the monster has
    if (passive)
        return RemovePassiveEffects(passive, monster);
 
    return 0;
}

//Recursive function to remove all the passive effects a monster has.
//Returns that number of passive effects that were removed
int DLL::RemovePassiveEffects(PassiveAbility*& mHead, Monster& monster)
{
    if(!mHead)
        return 0;
    mHead->RemovePassiveEffect(monster);

    Ability* temp = this->mHead->getNext();
    delete mHead;
    this->mHead = temp;
    
    //dynamic_cast the head pointer to a passive ability
    PassiveAbility* passive = dynamic_cast<PassiveAbility*>(this->mHead);
    return RemovePassiveEffects(passive, monster) +1;
}

//Compare two abilities. If they are null or don't have the same ID
//returns false. Else returns true
bool DLL::IsTheSame(Ability* mHead, Ability* toCompare)
{
    if (!mHead && !toCompare)
        return false;

    if (mHead->sameAbilityId(*toCompare))
        return IsTheSame(mHead->getNext(), toCompare->getNext());
    return false;
}

//Recursive add function to add a monster to the DLL
int DLL::Add(Ability& toAdd, Monster& monster)
{
    Ability* newAbility = nullptr;

    //check if ability being added is a passive ability
    PassiveAbility* passive = dynamic_cast<PassiveAbility*>(&toAdd);
    if (passive)
    {
        if (toAdd.sameAbilityId(1))
            passive = new InspiringPresence();
        else if (toAdd.sameAbilityId(2))
            passive = new FortifiedBark();
        else if (toAdd.sameAbilityId(3))
            passive = new SoothingDarkness();
        else if (toAdd.sameAbilityId(4))
            passive = new BloodFrenzy();
        else if (toAdd.sameAbilityId(21))
            passive = new CrushedArmor();
        else if (toAdd.sameAbilityId(22))
            passive = new Rage();
        else if (toAdd.sameAbilityId(23))
            passive = new ShreddedArmor();
        else if (toAdd.sameAbilityId(24))
            passive = new Demoralized();
        else
            return 0;

        //Apply the passiveAbility effects to the monster
        passive->UseAbility(monster);

        if (!mHead)
        {
            mHead = passive;
            mHead->setNext(nullptr);
            mHead->setPreviuos(nullptr);
            return 1;
        }
        else
        {
            passive->setNext(mHead);
            mHead->setPreviuos(passive);
            mHead = passive;
            return 1;
        }
    }
    else
    {
        if (toAdd.sameAbilityId(5))
            newAbility = new MeleeAttack();
        else if (toAdd.sameAbilityId(6))
            newAbility = new FeralFrenzy();
        else if (toAdd.sameAbilityId(7))
            newAbility = new ChargingBash();
        else if (toAdd.sameAbilityId(8))
            newAbility = new SoulShatter();
        else if (toAdd.sameAbilityId(9))
            newAbility = new DrainEssence();
        else if (toAdd.sameAbilityId(10))
            newAbility = new DeathsCaress();
        else if (toAdd.sameAbilityId(11))
            newAbility = new InfectiousBite();
        else if (toAdd.sameAbilityId(12))
            newAbility = new ConcussiveBlow();
        else if (toAdd.sameAbilityId(13))
            newAbility = new CrushArmor();
        else if (toAdd.sameAbilityId(14))
            newAbility = new SacrificeLimb();
        else if (toAdd.sameAbilityId(15))
            newAbility = new Berserk();
        else if (toAdd.sameAbilityId(16))
            newAbility = new ShreddingSwipe();
        else if (toAdd.sameAbilityId(17))
            newAbility = new Stomp();
        else if (toAdd.sameAbilityId(18))
            newAbility = new EntanglingRoots();
        else if (toAdd.sameAbilityId(19))
            newAbility = new DreadfulRoar();
        else if (toAdd.sameAbilityId(20))
            newAbility = new Slam();
        else
            return 0;
    }

    //check if there is a head node
    if (!mHead)
    {
        mHead = newAbility;
        return 1;
    }
    else
    {
        newAbility->setNext(mHead);
        mHead->setPreviuos(newAbility);
        mHead = newAbility;
        return 1;
    }

    //check if mHead was a passive ability. If it was
    //call UseAbility function to apply the ability effect
    return 1;
}

//Wrapper function to display the DLL.
//Returns the number of items displayed
int DLL::Display(void)
{
    if (!mHead)
        return 0;
    return Display(mHead);
}

//Recursive display for DLL. Returns number of abililities displayed
int DLL::Display(Ability* mHead)
{
    if (!mHead)
        return 0;
    mHead->display();
    return Display(mHead->getNext()) + 1;
}

//Wrapper function to return the number of abilities in the list
int DLL::Count(void)
{
    if (!mHead)
        return 0;
    return Count(mHead);
}

//Recursive function to return the number of abilities in the list
int DLL::Count(Ability* mHead)
{
    if (!mHead)
        return 0;
    return Count(mHead->getNext()) + 1;
}

//Wrapper function to display the abilities with a index number to the left of the name
int DLL::DisplayNumbered(void)
{
    int index = 1;
    if (!mHead)
        return 0;
    return DisplayNumbered(mHead, index);
}

//Recursive function to display the abilities with a index number to the left of the name
//returns the number of abilities displayed
int DLL::DisplayNumbered(Ability* mHead, int index)
{
    if (!mHead)
        return 0;
    cout << index << ". ";
    //call ability displayName function
    mHead->displayName();
    ++index;
    return DisplayNumbered(mHead->getNext(), index) + 1;
}

//Check if the DLL is empty
bool DLL::IsEmpty(void)
{
    if (!mHead)
        return true;
    return false;
}

//Wrapper function to return the Ability at a given index
//Return a pointer to the ability based on the index of the ability,
// or returns null if the index is out of bounds
Ability* DLL::GetIndex(int index)
{
    if (!mHead)
        return nullptr;
    if (index == 0)
        return mHead;
    else
    {
        int currentIndex = 1;
        return GetIndex(mHead->getNext(), index, currentIndex);
    }
}

//Recurssive function to return an ability based on the index it is in the DLL
//Will return a pointer to the ability if the index is found, null if it is out of
//bounds
Ability* DLL::GetIndex(Ability* mHead, int index, int currentIndex)
{
    if (!mHead)
        return nullptr;
    else if (index == currentIndex)
        return mHead;
    else
    {
        ++currentIndex;
        return GetIndex(mHead->getNext(), index, currentIndex);
    }
}

//DLLArray default constructor
DLLArray::DLLArray(void)
{
    mHead = new DLL * [2];
    for (int i = 0; i < 2; i++)
        mHead[i] = new DLL();
}

//DLLArray destructor
DLLArray::~DLLArray(void)
{
    Destroy();

    if (mHead)
        delete[] mHead;
    mHead = nullptr;
}

//Wrapper function to delete all the nodes
int DLLArray::Destroy(void)
{
    int removed = 0;
    int index = 0;
    if (!mHead)
        return 0;
    removed += Destroy(mHead, index);
    if (mHead)
        delete[] mHead;
    mHead = nullptr;
    return removed;
}

//Wrapper to display the active abilities the user has.
//Returns the number of abilities dispalyed
int DLLArray::DisplayActiveAbilities()
{
    if (!mHead)
        return 0;
    return DisplayActiveAbilities(mHead);
}

//Wrapper function to remove all the passive abilities
//from the monster. Returns the number of abilities removed
int DLLArray::RemovePassiveEffects(Monster& monster)
{
    return mHead[1]->RemovePassiveEffects(monster);
}

//Wrapper function to display all the active abilities
//the monster has
int DLLArray::DisplayActiveAbilities(DLL** mHead)
{
    if (!mHead[0])
        return 0;
    return mHead[0]->Display();
}

//Recursive function to destroy all the nodes in the DLLArray
int DLLArray::Destroy(DLL**& mHead, int& index)
{
    int removed = 0;
    if (index == 2)
        return 0;
    if (mHead[index])
    {
        removed += mHead[index]->Destroy();
        delete mHead[index];
        mHead[index] = nullptr;
    }
    return Destroy(mHead, ++index) + removed;
}

//Overloaded = for DLL
DLLArray& DLLArray::operator=(const DLLArray& obj)
{
    if (this == &obj)
        return *this;
    Destroy();
    mHead = new DLL * [2];
    for (int i = 0; i < 2; i++)
        mHead[i] = new DLL();
    int index = 0;
    Copy(obj.mHead, mHead, index);
    return *this;
}

//Wrapper function to Copy the DLLArray
int DLLArray::Copy(DLLArray& source)
{
    int index = 0;
    if (!mHead || !source.mHead)
        return 0;
    return Copy(&source.mHead[index], mHead, index);
}

//Recursive fucntion to copy the DLLArray
int DLLArray::Copy(DLL** source, DLL**& mHead, int index)
{
    int copied = 0;
    if (index == 2)
        return 0;

    //call the DLL copy function
    mHead[index]->Copy(*source[index]);
    return Copy(source, mHead, ++index);
}

//Wrapper function to get an active ability at a given index
//returns the ability in the index if it was in bounds,
//null if it was not
Ability* DLLArray::GetActiveAbility(int index)
{
    return mHead[0]->GetIndex(index);
}

//Wrapper function to get an passive ability at a given index
//returns the ability in the index if it was in bounds,
//null if it was not
Ability* DLLArray::GetPassiveAbility(int index)
{
    return mHead[1]->GetIndex(index);
}

//Add an ability to the DLL. This decides if it should go in the
//0th or 1st index. 0th index is for active abilities and the 1st is for passives
int DLLArray::Add(Ability& toAdd, Monster& monster)
{
    //check if ability being added is a passive ability
    PassiveAbility* passive = dynamic_cast<PassiveAbility*>(&toAdd);
    if (passive)
        return mHead[1]->Add(toAdd, monster);
    else
        return mHead[0]->Add(toAdd, monster);
    return 0;
}

//Wrapper function to display the DLLArray
int DLLArray::Display(void)
{
    int index = 0;
    if (!mHead)
        return 0;
    return Display(mHead, index);
}

//Recursive display for the DLLArray. Returns the number of data members displayed
int DLLArray::Display(DLL** mHead, int index)
{
    int displayed = 0;
    if (index == 2)
        return 0;
    displayed = mHead[index]->Display();
    ++index;
    return Display(mHead, index) + displayed;
}

//Wrapper function to display the monsters active abilities with a number next to it
int DLLArray::DisplayActiveByNumber(void)
{
    if (!mHead)
        return 0;
    return DisplayActiveByNumber(mHead);
}

//Call the DLL that holds the active abilities
int DLLArray::DisplayActiveByNumber(DLL** mHead)
{
    if (!mHead[0])
        return 0;
    return mHead[0]->DisplayNumbered();
}

//Wrapper function to return the number of active abilities the monster has
int DLLArray::Count(void)
{
    if (!mHead || !mHead[0])
        return 0;
    return Count(mHead);
}

//Return the number of active abilities the monster has
int DLLArray::Count(DLL** mHead)
{
    if (!mHead[0])
        return 0;
    return mHead[0]->Count();
}
