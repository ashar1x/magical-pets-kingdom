#ifndef PET_H
#define PET_H

#include<iostream>
#include<cstdlib>
#include<thread>
#include<chrono>
#include<functional>
using namespace std;

//forward declarations
class Dragon;
class Griffin;
class Unicorn;
class Phoenix;

class Pet {
protected:
    int health;
    int totalHealth;
    int attackPower;
    int defense;
    float speed;
    int level;
    bool abilityReady;
    bool attackReady;
    void getShield(int shield);
    void getBuff(float scale);
public:
    Pet();
    Pet(float health, float attackPower, float defense, float speed, int level = 1);
    Pet(const Pet& other);

    void setHealth(int h) { health = h; }
    void setAttackPower(int ap) { attackPower = ap; }
    void setDefense(int d) { defense = d; }
    void setSpeed(float s) { speed = s; }
    void setLevel(int l) { level = l; }
    void setAbilityReady(bool ar) { abilityReady = ar; }
    void setAttackReady(bool atk) { attackReady = atk; }
    void getStaminized() { abilityReady = true; }

    int getTotalHealth() { return totalHealth; }
    float getHealth() { cout << "HealthGetted\n"; return health; }
    float getAttack() { return attackPower; }
    float getDefense() { return defense; }
    float getSpeed() { return speed; }
    void levelUp();
    void trainHealth();
    void trainSpeed();
    void trainDefense();
    void trainAttack();
    int takeDamage(int attackPower);
    void operator=(const Pet& other);
    bool operator==(const Pet& other);
    void getStunned();
    void getHealed(int heal);
    void attack(Pet& enemyPet);
    bool isAlive();
    void trackAbility();
    virtual void useAbility(bool ability, Pet& enemyPet) = 0;
    virtual Pet* clone() const = 0;
    bool isAbilityReady() { return abilityReady; }
    bool isAttackReady() { return attackReady; }
    void resurrect();
    friend class Item;
};

#endif