#pragma once
#ifndef DRAGON_H
#define DRAGON_H
#include"Pet.h"
#include<functional>
#include<string>

class Dragon : public Pet {
private:
	int fireballAttack(Pet& enemyPet);
	void dragonsRoar(Pet& enemyPet);
public:
	Dragon();
	Pet* clone() const override;

    //PetType getType() const override { return DRAGON; } 
	void useAbility(bool ability, Pet& enemyPet);
};

//Dragon::Dragon(string& name) : Pet(name, 100, 25, 3, 3.75) {
//
//}
//
////pass in the attacked pet by reference
//int Dragon::fireballAttack(Pet& enemyPet) {
//	int r = (enemyPet.takeDamage(attackPower));
//	return r;
//}
//
//void Dragon::dragonsRoar(Pet& enemyPet) {
//	//using multithreading
//	thread t(&Pet::getStunned, &enemyPet); //stunned for 5 seconds.
//	t.detach();
//}
//
////0 for fireballAttack, 1 for dragonsRoar
////add visuals
//string Dragon::useAbility(bool ability, Pet& enemyPet) {
//
//	thread T(&Dragon::trackAbility, this);
//	T.detach();
//
//	if (ability == 0) {
//		string returnStr = "Hit " + to_string(fireballAttack(enemyPet));
//		return returnStr;
//	}
//	else {
//		dragonsRoar(enemyPet);
//		return "Stunned";
//	}
//}


#endif
