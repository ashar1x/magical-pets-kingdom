#include"Griffin.h"

Griffin::Griffin() : Pet( 100, 20, 5, 4) 
{

}

int Griffin::clawStrike(Pet& enemyPet)
{
	return enemyPet.takeDamage(attackPower);
}

void Griffin::diveBomb(Pet& enemyPet)
{
	//using multithreading
	thread t(&Pet::getStunned, &enemyPet); //stunned for 5 seconds.
	t.detach();
}

//0 for clawStrike, 1 for diveBomb
void Griffin::useAbility(bool ability, Pet& enemyPet) {

	thread T(&Griffin::trackAbility, this);
	T.detach();

	if (ability == 0) 
	{
		clawStrike(enemyPet);
	}
	else 
	{
		diveBomb(enemyPet);
	}
}

Pet* Griffin::clone() const {
	return new Griffin(*this);
}

