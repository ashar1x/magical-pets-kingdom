#include"Phoenix.h"

Phoenix::Phoenix() : Pet( 100, 20, 7, 4.5)
{
	totalHealth = 100;
}

//heal yourself or a teammate
void Phoenix::flameHealing(Pet& friendPet)
{
	friendPet.getHealed(attackPower); //heals as per its attack power
}

//gets health back to 100 instead of overPowered trained health
void Phoenix::rebirth() {
		this->health = totalHealth;
		ableToRevive = false;
}

//0 for flameHealing, 1 for rebirth
//add visuals
void Phoenix::useAbility(bool ability, Pet& enemyPet)  {

	if (ableToRevive) {
		thread T(&Phoenix::trackAbility, this);
		T.detach();
	}

	if (ability == 0)
	{
		flameHealing(enemyPet);
	}
	else 
	{
		if(ableToRevive)
		rebirth();
	}
}

Pet* Phoenix::clone() const {
	return new Phoenix(*this);
}
