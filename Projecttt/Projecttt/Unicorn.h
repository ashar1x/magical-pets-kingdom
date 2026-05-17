#ifndef UNICORN_H
#define UNICORN_H
#include"Pet.h"
class Unicorn : public Pet {
private:
	void speedBurst();
	void magicShield();
public:
	Unicorn();
	Pet* clone() const override;
	void useAbility(bool ability, Pet& enemyPet);
};

#endif
