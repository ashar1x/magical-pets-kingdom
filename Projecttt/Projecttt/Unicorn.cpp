#include"Unicorn.h"

void Unicorn::speedBurst() {
	float increase = speed * 0.3;
	speed -= increase;
	this_thread::sleep_for(std::chrono::seconds(5));
	speed += increase;
}

void Unicorn::magicShield() {
	int increase = defense * 2;
	defense += increase;
	this_thread::sleep_for(std::chrono::seconds(3));
	defense -= increase;
}

//0 for speedBurst, 1 for magicShield
//add visuals
void Unicorn::useAbility(bool ability, Pet& enemyPet) {

	thread T(&Unicorn::trackAbility, this);
	T.detach();

	if (ability == 0) {
		thread t(&Unicorn::speedBurst, this);
		t.detach();
	}
	else {
		thread t(&Unicorn::magicShield, this);
		t.detach();
	}
}

Unicorn::Unicorn() : Pet( 80, 20, 5, 3.5) {

}

Pet* Unicorn::clone() const{
	return new Unicorn(*this);
}
