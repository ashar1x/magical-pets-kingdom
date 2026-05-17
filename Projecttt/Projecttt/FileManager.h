//#pragma once
//#include <fstream>
//#include <string>
//#include "GameManager.h"
//#include "Player.h"
//#include "Pet.h"
//
//class FileManager {
//public:
//    static bool userExists(const std::string& username) {
//        std::ifstream file("users.txt");
//        std::string line;
//        while (std::getline(file, line)) {
//            if (line == username) return true;
//        }
//        return false;
//    }
//
//    static void addUser(const std::string& username) {
//        std::ofstream file("users.txt", std::ios::app);
//        file << username << std::endl;
//    }
//
//    static void savePlayerData(const Player& player) {
//        std::ofstream file(player.getName() + ".dat");
//        file << player.getName() << std::endl;
//        file << player.getCurrency() << std::endl;
//        file << player.getHealingPotions() << " "
//            << player.getBuffs() << " "
//            << player.getShields() << " "
//            << player.getStaminas() << std::endl;
//
//        file << player.pets.size() << std::endl;
//        for (const auto& pet : player.pets) {
//            file << static_cast<int>(pet->getType()) << " "
//                << pet->getHealth() << " "
//                << pet->getAttack() << " "
//                << pet->getDefense() << " "
//                << pet->getSpeed() << " "
//                << pet->getLevel() << " "
//                << pet->isAbilityReady() << " "
//                << pet->isAttackReady() << std::endl;
//        }
//    }
//
//    static bool loadPlayerData(const std::string& username, Player& player) {
//        std::ifstream file(username + ".dat");
//        if (!file.is_open()) return false;
//
//        std::string name;
//        std::getline(file, name);
//        player = Player(name);
//
//        int currency;
//        file >> currency;
//        player.setCurrency(currency);
//
//        int hp, b, s, st;
//        file >> hp >> b >> s >> st;
//        player.setHealingPotions(hp);
//        player.setBuffs(b);
//        player.setShields(s);
//        player.setStaminas(st);
//
//        int numPets;
//        file >> numPets;
//        for (int i = 0; i < numPets; ++i) {
//            int type, health, attack, defense, level;
//            float speed;
//            bool abilityReady, attackReady;
//            file >> type >> health >> attack >> defense >> speed >> level >> abilityReady >> attackReady;
//
//            std::unique_ptr<Pet> pet;
//            switch (static_cast<PetType>(type)) {
//            case DRAGON: pet = std::make_unique<Dragon>(); break;
//            case PHOENIX: pet = std::make_unique<Phoenix>(); break;
//            case UNICORN: pet = std::make_unique<Unicorn>(); break;
//            case GRIFFIN: pet = std::make_unique<Griffin>(); break;
//            default: continue;
//            }
//
//            pet->setHealth(health);
//            pet->setAttackPower(attack);
//            pet->setDefense(defense);
//            pet->setSpeed(speed);
//            pet->setLevel(level);
//            pet->setAbilityReady(abilityReady);
//            pet->setAttackReady(attackReady);
//
//            player.addPet(std::move(pet));
//        }
//
//        return true;
//    }
//};