#include"Item.h"

float Item::scaleBuff = 0.3;
int Item::scaleHeal = 30;
int Item::scaleShield = 5;
int Item::price = 500;

Item::Item()
{

	name = "null";
	description = "null";
	price = -1;

}

Item::Item(string name, string desc, int price) {

	this->name = name;
	description = desc;
	this->price = price;

}

void Item::use(Pet& pet, string name) {

	if (name == "HealingPotion") {
		heal(pet);
	}
	else if (name == "Buff") {
		buff(pet);
	}
	else if (name == "Shield") {
		shield(pet);
	}
	else if (name == "Stamina") {

	}

	else return;

}

int Item::getPrice() {

	return price;

}

void Item::heal(Pet& pet) {
	pet.getHealed(scaleHeal);
}

void Item::shield(Pet& pet) {
	pet.getShield(scaleShield);
	this_thread::sleep_for(std::chrono::seconds(10));
	pet.getShield(-scaleShield);
}

void Item::buff(Pet& pet) {

	cout << "Inside Item\n";
	pet.getBuff(scaleBuff);
	this_thread::sleep_for(std::chrono::seconds(10));
	pet.getBuff(-scaleBuff);

}

void Item::stamina(Pet& pet) {

	pet.getStaminized();

}

//bool Item::operator==(const Item& other) {
//
//	if (name != other.name || description != other.description) {
//		return false;
//	}
//
//	return true;
//
//}

