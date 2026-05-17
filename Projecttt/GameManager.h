#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include"Player.h"
#include"Dragon.h"
#include"Phoenix.h"
#include"Griffin.h"
#include"Unicorn.h"
#include"Pet.h"
#include"FileManager.h"

class GameManager {
private:

public:
	Player* player;
	Dragon* dragon;
	Griffin* griffin;
	Unicorn* unicorn;
	Phoenix* phoenix;
	GameManager();
	~GameManager();
	void createNewPlayer(string userName);
	/*void saveGame();
	bool loadGame(const string& userName);*/
	void startBattle(int pvp);
	void setup1v1Match(int pet, int enemyPet, atomic<bool>& isBattleOver);
	void setup2v2Match();
	void setupGuildWar();
	void openShop();

};


#endif