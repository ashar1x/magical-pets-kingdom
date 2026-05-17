#ifndef GRIFFIN_H
#define GRIFFIN_H
#include"Pet.h"
#include<thread>
#include<functional>
#include<string>


class Griffin : public Pet {
private:
	int clawStrike(Pet& enemyPet);
	void diveBomb(Pet& enemyPet);
public:
	Griffin();
	Pet* clone() const override;

    //PetType getType() const override { return GRIFFIN; } // Use appropriate type for each

	void useAbility(bool ability, Pet& enemyPet);
};


#endif
