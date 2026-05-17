
#include"GameManager.h"

GameManager::GameManager() {
	std::cout << "player bangaya?\n";
	player = nullptr;
	dragon = nullptr;
	griffin = nullptr;
	unicorn = nullptr;
	phoenix = nullptr;
}

GameManager::~GameManager() {
	if (player)
		delete player;
	if (griffin)
		delete griffin;
	if (dragon)
		delete dragon;
	if (unicorn)
		delete unicorn;
	if (phoenix)
		delete phoenix;
}

void GameManager::createNewPlayer(string userName) {

	std::cout << "player ka naam rakhdiya hai " << userName << endl;
	player = new Player(userName);

	griffin = new Griffin();

	dragon = new Dragon();

	phoenix = new Phoenix();

	unicorn = new Unicorn();

}

void GameManager::startBattle(int pvp) {

	if (pvp == 1) {

	}
	else if (pvp == 2) {

	}
	else if (pvp == 4) {

	}

}

void GameManager::setup1v1Match(int pet, int enemyPet, atomic<bool>& isBattleOver) {
	
	std::cout << "Setting up 1v1 match" << std::endl;

}

void GameManager::setup2v2Match() {
	// Dummy function for 2v2 setup
	std::cout << "Setting up 2v2 match" << std::endl;
}

void GameManager::setupGuildWar() {
	// Dummy function for guild war setup
	std::cout << "Setting up guild war" << std::endl;
}

void GameManager::openShop() {
	// Dummy function for shop
	std::cout << "Opening shop" << std::endl;
}

