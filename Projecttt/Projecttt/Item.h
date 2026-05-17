#ifndef ITEM_H
#define ITEM_H

#include"Pet.h"

class Item {
private:
	string name;
	string description;
	static int scaleShield;
	static int scaleHeal;
	static float scaleBuff;
	static int price;
	static void heal(Pet& pet);
	static void shield(Pet& pet);
	static void buff(Pet& pet);
	static void stamina(Pet& pet);
public:
	Item();
	Item(string name, string desc, int price);
	//bool operator==(const Item& other);
	static void use(Pet& pet, string name);
	static int getPrice();
};



#endif
