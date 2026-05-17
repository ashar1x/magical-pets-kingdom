#include "Player.h"
#include "Guild.h"
#include "Item.h"

Player::Player() {
	name = "null";
	currency = 0;
	guild = nullptr;
	noOfBuffs = 0;
	noOfShields = 0;
	noOfHealingPotions = 0;
}

Player::Player(std::string name) {
	this->name = std::move(name);
	currency = 0;
	guild = nullptr;
	noOfBuffs = 0;
	noOfHealingPotions = 0;
	noOfShields = 0;
	noOfStaminas = 0;
}

Player::~Player() {
	if (guild) {
		delete guild;
	}
}

Player::Player(const Player& other) {
	name = other.name;
	currency = other.currency;
	noOfBuffs = other.noOfBuffs;
	noOfHealingPotions = other.noOfHealingPotions;
	noOfShields = other.noOfShields;
	noOfStaminas = other.noOfStaminas;
	guild = other.guild; // Consider deep copy if needed

	for (const auto& pet : other.pets) {
		pets.push_back(std::unique_ptr<Pet>(pet->clone()));
	}
}

Player& Player::operator=(const Player& other) {
	if (this != &other) {
		name = other.name;
		currency = other.currency;
		noOfBuffs = other.noOfBuffs;
		noOfHealingPotions = other.noOfHealingPotions;
		noOfShields = other.noOfShields;
		noOfStaminas = other.noOfStaminas;
		guild = other.guild; // Consider deep copy if needed

		pets.clear();
		for (const auto& pet : other.pets) {
			pets.push_back(std::unique_ptr<Pet>(pet->clone()));
		}
	}
	return *this;
}

bool Player::operator==(const Player& other) const {
	return name == other.name && currency == other.currency && pets.size() == other.pets.size();
}

void Player::addPet(std::unique_ptr<Pet> newPet) {
	pets.push_back(std::move(newPet));
}

void Player::removePet(const Pet& petToRemove) {
	auto it = std::remove_if(pets.begin(), pets.end(), [&](const std::unique_ptr<Pet>& p) {
		return *p == petToRemove;
		});
	pets.erase(it, pets.end());
}

void Player::joinGuild() {
	if (guild) {
		guild->addMember(*this);
	}
}

void Player::leaveGuild() {
	if (guild) {
		guild->removeMember(*this);
	}
}

void Player::buyItem(std::string itemName) {
	if (currency >= Item::getPrice()) {
		if (itemName == "HealingPotion") {
			noOfHealingPotions++;
		}
		else if (itemName == "Buff") {
			noOfBuffs++;
		}
		else if (itemName == "Shield") {
			noOfShields++;
		}
		else if (itemName == "Stamina") {
			noOfStaminas++;
		}
		currency -= Item::getPrice();
	}
}

void Player::useItem(Pet& enemyPet, std::string itemName) {
	if (itemName == "HealingPotion" && noOfHealingPotions > 0) {
		Item::use(enemyPet, itemName);
		noOfHealingPotions--;
	}
	else if (itemName == "Buff" && noOfBuffs > 0) {
		Item::use(enemyPet, itemName);
		noOfBuffs--;
	}
	else if (itemName == "Shield" && noOfShields > 0) {
		cout << "Inside Player to use Shields\n";
		Item::use(enemyPet, itemName);
		noOfShields--;
	}
	else if (itemName == "Stamina" && noOfStaminas > 0) {
		Item::use(enemyPet, itemName);
		noOfStaminas--;
	}
}

void Player::win() {
	currency += 500;
	for (auto& pet : pets) {
		pet->levelUp();
	}
}

void Player::endBattle() {
	for (auto& pet : pets) {
		pet->resurrect();
	}
}

int Player::getItemCount(string name) {
	if (name == "HealingPotion")
		return noOfHealingPotions;
	else if (name == "Buff")
		return noOfBuffs;
	else if (name == "Shield")
		return noOfShields;
	else if (name == "Stamina")
		return noOfStaminas;

	return 0;
}