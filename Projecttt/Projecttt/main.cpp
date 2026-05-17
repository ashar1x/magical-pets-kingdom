
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include"Dragon.h"
#include"GameManager.h"
#include"Griffin.h"
#include"Guild.h"
#include"Item.h"
#include"menus.h"
#include"Pet.h"
#include"Phoenix.h"
#include"Player.h"
#include"Shop.h"
#include"train.h"
#include"Unicorn.h"
#include"ArenaBattleScreen.h" // Include the new header

PetType selectedPetType = DRAGON; // Default
PetType arenaSelectedPets[4] = { DRAGON, PHOENIX, UNICORN, GRIFFIN }; // Default selected pets for arena
PetType arenaSelectedEnemies[4] = { UNICORN, GRIFFIN, DRAGON, PHOENIX }; // Default selected pets for arena
int arenaSelectedPetCount = 0; // Number of selected pets
shopScreen* ShopScreen = nullptr;

// Add flags to track user's intention to return from screens
// At the top with your other state variables
bool returnFromArena1v1 = false;
bool returnFromArena2v2 = false;
bool returnFromArena4v4 = false;
bool returnFromArenaBattle = false;

// Separate transition flags for each direction
bool transitioningToMainMenu = false;
bool transitioningFromMainMenu = false;

bool isTransitioning = false;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Magical Pets Kingdom");
	GameState currentState = STATE_MAIN_MENU;
	GameState previousState = STATE_MAIN_MENU; // Track previous state

	// Global flags for screen control
	bool back = false;         // For training screen
	bool backFromArena = false;  // For arena pet selection screens

	MainMenu mainMenu(window);
	ModeSelectMenu modeMenu(window);
	ArenaMenu arenaMenu(window);
	GuildMenu guildMenu(window);
	TrainMenu trainMenu(window);
	TrainingScreen* trainingScreen = nullptr;
	ArenaPetSelect* arenaPetSelect1v1 = nullptr;
	ArenaPetSelect* arenaPetSelect2v2 = nullptr;
	ArenaPetSelect* arenaPetSelect4v4 = nullptr;
	ArenaBattleScreen* arenaBattleScreen = nullptr;

	while (window.isOpen())
	{

		// Store previous state before transitions
		previousState = currentState;
		cout << "current state: " << currentState << endl;
		switch (currentState)
		{
			// In main.cpp, modify the main loop:
		case STATE_MAIN_MENU:
			// Reset all return flags when at main menu
			returnFromArena1v1 = false;
			returnFromArena2v2 = false;
			returnFromArena4v4 = false;
			returnFromArenaBattle = false;

			// Reset transition flags when arriving from another state
			if (previousState != STATE_MAIN_MENU) {
				mainMenu.reset();
				transitioningToMainMenu = false;
				transitioningFromMainMenu = false;
			}

			mainMenu.handleInput();
			mainMenu.draw();

			// Check if there's a state change request from main menu
			if (!transitioningFromMainMenu && mainMenu.nextState != STATE_MAIN_MENU) {
				transitioningFromMainMenu = true;
				currentState = mainMenu.nextState;
			}
			break;

		case STATE_MODE_SELECT:
			// Reset transition flags when arriving from another state
			if (previousState != STATE_MODE_SELECT) {
				modeMenu.reset();
				transitioningToMainMenu = false;
				transitioningFromMainMenu = false;
			}

			modeMenu.handleInput();
			modeMenu.draw();

			// Check if there's a state change request from mode select menu
			if (!transitioningToMainMenu && modeMenu.nextState != STATE_MODE_SELECT) {
				if (modeMenu.nextState == STATE_MAIN_MENU) {
					transitioningToMainMenu = true;
				}
				currentState = modeMenu.nextState;
			}
			break;

		case STATE_TRAIN:
			trainMenu.handleInput();
			trainMenu.draw();
			currentState = trainMenu.nextState;
			break;

		case STATE_ARENA:
			// If we're coming from the battle screen, make sure the arena menu is reset
			if (previousState == STATE_ARENA_BATTLE) {
				std::cout << "Resetting arena menu after battle" << std::endl;
				arenaMenu.reset();
				returnFromArenaBattle = false;
			}

			// Also reset flags when coming from selection screens
			if (returnFromArena1v1) {
				returnFromArena1v1 = false;
			}

			if (returnFromArena2v2) {
				returnFromArena2v2 = false;
			}

			if (returnFromArena4v4) {
				returnFromArena4v4 = false;
			}
			arenaMenu.handleInput();
			arenaMenu.draw();

			// Check if state has changed
			if (arenaMenu.nextState != STATE_ARENA) {
				std::cout << "Arena menu changing state to: " << arenaMenu.nextState << std::endl;
				currentState = arenaMenu.nextState;
			}
			break;

		case STATE_GUILD:
			guildMenu.handleInput();
			guildMenu.draw();
			currentState = guildMenu.nextState;
			break;

		case STATE_GAME:
			// Game logic here
			currentState = STATE_MAIN_MENU;
			break;

		case STATE_TRAINING:
		{
			if (!trainingScreen) {
				std::cout << "Creating training screen for pet type: " << selectedPetType << std::endl;
				trainingScreen = new TrainingScreen(window, selectedPetType);
			}

			trainingScreen->handleInput();
			trainingScreen->update();
			trainingScreen->draw();

			// Check if state has changed
			if (trainingScreen->nextState != STATE_TRAINING) {
				currentState = trainingScreen->nextState;
				delete trainingScreen;
				trainingScreen = nullptr;
			}
			break;
		}

		case STATE_ARENA_SELECT_1V1:
		{
			if (!arenaPetSelect1v1) {
				std::cout << "Creating 1v1 pet select screen\n";
				arenaPetSelect1v1 = new ArenaPetSelect(window, 1, STATE_ARENA_SELECT_1V1);
			}

			arenaPetSelect1v1->handleInput();
			arenaPetSelect1v1->draw();

			// Check if state has changed
			if (arenaPetSelect1v1->nextState != STATE_ARENA_SELECT_1V1) {
				if (arenaPetSelect1v1->nextState == STATE_GAME) {
					// Get selected pets from the pet select screen
					arenaSelectedPetCount = 1;
					arenaSelectedPets[0] = (PetType)arenaPetSelect1v1->getSelectedPet(0);

					// Redirect to arena battle instead of game
					currentState = STATE_ARENA_BATTLE;
				}
				else if (arenaPetSelect1v1->nextState == STATE_ARENA) {
					// User wants to go back - set the flag
					returnFromArena1v1 = true;
					currentState = STATE_ARENA;
					std::cout << "Setting return flag from 1v1 screen" << std::endl;
				}
				else {
					currentState = arenaPetSelect1v1->nextState;
				}
				std::cout << "Exiting 1v1 pet select, going to state: " << currentState << std::endl;
				delete arenaPetSelect1v1;
				arenaPetSelect1v1 = nullptr;
			}
			break;
		}

		case STATE_ARENA_SELECT_2V2:
		{
			if (!arenaPetSelect2v2) {
				std::cout << "Creating 2v2 pet select screen\n";
				arenaPetSelect2v2 = new ArenaPetSelect(window, 2, STATE_ARENA_SELECT_2V2);
			}

			arenaPetSelect2v2->handleInput();
			arenaPetSelect2v2->draw();

			// Check if state has changed
			if (arenaPetSelect2v2->nextState != STATE_ARENA_SELECT_2V2) {
				if (arenaPetSelect2v2->nextState == STATE_GAME) {
					// Get selected pets from the pet select screen
					arenaSelectedPetCount = 2;
					arenaSelectedPets[0] = (PetType)arenaPetSelect2v2->getSelectedPet(0);
					arenaSelectedPets[1] = (PetType)arenaPetSelect2v2->getSelectedPet(1);

					// Redirect to arena battle instead of game
					currentState = STATE_ARENA_BATTLE;
				}
				else if (arenaPetSelect2v2->nextState == STATE_ARENA) {
					// User wants to go back - set the flag
					returnFromArena2v2 = true;
					currentState = STATE_ARENA;
					std::cout << "Setting return flag from 2v2 screen" << std::endl;
				}
				else {
					currentState = arenaPetSelect2v2->nextState;
				}
				std::cout << "Exiting 2v2 pet select, going to state: " << currentState << std::endl;
				delete arenaPetSelect2v2;
				arenaPetSelect2v2 = nullptr;
			}
			break;
		}

		case STATE_ARENA_SELECT_4V4:
		{
			if (!arenaPetSelect4v4) {
				std::cout << "Creating 4v4 pet select screen\n";
				arenaPetSelect4v4 = new ArenaPetSelect(window, 4, STATE_ARENA_SELECT_4V4);
			}

			arenaPetSelect4v4->handleInput();
			arenaPetSelect4v4->draw();

			// Check if state has changed
			if (arenaPetSelect4v4->nextState != STATE_ARENA_SELECT_4V4) {
				if (arenaPetSelect4v4->nextState == STATE_GAME) {
					// Get selected pets from the pet select screen
					arenaSelectedPetCount = 4;
					arenaSelectedPets[0] = (PetType)arenaPetSelect4v4->getSelectedPet(0);
					arenaSelectedPets[1] = (PetType)arenaPetSelect4v4->getSelectedPet(1);
					arenaSelectedPets[2] = (PetType)arenaPetSelect4v4->getSelectedPet(2);
					arenaSelectedPets[3] = (PetType)arenaPetSelect4v4->getSelectedPet(3);

					// Redirect to arena battle instead of game
					currentState = STATE_ARENA_BATTLE;
				}
				else if (arenaPetSelect4v4->nextState == STATE_ARENA) {
					// User wants to go back - set the flag
					returnFromArena4v4 = true;
					currentState = STATE_ARENA;
					std::cout << "Setting return flag from 4v4 screen" << std::endl;
				}
				else {
					currentState = arenaPetSelect4v4->nextState;
				}
				std::cout << "Exiting 4v4 pet select, going to state: " << currentState << std::endl;
				delete arenaPetSelect4v4;
				arenaPetSelect4v4 = nullptr;
			}
			break;
		}


		case STATE_ARENA_BATTLE:
		{
			if (!arenaBattleScreen) {
				std::cout << "Creating arena battle screen with " << arenaSelectedPetCount << " pets\n";
				arenaBattleScreen = new ArenaBattleScreen(window, arenaSelectedPetCount, arenaSelectedPets, arenaSelectedEnemies);
			}

			arenaBattleScreen->handleInput();
			arenaBattleScreen->update();
			arenaBattleScreen->draw();

			// Check if state has changed
			if (arenaBattleScreen->nextState != STATE_ARENA_BATTLE) {
				// If returning to arena, set the flag and ensure we reset the arena menu
				if (arenaBattleScreen->nextState == STATE_ARENA) {
					returnFromArenaBattle = true;
				}
				currentState = arenaBattleScreen->nextState;
				delete arenaBattleScreen;
				arenaBattleScreen = nullptr;
			}
			break;
		}

		case STATE_SHOP:
		{
			if (!ShopScreen) {
				std::cout << "Creating shop screen\n";
				ShopScreen = new shopScreen(window);
			}

			ShopScreen->handleInput();
			ShopScreen->draw();

			// Check if state has changed (like back button pressed)
			if (ShopScreen->nextState != STATE_SHOP) {
				currentState = ShopScreen->nextState;
				delete ShopScreen;
				ShopScreen = nullptr;
			}
			break;
		}
		}
	}

	// Cleanup
	if (trainingScreen) delete trainingScreen;
	if (arenaPetSelect1v1) delete arenaPetSelect1v1;
	if (arenaPetSelect2v2) delete arenaPetSelect2v2;
	if (arenaPetSelect4v4) delete arenaPetSelect4v4;
	if (arenaBattleScreen) delete arenaBattleScreen;
	if (ShopScreen) delete ShopScreen;
	return 0;
}