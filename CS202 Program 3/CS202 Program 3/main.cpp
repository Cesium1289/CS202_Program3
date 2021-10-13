//NAME:Carson Hansen
//FILE NAME:main.cpp
//PURPOSE: Allow the user to fight monsters!
#include <iomanip>
#include<iostream>
#include"Ability.h"
#include"BST.h"
#include"DLL.h"
#include "Monster.h"
using namespace std;

//Prototypes
int menu(void);
void createMonster(BST& playerMonsters, Monster*& currentMonster);
void generateEnemyMonsters(BST& tree);
void shop(Monster*& player);
void battleBash(Monster*& player, BST& enemyTree);
void generateBattleGround(Monster& player, Monster& enemy);
void selectDiffernMonster(BST& playerMonsters, Monster*& currentMonster);

int main()
{
	BST enemyTTT;
	BST playerTTT;
	Monster* currentMonster = nullptr;
	int selection;
	bool done = false;
	srand(time_t(NULL));

	//generate enemies
	generateEnemyMonsters(enemyTTT);

	do {
		//call the menu function
		selection = menu();

		switch (selection)
		{
		case 1:
		{
			//call the create monster function passing it the  BST of monsters 
			//the player has as well as the current monster
			createMonster(playerTTT, currentMonster);
			break;
		}
		case 2:
		{
			//call the select differnt monster function, passing it the
			//tree of monsters the user has as well as the current monster
			selectDiffernMonster(playerTTT, currentMonster);
			break;
		}
		case 3:
		{
			//call shop function passing the current player
			shop(currentMonster);
			break;
		}
		case 4:
		{
			//call the battleBash passing it the current monster the player is and the 
			//tree of enemies
			battleBash(currentMonster, enemyTTT);
			break;
		}
		case 5:
		{
			//check if the user has a current monster
			if (!currentMonster)
				cout << "You have no monster to display\n";
			else
			{
				//call the current monster display
				currentMonster->display();
				currentMonster->displayActiveAbilities();
			}
			break;
		}
		case 6:
		{
			done = true;
			break;
		}
		default:
		{
			cout << "Should not have got here...\nClosing program...";
			done = true;
			break;
		}
		}
	} while (!done);
}

//Display menu to the user
int menu()
{
	int choice = 0;
	cout << "1.Create character \n";
	cout << "2.Select a different character\n";
	cout << "3.Visit shop\n";
	cout << "4.Fight enemy\n";
	cout << "5.Display currrent character\n";
	cout << "6. Exit\n";
	cin >> choice; cin.ignore(256, '\n');

	//validate input
	while (cin.fail() || choice < 1 || choice > 6)
	{
		cin.clear(); cin.ignore(256, '\n');
		cout << "Enter valid choice\n";
		cin >> choice; cin.ignore(256, '\n');
	}
	return choice;
}

//Let the user create a monster
void createMonster(BST& playerMonsters, Monster*& currentMonster)
{
	int choice;
	string name;

	cout << "Enter the monster's name\n";
	cin >> name;
	cin.ignore(256, '\n');

	//show the special passive ability the monster will get to the user
	cout << "-_-_-_-Selecting different monsters can grant bonuses when fighting in different areas or time of day-_-_-_-\n";
	cout << "Vampire- Soothing darkness: when fighing during the cover of night, your vampiric sense grow stronger granting you 15% armor, health, and damage\n";
	cout << "Werewolf - Blood Frenzy: when a full moon is active, you go into a blood rage increasing your damage by 30%\n";
	cout << "Treant - Fortified Bark: When fighing in the forest, your bark thickens granting you 30% increased armor and 10% more health\n";
	cout << "Undead - Inspiring Pressence: When fighting in a graveyard, you call upon fallen allies to aid you in combat granting 40% increased health\n";
	cout << "\n\nSelect a mosnter type\n";
	cout << "1.Vampire\n";
	cout << "2.Werewolf\n";
	cout << "3.Treant\n";
	cout << "4.Undead\n";
	cin >> choice;

	//validate input
	while (cin.fail() || choice < 1 || choice > 4)
	{
		cin.clear(); cin.ignore(256, '\n');
		cout << "Enter a valid choice\n";
		cin >> choice; cin.ignore(256, '\n');
	}

	//add the correct monster the the BST
	//Set the current monster to the monster they just created
	if (choice == 1)
	{
		Vampire newMonster(name);
		playerMonsters.Add(newMonster);
		currentMonster = playerMonsters.Get(newMonster.GetName());
	}
	else if (choice == 2)
	{
		Werewolf newMonster(name);
		playerMonsters.Add(newMonster);
		currentMonster = playerMonsters.Get(newMonster.GetName());
	}
	else if (choice == 3)
	{
		Treant newMonster(name);
		currentMonster = &newMonster; playerMonsters.Add(newMonster);
		currentMonster = playerMonsters.Get(newMonster.GetName());
	}
	else
	{
		Undead newMonster(name);
		playerMonsters.Add(newMonster);
		currentMonster = playerMonsters.Get(newMonster.GetName());
	}
}

//Generate enemies the player monsters will fight
void generateEnemyMonsters(BST& bst)
{
	//create an array of differnt enemies
	Vampire vamp[2];
	Werewolf werewolf[2];
	Undead undead[2];
	Treant treant[2];

	//create the enemy stats
	int enemyLevel = 1;
	float enemyHealth = 370.0f;
	float enemeyDamage = 70.0f;
	float enemyArmor = 85.0f;
	float multiplier = 1.13f;

	//create monsters for player to fight and give them stats
	vamp[0] = { "Alaric","Vampire",enemyHealth ,enemyArmor ,enemeyDamage ,enemyLevel };
	enemeyDamage *= multiplier, enemyArmor *= multiplier, enemyHealth *= multiplier, ++enemyLevel;
	treant[0] = { "Bul","Treant",enemyHealth ,enemyArmor ,enemeyDamage ,enemyLevel };
	enemeyDamage *= multiplier, enemyArmor *= multiplier, enemyHealth *= multiplier, ++enemyLevel;
	werewolf[0] = { "Chris" ,"Werewolf",enemyHealth ,enemyArmor ,enemeyDamage ,enemyLevel };
	enemeyDamage *= multiplier, enemyArmor *= multiplier, enemyHealth *= multiplier, ++enemyLevel;
	undead[0] = { "Dave","Undead",enemyHealth ,enemyArmor ,enemeyDamage ,enemyLevel };
	enemeyDamage *= multiplier, enemyArmor *= multiplier, enemyHealth *= multiplier, ++enemyLevel;
	vamp[1] = { "Frank","Vampire",enemyHealth ,enemyArmor ,enemeyDamage ,enemyLevel };
	enemeyDamage *= multiplier, enemyArmor *= multiplier, enemyHealth *= multiplier, ++enemyLevel;
	treant[1] = { "Harry","Treant",enemyHealth ,enemyArmor ,enemeyDamage ,enemyLevel };
	enemeyDamage *= multiplier, enemyArmor *= multiplier, enemyHealth *= multiplier, ++enemyLevel;
	werewolf[1] = { "Jeff","Werewolf",enemyHealth ,enemyArmor ,enemeyDamage ,enemyLevel };
	enemeyDamage *= multiplier, enemyArmor *= multiplier, enemyHealth *= multiplier, ++enemyLevel;
	undead[1] = { "Kira","Undead",enemyHealth ,enemyArmor ,enemeyDamage ,enemyLevel };
	enemeyDamage *= multiplier, enemyArmor *= multiplier, enemyHealth *= multiplier, ++enemyLevel;
	
	//add monsters to the enemy BST
	for (int i = 0; i < 2; i++)
	{
		bst.Add(vamp[i]);
		bst.Add(treant[i]);
		bst.Add(werewolf[i]);
		bst.Add(undead[i]);
	}
}

//Show the user the shop which allows them to increase their armor, health, or damage
void shop(Monster*& player)
{
	int choice = 0;
	float increased = 0.0f;
	bool notDone = true;

	//check if ther is a current player
	if (!player)
	{
		cout << "Create a player to view shop\n";
		return;
	}

	//while user is not done with the store
	while (notDone)
	{

		//display the player stats and gold
		player->display();
		cout << "1. +7 armor (60g)\n";
		cout << "2. +10 health (50g)\n";
		cout << "3. +7 damage (75g)\n";
		cout << "4.Exit\n";
		cin >> choice; cin.ignore(256, '\n');

		//validate input
		while (cin.fail() || choice < 0 || choice > 4)
		{
			cin.clear(); cin.ignore(256, '\n');
			cout << "Enter a valid choice\n";
		}

		if (choice == 1)
		{
			if (player->removeGold(60))
			{
				increased = player->AdjustStatFlat(7.0f, "Armor");
				cout << "Your armor has been incrased to " << increased << "\n";
			}
			else
				cout << "You lack the funds to purchase this\n";
		}
		else if (choice == 2)
		{
			if (player->removeGold(50))
			{
				increased = player->AdjustStatFlat(10.0f, "Health");
				cout << "Your health has been increased to " << increased << "\n";
			}
			else
				cout << "You lack the funds to purchase this\n";
		}
		else if (choice == 3)
		{
			if (player->removeGold(75))
			{
				increased = player->AdjustStatFlat(7.0f, "Damage");
				cout << "Your damage has been increased to " << increased << "\n";
			}
			else
				cout << "You lack the funds to purchase this\n";
		}
		else if (choice == 4)
		{
			notDone = false;
		}
	}
	return;
}


//Allows the user to battle another monster
void battleBash(Monster*& player, BST& enemyBST)
{
	//check if the player has a monster
	if (!player)
	{
		cout << "You must create a character before battling a monster!\n";
		return;
	}

	float playerDamageDealt = 0;
	float enemyDamageDealt = 0;
	
	Monster* enemy = nullptr;
	enemy = enemyBST.GetByLevel(player->GetLevel());

	//check if an enemy monster was selected
	if (!enemy)
	{
		cout << "Your current monster has bested all other monsters"
			<< "In its way.\n Select or create a new monster to fight\n";
		return;
	}

	//generate a random time of day and setting for the battle
	generateBattleGround(*player, *enemy);
	
	//check if the player and the enemy is alive
	while (player->isAlive() && enemy->isAlive())
	{
		//display the battle interface
		player->displayBattle(*enemy);

		//check that the player and enemy are alive
		if (player->isAlive() && enemy->isAlive())
		{
			//call the player useAbility function and pass it the enemy
			playerDamageDealt = player->useAbility(*enemy);

			//check if user tried to use an ability that was currently unusable
			//let user attack until they have a valid attack
			while (playerDamageDealt <= 0.0f)
			{
				cout << "\nUnable to use that ability. Select another!\n";
				playerDamageDealt = player->useAbility(*enemy);
			}
		}

		//check if the enermy and player is alive
		if (enemy->isAlive() && player->isAlive())
		{
			//call the monster userRandom ability to let the monster select an ability to use
			//pass the player as the argument
			enemyDamageDealt = enemy->useRandomAbility(*player);

			//check if enemy tried to use something unusable
			while (enemyDamageDealt <= 0.0f)
			{
				//let the enemy randomly select a valid ability
				enemyDamageDealt = enemy->useRandomAbility(*player);
			}
		}
	}

	//display the results of the battle
	player->displayBattle(*enemy);

	//check if the enemy is dead
	if (!enemy->isAlive())
	{
		cout << "Congratz you won the battle and leveled up!\nYour stats and gold has increased!\n\n\n";

		//level up the player after they won the battle
		player->levelUp();
	}
	//check if the player is dead
	else
		cout << "You were bested in battle. Try again!\n\n\n";
	
	//remove the passive effects the monsters had
	player->RemovePassiveEffects();
	enemy->RemovePassiveEffects();

	//reset the current health of the player and enemy to the inital value
	player->SetCurrentHealthToMax();
	enemy->SetCurrentHealthToMax();
}

//Randomly select where the battle will take place as well as the time of day.
//This is used to allow certain monsters to gain unique passive abilities 
//if the location and time of day  benefit them
void generateBattleGround(Monster& player, Monster& enemy)
{
	int location = 0;
	int timeOfDay = 0;

	//1 = forest, 2 = graveyard, 3 = abandoned town
	location = rand() % (3 - 1 + 1) + 1;
	//1 = sunset 2 = moonless night, 3 = full moon
	timeOfDay = rand() % (3 - 1 + 1) + 1;


	Vampire* playerVamp = dynamic_cast<Vampire*>(&player);
	Vampire* enemyVamp = dynamic_cast<Vampire*>(&enemy);
	Undead* playerUndead = dynamic_cast<Undead*>(&player);
	Undead* enemyUndead = dynamic_cast<Undead*>(&enemy);
	Treant* playerTreant = dynamic_cast<Treant*>(&player);
	Treant* enemyTreant = dynamic_cast<Treant*>(&enemy);
	Werewolf* playerWerewolf = dynamic_cast<Werewolf*>(&player);
	Werewolf* enemyWerewolf = dynamic_cast<Werewolf*>(&enemy);

	//check if the location is the forest
	if (location == 1)
	{
		//check if the player or enemy is a treat monster
		//if they are. Give them the special passive ability
		FortifiedBark fb;
		if (playerTreant)
			player.addAbility(fb);
		if (enemyTreant)
			enemy.addAbility(fb);
	}
	//check if the location is the graveyard
	else if (location == 2)
	{
		//check if the player or enemy is a undead monster
		//if they are. Give them the special passive ability
		InspiringPresence ip;
		if (playerUndead)
			player.addAbility(ip);
		if (enemyUndead)
			enemy.addAbility(ip);
	}
	//check if it is dark w/o a  full moon
	if (timeOfDay == 2)
	{
		//check if the player or enemy is a vampire monster
		//if they are. Give them the special passive ability
		SoothingDarkness sd;
		if (playerVamp)
			player.addAbility(sd);
		if (enemyVamp)
			enemy.addAbility(sd);
	}
	//check if there is a full moon
	else if (timeOfDay == 3)
	{
		BloodFrenzy bf;
		if (playerWerewolf)
			player.addAbility(bf);
		if (enemyWerewolf)
			enemy.addAbility(bf);
	}

	//display a message to the player to tell them where and when the battle is taking place
	if (timeOfDay == 1 && location == 1)
	{
		cout << "The setting sun illuminates the forest ground empowering treant monsters in battle\n";
	}
	else if (timeOfDay == 1 && location == 2)
	{
		cout << "The graveyard dimmly lights up as the sun sets in the distance. Undead monsters in this area become empowered\n";
	}
	else if (timeOfDay == 1 && location == 3)
	{
		cout << "The setting sun dimmly lights the abandoned town. No monsters are empowered\n";
	}
	if (timeOfDay == 2 && location == 1)
	{
		cout << "The dark sky above creates an uneasy feeling as you enter the forest. Vampire and treant units are empowered\n";
	}
	else if (timeOfDay == 2 && location == 2)
	{
		cout << "The moonless night casts no shadows on the tombstones in the graveyard. Vampire and undead units become empowered\n";
	}
	else if (timeOfDay == 2 && location == 3)
		cout << "The dark sky makes the abandoned town lifeless, spooking even the scariest monsters! Vampire monsters are empowered\n";
	if (timeOfDay == 3 && location == 1)
	{
		cout << "The full moon illuminates the forest floor, casting spooky shadows. Werewolf and treant monsters are empowered\n";
	}
	else if (timeOfDay == 3 && location == 2)
	{
		cout << "The full moon casts shadows on the tomestones in the graveyard. Werewolf and undead monsters are empowered\n";
	}
	else if (timeOfDay == 3 && location == 3)
		cout << "The abandoned town becomes lit up as the full moon casts shadows though all the buildings. Werewolf monsters are empowered\n";
}

//Allow the user select a differnt monster to battle with
void selectDiffernMonster(BST& playerMonsters, Monster*& currentMonster)
{
	//create a temp to hold the current monster
	Monster* temp = currentMonster;
	string name;

	//check if they have monsters
	if (playerMonsters.IsEmpty())
	{
		cout << "You have no monsters to select\n\n\n";
	}
	else
	{
		//display all the monsters the user has
		playerMonsters.Display();

		cout << "Enter the name of the monster you want to change to\n";
		cin >> name; cin.ignore(256, '\n');

		//call the find function of the BST to see if the monster is there. 
		currentMonster = playerMonsters.Get(name);

		//check if the monster was valid
		if (!currentMonster)
		{
			//tell user the monster was not valid
			cout << "There are no monster in your collection with that name\n\n";
			currentMonster = temp;
		}
		else
			cout << "New monster was selected!\n\n";
	}
}