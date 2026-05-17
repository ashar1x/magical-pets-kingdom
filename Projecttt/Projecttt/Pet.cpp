#include"Pet.h"

Pet::Pet()
{
    totalHealth = health = attackPower = defense = speed = level = 0;
    abilityReady = 1;

}

Pet::Pet(float health, float attackPower, float defense, float speed, int level)
{
    this->health = health;
    this->totalHealth = health;
    this->attackPower = attackPower;
    this->defense = defense;
    this->speed = speed;
    this->level = level;
    this->abilityReady = true;
    this->attackReady = true;
}

//copy constructor
Pet::Pet(const Pet& other) {


    health = other.health;
    totalHealth = other.totalHealth;
    defense = other.defense;
    attackPower = other.attackPower;
    level = other.level;
    speed = other.speed;
    abilityReady = other.abilityReady;
    attackReady = other.attackReady;

}

void Pet::levelUp() {
    level++;
}

void Pet::trainAttack()
{
    cout << "Trained Attack\n";
    attackPower += 0.5;
}

void Pet::trainSpeed() {

    cout << "Trained Speed\n";
    speed -= 0.05;
}

void Pet::trainDefense() {
    cout << "Trained Defense\n";
    defense++;
}

void Pet::trainHealth() {
    cout << "Trained Health\n";
    health += 5;
}

void Pet::operator=(const Pet& other) {

    health = other.health;
    defense = other.defense;
    attackPower = other.attackPower;
    level = other.level;
    speed = other.speed;
    totalHealth = other.totalHealth;

}

bool Pet::operator==(const Pet& other) {
    bool flag = true;
    if (attackPower != other.attackPower || health != other.health ||
        defense != other.defense || speed != other.speed || level != other.level) {
        flag = false;
    }

    return flag;

}

int Pet::takeDamage(int attackPower) {
    this->health -= attackPower - this->defense;

    return attackPower - this->defense;
}

void Pet::getStunned() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void Pet::getHealed(int heal) {
    health += heal;
}

void Pet::getShield(int shield) {

    defense += shield;

    cout << "Defense: " << defense << endl;

}

void Pet::getBuff(float scale) {

    health += scale * health;
    defense += scale * defense;
    attackPower += scale * attackPower;
    speed -= scale * speed;

}

void Pet::attack(Pet& enemyPet) {

    enemyPet.takeDamage(attackPower);

    attackReady = false;

    this_thread::sleep_for(std::chrono::duration<float>(speed));

    attackReady = true;

}

bool Pet::isAlive() {

    if (health > 0) {
        return true;
    }

    return false;

}

void Pet::trackAbility() {

    abilityReady = false;

    this_thread::sleep_for(std::chrono::seconds(7));

    abilityReady = true;

}

void Pet::resurrect() {

    health = totalHealth;

}


