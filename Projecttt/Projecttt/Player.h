#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <memory>
#include "Pet.h"

class Guild;

class Player {
private:
    std::string name;
    int currency;
    std::vector<std::unique_ptr<Pet>> pets;
    Guild* guild;
    int noOfHealingPotions;
    int noOfBuffs;
    int noOfShields;
    int noOfStaminas;

public:
    Player();
    Player(std::string name);
    ~Player();
    Player(const Player& other);
    Player& operator=(const Player& other);
    bool operator==(const Player& other) const;

    Pet& getPet(int n) {
        if (n < 0 || n >= static_cast<int>(pets.size())) {
            std::cerr << "getPet: Invalid index " << n << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return *pets[n];
    }

    void addPet(std::unique_ptr<Pet> newPet);
    void removePet(const Pet& petToRemove);
    void joinGuild();
    void leaveGuild();
    void buyItem(std::string itemName);
    void useItem(Pet& enemyPet, std::string itemName);
    int getItemCount(string name);
    void endBattle();
    void win();

	// Getters
	int getCurrency() const { return currency; }
	int getHealingPotions() const { return noOfHealingPotions; }
	int getBuffs() const { return noOfBuffs; }
	int getShields() const { return noOfShields; }
	int getStaminas() const { return noOfStaminas; }

	// Setters
	void setCurrency(int c) { currency = c; }
	void setHealingPotions(int hp) { noOfHealingPotions = hp; }
	void setBuffs(int b) { noOfBuffs = b; }
	void setShields(int s) { noOfShields = s; }
	void setStaminas(int st) { noOfStaminas = st; }
};

#endif
