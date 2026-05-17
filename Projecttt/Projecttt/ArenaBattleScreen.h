// #pragma once
// #include <SFML/Graphics.hpp>
// #include "menus.h"

// // Maximum number of selectable pets
// const int MAX_SELECTABLE_PETS = 2;

// extern GameManager gamemanager; 

// class ArenaBattleScreen {
// private:
//     sf::RenderWindow& window;
//     sf::Texture bgTexture;
//     sf::Sprite background;

//     int petCount;  // Number of pets selected
//     int activePet;
//     PetType selectedPets[MAX_SELECTABLE_PETS];  // Store selected pet types
//     PetType selectedEnemyPets[MAX_SELECTABLE_PETS];  // Store selected pet types
//     sf::Sprite petSprites[MAX_SELECTABLE_PETS];  // Sprites for selected pets
//     sf::Sprite enemySprites[MAX_SELECTABLE_PETS];  // Sprites for selected pets
//     bool petOnBattlefield[MAX_SELECTABLE_PETS];  // Whether pet is on battlefield (left side)

//     sf::Texture petTextures[4]; // DRAGON, PHOENIX, UNICORN, GRIFFIN

//     sf::Texture buttonTex;
//     sf::Sprite backButton;

//     atomic<bool> isBattleOver;

    

    
// public:
//     GameState nextState = STATE_ARENA_BATTLE;

//     ArenaBattleScreen(sf::RenderWindow& win, int numPets, PetType* pets, PetType* enemyPets)
//         : window(win), petCount(numPets) {

//         activePet = 0;

//         window.setFramerateLimit(60); // Cap at 60 FPS

//         isBattleOver.store(false);

//         // Copy selected pets
//         for (int i = 0; i < petCount && i < MAX_SELECTABLE_PETS; i++) {
//             selectedPets[i] = pets[i];

//             selectedEnemyPets[i] = enemyPets[i];

//             petOnBattlefield[i] = false;  // Initially on right side
//         }

//         // Load background
//         if (!bgTexture.loadFromFile("backgrounds/arena_bg.png")) {
//             std::cerr << "Failed to load arena background texture!" << std::endl;
//         }
//         background.setTexture(bgTexture);
//         background.setScale(
//             1280.0f / background.getLocalBounds().width,
//             720.0f / background.getLocalBounds().height
//         );

//         // Load pet textures
//         std::string texturePaths[] = {
//             "textures/dragon.png",
//             "textures/pheonix.png",
//             "textures/unicorn.png",
//             "textures/griffin.png"
//         };

//         for (int i = 0; i < 4; i++) {
//             if (!petTextures[i].loadFromFile(texturePaths[i])) {
//                 std::cerr << "Failed to load texture: " << texturePaths[i] << std::endl;
//             }
//         }

//         // Setup enemy pet sprites
//         for (int i = 0; i < petCount; i++) {
//             enemySprites[i].setTexture(petTextures[selectedPets[i]]);

//             // Scale sprites to appropriate size
//             float scale = 0.6f;  // Adjust as needed   
//             enemySprites[i].setScale(scale, scale);

//             enemySprites->setColor(sf::Color(255, 150, 150, 255));
            

//             // Position on right side initially, evenly spaced
//             float rightSideX = 800;  // Adjust as needed
//             float spacing = 720.0f / (petCount + 1);
//             enemySprites[i].setPosition(rightSideX, (i + 1) * spacing);
//         }

//         // Setup pet sprites
//         for (int i = 0; i < petCount; i++) {
//             petSprites[i].setTexture(petTextures[selectedPets[i]]);

//             // Scale sprites to appropriate size
//             float scale = 0.6f;  // Adjust as needed
//             petSprites[i].setScale(scale, scale);

//             // Position on right side initially, evenly spaced
//             float leftSideX = 200;  // Adjust as needed
//             float spacing = 720.0f / (petCount + 1);
//             petSprites[i].setPosition(leftSideX, (i + 1) * spacing);
//         }

        




//         // Load back button
//         if (!buttonTex.loadFromFile("textures/back.png")) {
//             std::cerr << "Failed to load back button texture!" << std::endl;
//         }
//         backButton.setTexture(buttonTex);
//         backButton.setPosition(20, 20);
//         backButton.setScale(0.7f, 0.7f);

//         //gamemanager.setup1v1Match(1, 2, isBattleOver);

//     }



//     void handleInput() {
//         sf::Event event;
//         sf::Clock clock;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) window.close();

//             if (event.type == sf::Event::MouseButtonPressed) {
//                 sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

//                 // Check back button
//                 if (backButton.getGlobalBounds().contains(mousePos)) {
//                     nextState = STATE_ARENA;
//                     return;
//                 }

//                 // Check pet clicks
//                 for (int i = 0; i < petCount; i++) {
//                     if (petSprites[i].getGlobalBounds().contains(mousePos)) {
//                         // Toggle pet between right side and battlefield (left side)
//                         if (!petOnBattlefield[i]) {
//                             // Move to battlefield (left side)
//                             float leftSideX = 300;  // Adjust as needed
//                             float currentY = petSprites[i].getPosition().y;
//                             petSprites[i].setPosition(leftSideX, currentY);
//                             petOnBattlefield[i] = true;
//                         }
//                         else {
//                             // Move back to right side
//                             float rightSideX = 1000;  // Adjust as needed
//                             float currentY = petSprites[i].getPosition().y;
//                             petSprites[i].setPosition(rightSideX, currentY);
//                             petOnBattlefield[i] = false;
//                         }
//                         activePet = i;
//                     }
//                 }
//             }

//             sf::Vector2f movement(0.f, 0.f);
//             float speed = 18000.f;
//             sf::Time deltaTime = clock.restart();

//             if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
//                 movement.y -= speed;
//             }
//             if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//                 movement.y += speed;

//             }
//             if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//                 movement.x -= speed;
//             }
//             if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//                 movement.x += speed;

//             }

//             // Calculate intended new position
//             sf::Vector2f newPos = petSprites[activePet].getPosition() + movement * deltaTime.asSeconds();
//             sf::FloatRect spriteBounds = petSprites[activePet].getGlobalBounds();
//             sf::Vector2u windowSize = window.getSize();

//             // Clamp to window bounds
//             if (newPos.x < 0)
//                 newPos.x = 0;
//             if (newPos.y < 0)
//                 newPos.y = 0;
//             if (newPos.x + spriteBounds.width > windowSize.x)
//                 newPos.x = windowSize.x - spriteBounds.width;
//             if (newPos.y + spriteBounds.height > windowSize.y)
//                 newPos.y = windowSize.y - spriteBounds.height;

//             petSprites[activePet].setPosition(newPos);

//         }
//     }

//     void update() {
//         // Any continuous updates would go here
//     }

//     void draw() {
//         window.clear();
//         window.draw(background);

//         // Draw all pets
//         for (int i = 0; i < petCount; i++) {
//             window.draw(petSprites[i]);
//             window.draw(enemySprites[i]);
//         }

//         window.draw(backButton);
//         window.display();
//     }
// };

#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include<algorithm>
#include "menus.h"
#include"Player.h"
#include"Pet.h"
#include"Phoenix.h"
#include"Griffin.h"
#include"Unicorn.h"
#include"Dragon.h"

// Maximum number of selectable pets
const int MAX_SELECTABLE_PETS = 4;
const float MAX_ATTACK_RANGE = 150.0f;


extern GameManager gamemanager;

class ArenaBattleScreen {
private:
	sf::RenderWindow& window;
	sf::Texture bgTexture;
	sf::Sprite background;

	sf::Font font;
	sf::Text text;

	int petCount;  // Number of pets selected
	int activePet;
	PetType selectedPets[MAX_SELECTABLE_PETS];  // Store selected pet types
	PetType selectedEnemyPets[MAX_SELECTABLE_PETS];  // Store selected pet types
	sf::Sprite petSprites[MAX_SELECTABLE_PETS];  // Sprites for selected pets
	sf::Sprite enemySprites[MAX_SELECTABLE_PETS];  // Sprites for selected pets
	sf::Sprite rockSprite[5];
	bool petOnBattlefield[MAX_SELECTABLE_PETS];  // Whether pet is on battlefield (left side)
	bool gameOver = 0;
	bool isStunned = 0;
	bool isEnemyStunned = 0;

	Player user = *gamemanager.player;
	Player opponent;

	//prototype pets to pass inside opponent and user
	Dragon dragon;
	Phoenix phoenix;
	Griffin griffin;
	Unicorn unicorn;

	sf::Texture petTextures[4]; // DRAGON, PHOENIX, UNICORN, GRIFFIN
	sf::Texture rockTexture;

	sf::Texture buttonTex;
	sf::Sprite backButton;

	sf::RectangleShape finalBox;
	sf::RectangleShape healthBarOutline1, healthBarOutline2, healthBar1, healthBar2, attackReady, abilityReady, potions[4];

	atomic<bool> isBattleOver;

	//  enemy movement related members
	std::mt19937 rng;  // Mersenne Twister random number generator
	sf::Vector2f enemyTargetPositions[MAX_SELECTABLE_PETS];
	sf::Clock enemyMovementClock;
	float enemyMovementInterval = 3.0f;  // Recalculate target every 2 seconds
	bool changeEnemy = false;
	int activeEnemyIndex = 0;

	// Random number generation setup
	std::uniform_real_distribution<float> xDistribution;
	std::uniform_real_distribution<float> yDistribution;

	// Function to calculate distance between two sprites
	float calculateDistance(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
		// Get the center positions of both sprites
		sf::Vector2f pos1 = sprite1.getPosition();
		sf::Vector2f pos2 = sprite2.getPosition();

		// Calculate the distance using the Pythagorean theorem
		float dx = pos2.x - pos1.x;
		float dy = pos2.y - pos1.y;

		return std::sqrt(dx * dx + dy * dy);
	}

	// Function to check if pet is in attack range
	bool isInAttackRange(int petIndex, int enemyIndex) {
		return calculateDistance(petSprites[petIndex], enemySprites[enemyIndex]) <= MAX_ATTACK_RANGE;
	}

	void resetStatuses() {
		if (user.getPet(activePet).isAttackReady()) {
			attackReady.setFillColor(sf::Color(255, 255, 150));
		}
		if (user.getPet(activePet).isAbilityReady()) {
			abilityReady.setFillColor(sf::Color(100, 150, 255));
		}
	}

	void endScreen(bool userWon) {

		finalBox.setSize(sf::Vector2f(300.f, 200.f));
		finalBox.setOrigin(sf::Vector2f(150.f, 100.f));
		finalBox.setPosition(sf::Vector2f(640.f, 360.f));
		finalBox.setFillColor(sf::Color(30, 30, 30));
		window.draw(finalBox);

		int deathCounts = 0;

		gameOver = 1;

		text.setFont(font);
		text.setCharacterSize(16);

		if (!userWon) {
			cout << "You Lost!\n";
			string s = "You Lost!";
			text.setString(s);
			text.setPosition(sf::Vector2f(600, 330));
			window.draw(text);
			s = "You Got: 0$";
			text.setString(s);
			text.setPosition(sf::Vector2f(590, 360));
			window.draw(text);
		}
		else {
			cout << "You Won!\n";
			string s = "You Won!";
			text.setString(s);
			text.setPosition(sf::Vector2f(600, 330));
			window.draw(text);
			s = "You Got: 500$";
			text.setString(s);
			text.setPosition(sf::Vector2f(590, 360));
			window.draw(text);
			user.win();
		}
		cout << "hosla\n";

	}

	void checkDeath() {

		if (!user.getPet(activePet).isAlive()) {
			if (petCount > activePet + 1) {
				petSprites[activePet].setColor(sf::Color::Transparent);
				activePet++;
			}
			else {
				this_thread::sleep_for(std::chrono::seconds(2));
				user.endBattle();
				opponent.endBattle();
				//change state here
				endScreen(0);
				
			}
		}
		if (!opponent.getPet(activeEnemyIndex).isAlive()) {
			if (petCount > activeEnemyIndex + 1) {
				cout << "Death\n";
				enemySprites[activeEnemyIndex].setColor(sf::Color::Transparent);
				activeEnemyIndex++;
			}
			else {
				this_thread::sleep_for(std::chrono::seconds(2));
				user.endBattle();
				opponent.endBattle();
				//change state here
				endScreen(1);
			}
		}

	}

	void enemyAttacks() {

		if (!gameOver && opponent.getPet(activeEnemyIndex).isAttackReady() && isInAttackRange(activePet, activeEnemyIndex)) {

			Pet& userPet = user.getPet(activePet);
			Pet& oppoPet = opponent.getPet(activeEnemyIndex);
			std::thread t(&Pet::attack, &oppoPet, std::ref(userPet));
			t.detach();
			this_thread::sleep_for(std::chrono::milliseconds(20));

			updateHealthBar(healthBar1, userPet.getHealth(), userPet.getTotalHealth());
			sf::Sprite& tempSprite = petSprites[activePet];

			if (userPet.isAlive()) {
				bool use = 1;
				std::thread healthT(&ArenaBattleScreen::changeColorOnHit, this, std::ref(tempSprite), use);
				healthT.detach();
			}

		}
		else if (!gameOver && opponent.getPet(activeEnemyIndex).isAbilityReady()) {

			Pet& userPet = user.getPet(activePet);
			Pet& oppoPet = opponent.getPet(activeEnemyIndex);

			bool abilityNo = rand() % 2;

			if (auto* unicorn = dynamic_cast<Unicorn*>(&oppoPet)) {
				unicorn->useAbility(abilityNo, userPet);
			}
			else if (auto* dragon = dynamic_cast<Dragon*>(&oppoPet)) {
				dragon->useAbility(abilityNo, userPet);
				if (abilityNo) {
					thread t(&ArenaBattleScreen::stunned, this);
					t.detach();
				}
			}
			else if (auto* phoenix = dynamic_cast<Phoenix*>(&oppoPet)) {
				phoenix->useAbility(abilityNo, oppoPet);
			}
			else if (auto* griffin = dynamic_cast<Griffin*>(&oppoPet)) {
				griffin->useAbility(abilityNo, userPet);
				if (abilityNo) {
					thread t(&ArenaBattleScreen::stunned, this);
					t.detach();
				}
			}

			this_thread::sleep_for(std::chrono::milliseconds(20));

			updateHealthBar(healthBar2, oppoPet.getHealth(), oppoPet.getTotalHealth());
			updateHealthBar(healthBar1, userPet.getHealth(), userPet.getTotalHealth());
			sf::Sprite& tempSprite = petSprites[activePet];

			if (userPet.isAlive()) {
				bool use = 1;
				std::thread healthT(&ArenaBattleScreen::changeColorOnHit, this, std::ref(tempSprite), use);
				healthT.detach();
			}


		}

	}

	void stunned() {
		isStunned = true;
		cout << "Me Stunned\n";
		this_thread::sleep_for(std::chrono::seconds(5));
		isStunned = false;
	}

	void enemyStunned() {
		isEnemyStunned = true;
		enemySprites[activeEnemyIndex].setColor(sf::Color(150, 150, 220, 255));
		cout << "Enemy Stunned\n";
		this_thread::sleep_for(std::chrono::seconds(5));
		enemySprites[activeEnemyIndex].setColor(sf::Color(255, 150, 150, 255));
		isEnemyStunned = false;
	}
	
	bool isPetClear(float dx, float dy, float deltaTime) {
		// Calculate the actual movement distance based on delta time
		sf::Vector2f movement(dx * deltaTime, dy * deltaTime);

		// Create a copy of the sprite's bounds with the proposed movement applied
		sf::FloatRect futureBounds = petSprites[activePet].getGlobalBounds();
		futureBounds.left += movement.x;
		futureBounds.top += movement.y;

		// Optional: smaller buffer (or no buffer) to avoid excessive collision detection
		const float BUFFER = 1.0f; // Smaller buffer or 0.0f for exact collision
		futureBounds.left += BUFFER;
		futureBounds.top += BUFFER;
		futureBounds.width -= 2 * BUFFER;
		futureBounds.height -= 2 * BUFFER;

		// Check collision with each rock
		for (int i = 0; i < 5; i++) {
			if (rockSprite[i].getGlobalBounds().intersects(futureBounds)) {
				return false;
			}
		}
		return true;
	}

	bool isEnemyClear(int dx, int dy) {

		bool flag = true;

		sf::FloatRect futureBounds = enemySprites[activeEnemyIndex].getGlobalBounds();
		futureBounds.left += dx;
		futureBounds.top += dy;

		for (int i = 0; i < 5; i++) {
			if (rockSprite[i].getGlobalBounds().intersects(futureBounds)) {
				flag = false;
				break;
			}
		}
		return flag;
	}

public:
	GameState nextState = STATE_ARENA_BATTLE;

	ArenaBattleScreen(sf::RenderWindow& win, int numPets, PetType* pets, PetType* enemyPets)
		: window(win), petCount(numPets), rng(std::random_device{}()), activePet(0) {

		if (!font.loadFromFile("font.ttf")) {
			std::cerr << "Failed to load font!" << std::endl;
		}

		window.setFramerateLimit(60); // Cap at 60 FPS

		isBattleOver.store(false);

		// Setup random distribution for enemy movement
		xDistribution = std::uniform_real_distribution<float>(0, window.getSize().x * 0.8f);  // Avoid extreme edges
		yDistribution = std::uniform_real_distribution<float>(0, window.getSize().y * 0.8f);

		// Copy selected pets
		for (int i = 0; i < petCount && i < MAX_SELECTABLE_PETS; i++) {
			selectedPets[i] = pets[i];
			selectedEnemyPets[i] = enemyPets[i];
			petOnBattlefield[i] = false;  // Initially on right side

			//initialize user pets
			if (pets[i] == DRAGON) {
				user.addPet(std::make_unique<Dragon>());
			}
			else if (pets[i] == PHOENIX) {
				user.addPet(std::make_unique<Phoenix>());
			}
			else if (pets[i] == GRIFFIN) {
				user.addPet(std::make_unique<Griffin>());
			}
			else if (pets[i] == UNICORN) {
				user.addPet(std::make_unique<Unicorn>());
			}


			//initialize enemy pets
			if (enemyPets[i] == DRAGON) {
				opponent.addPet(std::make_unique<Dragon>());
			}
			else if (enemyPets[i] == PHOENIX) {
				opponent.addPet(std::make_unique<Phoenix>());
			}
			else if (enemyPets[i] == GRIFFIN) {
				opponent.addPet(std::make_unique<Griffin>());
			}
			else if (enemyPets[i] == UNICORN) {
				opponent.addPet(std::make_unique<Unicorn>());
			}



			// Initialize enemy target positions
			enemyTargetPositions[i] = sf::Vector2f
			(
				xDistribution(rng),
				yDistribution(rng)
			);
		}


		// Load background
		if (!bgTexture.loadFromFile("backgrounds/arena_bg.png")) {
			std::cerr << "Failed to load arena background texture!" << std::endl;
		}
		background.setTexture(bgTexture);
		background.setScale(
			1280.0f / background.getLocalBounds().width,
			720.0f / background.getLocalBounds().height
		);

		//loading rock
		if (!rockTexture.loadFromFile("textures/rock.png")) {
			std::cerr << "Failed to load arena background texture!" << std::endl;
		}

		for (int i = 0; i < 5; i++)
		{
			rockSprite[i].setTexture(rockTexture);
			rockSprite[i].setPosition(
				rand() % (1280 - 100) + 50,
				rand() % (500 - 250) + 100
			);
			rockSprite[i].setScale(0.2f, 0.2f);
		}

		// Load pet textures
		std::string texturePaths[] = {
			"textures/dragon.png",
			"textures/pheonix.png",
			"textures/unicorn.png",
			"textures/griffin.png"
		};

		for (int i = 0; i < 4; i++) {
			if (!petTextures[i].loadFromFile(texturePaths[i])) {
				std::cerr << "Failed to load texture: " << texturePaths[i] << std::endl;
			}
		}

		// Setup enemy pet sprites
		for (int i = 0; i < petCount; i++)
		{
			enemySprites[i].setTexture(petTextures[selectedEnemyPets[i]]);

			// Scale sprites to appropriate size
			float scale = 0.2f;  // Adjust as needed   
			enemySprites[i].setScale(scale, scale);

			enemySprites[i].setColor(sf::Color(255, 150, 150, 255));

			// Position on right side initially, evenly spaced
			float rightSideX = 800;  // Adjust as needed
			float spacing = 720.0f / (petCount + 1);
			if(i == 0)
				enemySprites[i].setPosition(rightSideX, (i + 1) * spacing);
			else
				enemySprites[i].setPosition(rightSideX, 650);
		}

		// Setup pet sprites (player pets)
		for (int i = 0; i < petCount; i++) {
			petSprites[i].setTexture(petTextures[selectedPets[i]]);

			// Scale sprites to appropriate size
			float scale = 0.2f;  // Adjust as needed
			petSprites[i].setScale(scale, scale);

			// Position on right side initially, evenly spaced
			float leftSideX = 200;  // Adjust as needed
			float spacing = 720.0f / (petCount + 1);
			if(i == 0)
				petSprites[i].setPosition(leftSideX, spacing);
			else
				petSprites[i].setPosition(leftSideX, 650);

		}

		//Make Health Bars

		healthBarOutline1.setSize(sf::Vector2f(104.f, 14.f));
		healthBar1.setSize(sf::Vector2f(100.f, 10.f));

		healthBarOutline2.setSize(sf::Vector2f(104.f, 14.f));
		healthBar2.setSize(sf::Vector2f(100.f, 10.f));

		healthBarOutline1.setFillColor(sf::Color::Transparent);
		healthBarOutline1.setOutlineColor(sf::Color::White);
		healthBarOutline1.setOutlineThickness(2.f);
		healthBarOutline1.setPosition(276.f, 50.f);

		healthBar1.setFillColor(sf::Color::Green);
		healthBar1.setPosition(278.f, 52.f);

		healthBarOutline2.setFillColor(sf::Color::Transparent);
		healthBarOutline2.setOutlineColor(sf::Color::White);
		healthBarOutline2.setOutlineThickness(2.f);
		healthBarOutline2.setPosition(900.f, 50.f);

		healthBar2.setFillColor(sf::Color::Red);
		healthBar2.setPosition(902.f, 52.f);

		//setting up the attackReady and abilityReady
		attackReady.setSize(sf::Vector2f(14.f, 14.f));
		abilityReady.setSize(sf::Vector2f(14.f, 14.f));
		//setting up potion boxes
		for (int i = 0; i < 4; i++) {
			potions[i].setSize(sf::Vector2f(14.f, 14.f));
		}

		attackReady.setFillColor(sf::Color(255, 255, 150));
		abilityReady.setFillColor(sf::Color(100, 150, 255));

		potions[0].setFillColor(sf::Color::Yellow); //Health
		potions[1].setFillColor(sf::Color::Blue); //Shield
		potions[2].setFillColor(sf::Color::Red); //Buff
		potions[3].setFillColor(sf::Color::White);//Stamina


		attackReady.setPosition(sf::Vector2f(226.f, 50.f));
		abilityReady.setPosition(sf::Vector2f(246.f, 50.f));

		float yPotion = 20;
		float xStart = 80;
		float xDiff = 20;

		for (int i = 0; i < 4; i++) {
			potions[i].setPosition(sf::Vector2f(xStart + xDiff*i , yPotion));
		}

		// Load back button
		if (!buttonTex.loadFromFile("textures/back.png")) {
			std::cerr << "Failed to load back button texture!" << std::endl;
		}
		backButton.setTexture(buttonTex);
		backButton.setPosition(20, 20);
		backButton.setScale(0.7f, 0.7f);
	}

	void setPotionColors() {

		if (user.getItemCount("HealingPotion") > 0) {
			potions[0].setFillColor(sf::Color::Yellow); //Health
		}
		else
		{
			potions[0].setFillColor(sf::Color(50, 50, 50)); //Health
		}

		if (user.getItemCount("Shield") > 0) {
			potions[1].setFillColor(sf::Color::Blue); //Shield
		}
		else
			potions[1].setFillColor(sf::Color(50, 50, 50)); //Health

		if (user.getItemCount("Buff") > 0)
			potions[2].setFillColor(sf::Color::Red); //Buff
		else
			potions[2].setFillColor(sf::Color(50, 50, 50)); //Buff

		if (user.getItemCount("Stamina") > 0)
			potions[3].setFillColor(sf::Color::White); //Stamina
		else
			potions[3].setFillColor(sf::Color(50, 50, 50)); //Stamina

	}

	void changeColorOnHit(sf::Sprite& sprite, bool isUser) {

		cout << "Color Hit\n";
		sprite.setColor(sf::Color(255, 0, 0, 255));
		this_thread::sleep_for(std::chrono::milliseconds(700));
		if (isUser) {
			sprite.setColor(sf::Color(255, 255, 255, 255));
		}
		else {
			sprite.setColor(sf::Color(255, 150, 150, 255));
		}
		cout << "Color Reset\n";

	}

	void updateHealthBar(sf::RectangleShape& bar, int currentHealth, int maxHealth) {
		if (maxHealth <= 0) return; // Avoid division by zero
		float ratio = std::clamp(static_cast<float>(currentHealth) / maxHealth, 0.f, 1.f);
		bar.setSize(sf::Vector2f(100.f * ratio, 10.f)); // 100.f is the full bar width
	}

	void updateEnemyMovement()
	{


		float deltaTime = enemyMovementClock.getElapsedTime().asSeconds();

		// Ensure the active enemy index is within bounds
		if (activeEnemyIndex >= petCount) {
			activeEnemyIndex = 0;
		}

		// Current position of the active enemy sprite
		float currentX = enemySprites[activeEnemyIndex].getPosition().x;
		float currentY = enemySprites[activeEnemyIndex].getPosition().y;

		// Get player's current position (active pet)
		float playerX = petSprites[activePet].getPosition().x;
		float playerY = petSprites[activePet].getPosition().y;

		// State management: approach player first, then random position
		static bool isFollowingPlayer = true;
		static float stateTimer = 0.0f;

		// Update state timer
		stateTimer += deltaTime;

		// Switch states every few seconds
		if (stateTimer >= 3.0f) {
			isFollowingPlayer = !isFollowingPlayer;
			stateTimer = 0.0f;

			// If switching to random movement, choose new random position
			if (!isFollowingPlayer) {
				enemyTargetPositions[activeEnemyIndex].x = rand() % (int)(window.getSize().x * 0.8f);
				enemyTargetPositions[activeEnemyIndex].y = rand() % (int)(window.getSize().y * 0.8f);
			}
		}

		// Determine target position
		float targetX, targetY;
		if (isFollowingPlayer) {
			targetX = playerX;
			targetY = playerY;
		}
		else {
			targetX = enemyTargetPositions[activeEnemyIndex].x;
			targetY = enemyTargetPositions[activeEnemyIndex].y;
		}

		// Calculate direction
		float dirX = targetX - currentX;
		float dirY = targetY - currentY;

		// Calculate distance
		float distance = sqrt(dirX * dirX + dirY * dirY);

		// Move toward target if not too close
		if (distance > 10.0f) {
			// Normalize direction
			float normalizedDirX = dirX / distance;
			float normalizedDirY = dirY / distance;

			// Calculate movement with fixed speed
			float speed = 5.0f;
			float moveX = normalizedDirX * speed * deltaTime;
			float moveY = normalizedDirY * speed * deltaTime;

			if (isEnemyClear(moveX, moveY)) {
				enemySprites[activeEnemyIndex].move(moveX, moveY);
			}
			else {
				// Try X only
				if (isEnemyClear(moveX, 0)) {
					enemySprites[activeEnemyIndex].move(moveX, 0);
				}
				// Try Y only
				else if (isEnemyClear(0, moveY)) {
					enemySprites[activeEnemyIndex].move(0, moveY);
				}
				// Else blocked entirely, do nothing this frame
			}
		}


		// Reset clock if interval has passed
		if (deltaTime >= enemyMovementInterval) {
			enemyMovementClock.restart();
		}
	}

	void handleInput() {
		sf::Event event;
		static sf::Clock movementClock;
		float deltaTime = movementClock.restart().asSeconds();


		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

				// Check back button
				if (backButton.getGlobalBounds().contains(mousePos)) {
					nextState = STATE_MODE_SELECT;
					return;
				}

				// Check pet clicks
				for (int i = 0; i < petCount; i++) {
					if (petSprites[i].getGlobalBounds().contains(mousePos)) {
						// Set active pet
						activePet = i;

						// Toggle pet between right side and battlefield (left side)
						if (!petOnBattlefield[i]) {
							// Move to battlefield
							float topSideY = 720;  // Adjust as needed
							float currentX = petSprites[i].getPosition().x;
							petSprites[i].setPosition(currentX, topSideY);
							petOnBattlefield[i] = true;
						}
						else {
							// Move back to Bench
							float topSideY = 650;  // Adjust as needed
							float currentX = petSprites[i].getPosition().x;
							petSprites[i].setPosition(currentX, topSideY);
							petOnBattlefield[i] = false;
						}
					}
				}
			}

			// Ensure activePet is within bounds
			if (activePet < 0 || activePet >= petCount) {
				activePet = 0;
			}

			if (event.type == sf::Event::KeyPressed && !gameOver && !isStunned) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && user.getPet(activePet).isAttackReady() && isInAttackRange(activePet, activeEnemyIndex) && !gameOver) {
					std::cout << "Attacked in range!\n";
					Pet& userPet = user.getPet(activePet);
					Pet& oppoPet = opponent.getPet(activeEnemyIndex);
					std::thread t(&Pet::attack, &userPet, std::ref(oppoPet));
					t.detach();
					this_thread::sleep_for(std::chrono::milliseconds(20));

					attackReady.setFillColor(sf::Color(50, 50, 50));
					updateHealthBar(healthBar2, oppoPet.getHealth(), oppoPet.getTotalHealth());
					sf::Sprite& tempSprite = enemySprites[activeEnemyIndex];

					if (oppoPet.isAlive()) {
						bool oppo = 0;
						std::thread healthT(&ArenaBattleScreen::changeColorOnHit, this, std::ref(tempSprite), oppo);
						healthT.detach();
					}

				}
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::X) || sf::Keyboard::isKeyPressed(sf::Keyboard::C)) && user.getPet(activePet).isAbilityReady()) {

					cout << "Ability used\n";

					Pet& userPet = user.getPet(activePet);
					Pet& oppoPet = opponent.getPet(activeEnemyIndex);

					bool abilityNo = false;
					bool specialForPhoenix = true;

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
						abilityNo = true;

					if (auto* unicorn = dynamic_cast<Unicorn*>(&userPet)) {
						unicorn->useAbility(abilityNo, oppoPet);

					}
					else if (auto* dragon = dynamic_cast<Dragon*>(&userPet)) {
						dragon->useAbility(abilityNo, oppoPet);
						if (abilityNo) {
							thread t(&ArenaBattleScreen::enemyStunned, this);
							t.detach();
						}
					}
					else if (auto* phoenix = dynamic_cast<Phoenix*>(&userPet)) {
						if (phoenix->getIsAbleToRevive() || !abilityNo)
							phoenix->useAbility(abilityNo, userPet);
						else
							specialForPhoenix = false;
					}
					else if (auto* griffin = dynamic_cast<Griffin*>(&userPet)) {
						griffin->useAbility(abilityNo, oppoPet);
						if (abilityNo) {
							thread t(&ArenaBattleScreen::enemyStunned, this);
							t.detach();
						}
					}

					this_thread::sleep_for(std::chrono::milliseconds(20));

					if(specialForPhoenix)
						abilityReady.setFillColor(sf::Color(50, 50, 50));

					updateHealthBar(healthBar2, oppoPet.getHealth(), oppoPet.getTotalHealth());
					updateHealthBar(healthBar1, userPet.getHealth(), userPet.getTotalHealth());
					sf::Sprite& tempSprite = enemySprites[activeEnemyIndex];

					if (oppoPet.isAlive()) {
						bool oppo = 0;
						std::thread healthT(&ArenaBattleScreen::changeColorOnHit, this, std::ref(tempSprite), oppo);
						healthT.detach();
					}

				}
				
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && user.getItemCount("HealingPotion") > 0)) {
					std::thread t([&]() {
						user.useItem(user.getPet(activePet), "HealingPotion");
						});
					t.detach(); 
					setPotionColors();
				}
				
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && user.getItemCount("Shield") > 0)) {
					cout << "Bought Shields\n";
					user.buyItem("Shield");
					std::thread t([&]() {
						user.useItem(user.getPet(activePet), "Shield");
						});
					t.detach(); // Or t.join(); if you want to wait for it
					setPotionColors();
				}
				
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && user.getItemCount("Buff") > 0)) {
					std::thread t([&]() {
						user.useItem(user.getPet(activePet), "Buff");
						});
					t.detach(); // Or t.join(); if you want to wait for it
					setPotionColors();
				}
				
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && user.getItemCount("Stamina") > 0)) {
					std::thread t([&]() {
						user.useItem(user.getPet(activePet), "Stamina");
						});
					t.detach(); // Or t.join(); if you want to wait for it
					setPotionColors();
				}
			}
			//movement

	// Handle movement separately from the event polling loop
			sf::Vector2f movement(0.f, 0.f);
			float speed = 400.f; // Adjust this value as needed

			if (!gameOver && !isStunned) {
				// Get input direction
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed * deltaTime;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed * deltaTime;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed * deltaTime;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed * deltaTime;

				// Try to apply movement with collision detection
				sf::Vector2f currentPos = petSprites[activePet].getPosition();
				sf::Vector2f newPos = currentPos + movement;

				// Test if the new position would cause a collision
				sf::FloatRect currentBounds = petSprites[activePet].getGlobalBounds();
				sf::FloatRect newBounds = currentBounds;
				newBounds.left = newPos.x;
				newBounds.top = newPos.y;

				bool collision = false;
				for (int i = 0; i < 5; i++) {
					if (rockSprite[i].getGlobalBounds().intersects(newBounds)) {
						collision = true;
						break;
					}
				}

				// If no collision, apply the movement
				if (!collision) {
					petSprites[activePet].setPosition(newPos);
				}
				else {
					// Try horizontal movement only
					sf::Vector2f horizontalPos = currentPos;
					horizontalPos.x += movement.x;

					sf::FloatRect horizontalBounds = currentBounds;
					horizontalBounds.left = horizontalPos.x;

					bool horizontalCollision = false;
					for (int i = 0; i < 5; i++) {
						if (rockSprite[i].getGlobalBounds().intersects(horizontalBounds)) {
							horizontalCollision = true;
							break;
						}
					}

					// If horizontal movement is clear, apply it
					if (!horizontalCollision) {
						petSprites[activePet].setPosition(horizontalPos);
					}

					// Try vertical movement only
					sf::Vector2f verticalPos = currentPos;
					verticalPos.y += movement.y;

					sf::FloatRect verticalBounds = currentBounds;
					verticalBounds.top = verticalPos.y;

					bool verticalCollision = false;
					for (int i = 0; i < 5; i++) {
						if (rockSprite[i].getGlobalBounds().intersects(verticalBounds)) {
							verticalCollision = true;
							break;
						}
					}

					// If vertical movement is clear, apply it
					if (!verticalCollision && horizontalCollision) {
						petSprites[activePet].setPosition(verticalPos);
					}
				}

				// Ensure the sprite stays within screen bounds
				sf::Vector2f finalPos = petSprites[activePet].getPosition();
				sf::FloatRect spriteBounds = petSprites[activePet].getGlobalBounds();
				sf::Vector2u windowSize = window.getSize();

				finalPos.x = std::max(0.f, std::min(finalPos.x, static_cast<float>(windowSize.x - spriteBounds.width)));
				finalPos.y = std::max(0.f, std::min(finalPos.y, static_cast<float>(windowSize.y - spriteBounds.height)));

				petSprites[activePet].setPosition(finalPos);
			}
		}

	}
	 
	void update() {
		// Update enemy movement
		if (!gameOver) {
			if (!isEnemyStunned) {
				updateEnemyMovement();
				enemyAttacks();
			}
			resetStatuses();
			setPotionColors();
			checkDeath();
		}
	}

	void draw() {
		window.clear();
		window.draw(background);

		// Draw all pets
		for (int i = 0; i < petCount; i++) {
			window.draw(petSprites[i]);
			window.draw(enemySprites[i]);
		}

		for (int i = 0; i < 5; i++) {
			window.draw(rockSprite[i]);
		}

		// optional shiz agar acha lagta tou good ni tou remove 
		if (petOnBattlefield[activePet]) {
			// visual indicator for the attack range
			sf::CircleShape rangeIndicator(MAX_ATTACK_RANGE);
			rangeIndicator.setOrigin(MAX_ATTACK_RANGE, MAX_ATTACK_RANGE);
			rangeIndicator.setPosition(petSprites[activePet].getPosition());
			rangeIndicator.setFillColor(sf::Color(100, 255, 100, 50)); // semi-transparent green
			rangeIndicator.setOutlineColor(sf::Color(50, 200, 50, 100));
			rangeIndicator.setOutlineThickness(2.0f);
			window.draw(rangeIndicator);
		}

		for (int i = 0; i < 4; i++) {
			window.draw(potions[i]);
		}


		window.draw(backButton);
		window.draw(healthBar1);
		window.draw(healthBar2);
		window.draw(healthBarOutline1);
		window.draw(healthBarOutline2);
		window.draw(attackReady);
		window.draw(abilityReady);
		window.draw(finalBox);
		window.draw(text);
		window.display();
	}

};