#ifndef GUILD_H
#define GUILD_H

#include"Player.h"
#include<iostream>

class Guild {
private:
	string name;
	Player* members;
	int noOfMembers;
public:
	Guild(string name);
	~Guild();
	void addMember(const Player& player);
	void removeMember(const Player& player);
};



#endif