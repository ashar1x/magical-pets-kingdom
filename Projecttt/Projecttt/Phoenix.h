#ifndef PHOENIX_H
#define PHOENIX_H
#include"Pet.h"
class Phoenix : public Pet {
private:
	int totalHealth;
	bool ableToRevive = true;
	void flameHealing(Pet& enemyPet);
	void rebirth();
public:
	Phoenix();
	Pet* clone() const override;

	bool getIsAbleToRevive() { return ableToRevive; }

    //PetType getType() const override { return PHOENIX; } // Use appropriate type for each

	void useAbility(bool ability, Pet& enemyPet);
};

//Phoenix::Phoenix(string& name) : Pet(name, 100, 20, 7, 4.5) {
//	totalHealth = 100;
//}
//
////heal yourself or a teammate
//void Phoenix::flameHealing(Pet& friendPet) {
//	friendPet.getHealed(attackPower); //heals as per its attack power
//}
//
////gets health back to 100 instead of overPowered trained health
//void Phoenix::rebirth() {
//	this->health = totalHealth;
//}
//
////0 for flameHealing, 1 for rebirth
////add visuals
//void Phoenix::useAbility(bool ability, Pet& enemyPet) {
//
//	thread T(&Phoenix::trackAbility, this);
//	T.detach();
//
//	if (ability == 0) {
//		flameHealing(enemyPet);
//	}
//	else {
//		rebirth();
//	}
//}


#endif
