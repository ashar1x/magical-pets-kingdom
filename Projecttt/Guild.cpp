#include"Guild.h"
#include<iostream>
#include"Player.h"
////////////////////////////////////////////////////////////////////////////////////////////

Guild::Guild(string name) {
	this->name = name;
	noOfMembers = 0;
	members = nullptr;
}

Guild::~Guild() {
	if (members)
		delete[] members;
}

void Guild::addMember(const Player& 
) {

	Player* temp = new Player[noOfMembers + 1];

	for (int i = 0; i < noOfMembers; i++) {
		temp[i] = members[i];
	}

	if (members)
		delete[] members;

	temp[noOfMembers] = player;

	members = temp;

	noOfMembers++;

}

void Guild::removeMember(const Player& player) {

	Player* temp = new Player[noOfMembers - 1];
	int j = 0;

	for (int i = 0; i < noOfMembers; i++) {
		if (!(members[i] == player)) {
			temp[j] = members[i];
			j++;
		}
	}

	if (members)
		delete[] members;

	members = temp;

	noOfMembers--;

}


