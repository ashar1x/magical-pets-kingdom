#include"Dragon.h"

Dragon::Dragon() : Pet( 100, 25, 3, 3.75) {

}

//pass in the attacked pet by reference
int Dragon::fireballAttack(Pet& enemyPet) {
	int r = (enemyPet.takeDamage(attackPower));
	return r;
}

void Dragon::dragonsRoar(Pet& enemyPet) {
	//using multithreading
	thread t(&Pet::getStunned, &enemyPet); //stunned for 5 seconds.
	t.detach();
}

//0 for fireballAttack, 1 for dragonsRoar
//add visuals
void Dragon::useAbility(bool ability, Pet& enemyPet)  {

	cout << "Hello ji inside the ability\n";

	thread T(&Dragon::trackAbility, this);
	T.detach();

	if (ability == 0) {
		fireballAttack(enemyPet);
	}
	else {
		dragonsRoar(enemyPet);
	}
}

Pet* Dragon::clone() const {
	return new Dragon(*this);
}

