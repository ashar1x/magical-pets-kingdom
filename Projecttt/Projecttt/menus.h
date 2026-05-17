#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>



enum PetType { DRAGON, PHOENIX, UNICORN, GRIFFIN };

GameManager gamemanager;

enum GameState {
    STATE_MAIN_MENU,
    STATE_MODE_SELECT,
    STATE_TRAIN,
    STATE_TRAINING,
    STATE_ARENA,
    STATE_ARENA_SELECT_1V1,
    STATE_ARENA_SELECT_2V2,
    STATE_ARENA_SELECT_4V4,
    STATE_GUILD,
    STATE_GAME,
    STATE_SHOP,
    STATE_ARENA_BATTLE 
};

// Declaration for global variable
extern PetType selectedPetType;

// Global state variable
extern GameState currentState;

// Helper function to center text relative to its background
void centerTextOnBackground(sf::Text& text, const sf::RectangleShape& background) {
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(
        background.getPosition().x + background.getSize().x / 2.0f,
        background.getPosition().y + background.getSize().y / 2.0f
    );
}

class MainMenu {
private:
    sf::RenderWindow& window;
    sf::Font mainFont;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Text inputText;
    sf::RectangleShape textBox;

    sf::Text playText;
    sf::RectangleShape playButton;

    sf::Text changeNameText;
    sf::RectangleShape changeNameButton;

    sf::Text exitText;
    sf::RectangleShape exitButton;

    std::string playerName;
    bool nameEntered = false;

    // not used abi for potential find handling: 
    void processPlayerName(const std::string& username) 
    {
        // This function will only be called once when Enter is pressed
        // or when clicking outside the textbox after entering a valid name

        std::cout << "Processing username: " << username << std::endl;

        // Here you can add any other functionality you need
        // For example:
        // savePlayerName(username);
        // loadPlayerProfile(username);
        // or pass it to another system
    }

public:
    GameState nextState = STATE_MAIN_MENU;

    MainMenu(sf::RenderWindow& win) : window(win) {
        // Load font
        if (!mainFont.loadFromFile("font.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        // Load background
        if (!backgroundTexture.loadFromFile("backgrounds/main_bg.png")) {
            std::cerr << "Failed to load menu background!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        // Scale background to fill screen
        float scaleX = 1280.0f / backgroundTexture.getSize().x; 
        float scaleY = 720.0f / backgroundTexture.getSize().y;
        backgroundSprite.setScale(scaleX, scaleY);

        // Text input box - centered
        textBox.setSize(sf::Vector2f(400, 40));
        textBox.setPosition((1280 - 400) / 2.0f, 250);
        textBox.setFillColor(sf::Color(255, 255, 255, 220));
        textBox.setOutlineThickness(2);
        textBox.setOutlineColor(sf::Color(139, 69, 19)); // Brown outline

        inputText.setFont(mainFont);
        inputText.setCharacterSize(24);
        inputText.setPosition(textBox.getPosition().x + 10, textBox.getPosition().y + 5);
        inputText.setFillColor(sf::Color::Black);
        inputText.setString("Enter Your Name...");

        // Play Button - centered with nature theme colors
        playButton.setSize(sf::Vector2f(250, 60));
        playButton.setPosition((1280 - 250) / 2.0f, 350);
        playButton.setFillColor(sf::Color(76, 175, 80)); // Green
        playButton.setOutlineThickness(2);
        playButton.setOutlineColor(sf::Color(27, 94, 32)); // Dark green

        playText.setFont(mainFont);
        playText.setString("Play Game");
        playText.setCharacterSize(30);
        centerTextOnBackground(playText, playButton);

        // Change Name Button - centered
        changeNameButton.setSize(sf::Vector2f(250, 60));
        changeNameButton.setPosition((1280 - 250) / 2.0f, 440);
        changeNameButton.setFillColor(sf::Color(156, 204, 101)); // Light green
        changeNameButton.setOutlineThickness(2);
        changeNameButton.setOutlineColor(sf::Color(27, 94, 32)); // Dark green

        changeNameText.setFont(mainFont);
        changeNameText.setString("Change Name");
        changeNameText.setCharacterSize(30);
        centerTextOnBackground(changeNameText, changeNameButton);

        // Exit Button - centered
        exitButton.setSize(sf::Vector2f(250, 60));
        exitButton.setPosition((1280 - 250) / 2.0f, 530);
        exitButton.setFillColor(sf::Color(211, 47, 47)); // Red
        exitButton.setOutlineThickness(2);
        exitButton.setOutlineColor(sf::Color(183, 28, 28)); // Dark red

        exitText.setFont(mainFont);
        exitText.setString("Exit");
        exitText.setCharacterSize(30);
        centerTextOnBackground(exitText, exitButton);
    }

    // Add to MainMenu class:
    void reset() {
        nextState = STATE_MAIN_MENU;
        // If you need to reset any other state variables, do it here
    }

    void handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


            if (!nameEntered) {
                // Text input handling
                if (event.type == sf::Event::TextEntered) {
                    // Clear placeholder text on first input
                    if (inputText.getString() == "Enter Your Name..." &&
                        event.text.unicode != '\b' &&
                        event.text.unicode != '\r') {
                        playerName.clear();
                    }

                    if (event.text.unicode == '\b') { // Backspace
                        if (!playerName.empty())
                            playerName.pop_back();
                    }
                    else if (event.text.unicode < 128 &&
                        event.text.unicode != '\r' &&
                        playerName.length() < 20) { // Character limit
                        playerName += static_cast<char>(event.text.unicode);
                    }
                    inputText.setString(playerName.empty() ? "Enter Your Name..." : playerName);
                }

                // Enter key or clicking outside textbox
                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Enter &&
                    !playerName.empty() &&
                    playerName != "Enter Your Name...") {

                    nameEntered = true;
                    gamemanager.createNewPlayer(playerName);
                }
            }
            else { // When name is already entered
                if (event.type == sf::Event::MouseButtonReleased) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);

                    if (playButton.getGlobalBounds().contains(mousePosF)) {
                        nextState = STATE_MODE_SELECT;
                    }
                    else if (event.type == sf::Event::MouseButtonReleased &&
                        !textBox.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
                        if (!playerName.empty() && playerName != "Enter Your Name...") {
                            nameEntered = true;

                            // Process the username here too
                            gamemanager.createNewPlayer(playerName);
                        }
                    }
                    else if (exitButton.getGlobalBounds().contains(mousePosF)) {
                        window.close();
                    }
                }
            }
        }
    }

    void draw() {
        window.clear();
        window.draw(backgroundSprite);

        if (!nameEntered) {
            window.draw(textBox);
            window.draw(inputText);
        }
        else {
            window.draw(playButton);
            window.draw(playText);
            window.draw(changeNameButton);
            window.draw(changeNameText);
            window.draw(exitButton);
            window.draw(exitText);
        }

        window.display();
    }

    std::string getPlayerName() const {
        return playerName;
    }
};

class ModeSelectMenu {
private:
    sf::RenderWindow& window;
    sf::Font mainFont;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture backTexture;
    sf::Sprite backButton;

    sf::Text trainText;
    sf::RectangleShape trainButton;

    sf::Text arenaText;
    sf::RectangleShape arenaButton;

    sf::Text guildText;
    sf::RectangleShape guildButton;

    sf::Text shopText;
    sf::RectangleShape shopButton;

public:
    GameState nextState = STATE_MODE_SELECT;

    ModeSelectMenu(sf::RenderWindow& win) : window(win) {
        if (!mainFont.loadFromFile("font.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        // Load background
        if (!backgroundTexture.loadFromFile("backgrounds/mode_bg.png")) {
            std::cerr << "Failed to load mode selection background!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        // Scale background to fill screen
        float scaleX = 1280.0f / backgroundTexture.getSize().x;
        float scaleY = 720.0f / backgroundTexture.getSize().y;
        backgroundSprite.setScale(scaleX, scaleY);

        // Back button at top left corner
        if (!backTexture.loadFromFile("textures/back.png")) {
            std::cerr << "Failed to load back button texture!" << std::endl;
        }
        backButton.setTexture(backTexture);
        backButton.setPosition(20, 20);
        backButton.setScale(0.7f, 0.7f);

        // Train Button - centered
        trainButton.setSize(sf::Vector2f(300, 70));
        trainButton.setPosition((1280 - 300) / 2.0f, 240);
        trainButton.setFillColor(sf::Color(76, 175, 80)); // Green
        trainButton.setOutlineThickness(3);
        trainButton.setOutlineColor(sf::Color(27, 94, 32)); // Dark green

        trainText.setFont(mainFont);
        trainText.setString("Train");
        trainText.setCharacterSize(36);
        centerTextOnBackground(trainText, trainButton);

        // Arena Button - centered
        arenaButton.setSize(sf::Vector2f(300, 70));
        arenaButton.setPosition((1280 - 300) / 2.0f, 340);
        arenaButton.setFillColor(sf::Color(255, 193, 7)); // Amber/Gold
        arenaButton.setOutlineThickness(3);
        arenaButton.setOutlineColor(sf::Color(255, 111, 0)); // Orange

        arenaText.setFont(mainFont);
        arenaText.setString("Arena");
        arenaText.setCharacterSize(36);
        centerTextOnBackground(arenaText, arenaButton);

        // Guild Button - centered
        guildButton.setSize(sf::Vector2f(300, 70));
        guildButton.setPosition((1280 - 300) / 2.0f, 440);
        guildButton.setFillColor(sf::Color(121, 85, 72)); // Brown
        guildButton.setOutlineThickness(3);
        guildButton.setOutlineColor(sf::Color(62, 39, 35)); // Dark brown

        guildText.setFont(mainFont);
        guildText.setString("Guild");
        guildText.setCharacterSize(36);
        centerTextOnBackground(guildText, guildButton);

        // shop button centered
        shopButton.setSize(sf::Vector2f(300, 70));
        shopButton.setPosition((1280 - 300) / 2.0f, 540);
        shopButton.setFillColor(sf::Color(3, 169, 244)); // Light Blue
        shopButton.setOutlineThickness(3);
        shopButton.setOutlineColor(sf::Color(1, 87, 155)); // Dark Blue

        shopText.setFont(mainFont);
        shopText.setString("Shop");
        shopText.setCharacterSize(36);
        centerTextOnBackground(shopText, shopButton);
    }

    void reset() {
        nextState = STATE_MODE_SELECT;
        // Reset any other state if needed
    }

    // In ModeSelectMenu::handleInput()
    void handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonReleased) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);
                if (trainButton.getGlobalBounds().contains(mousePosF)) {
                    nextState = STATE_TRAIN;
                }
                else if (arenaButton.getGlobalBounds().contains(mousePosF)) {
                    nextState = STATE_ARENA;
                }
                else if (guildButton.getGlobalBounds().contains(mousePosF)) {
                    nextState = STATE_GUILD;
                }
                else if (backButton.getGlobalBounds().contains(mousePosF)) {
                    cout << "Back button pressed, returning to main menu\n";
                    nextState = STATE_MAIN_MENU;
                }
                else if (shopButton.getGlobalBounds().contains(mousePosF))
                {
                    nextState = STATE_SHOP;
                }
            }
        }
    }
    void draw() {
        window.clear();
        window.draw(backgroundSprite);

        window.draw(trainButton);
        window.draw(trainText);
        window.draw(arenaButton);
        window.draw(arenaText);
        window.draw(guildButton);
        window.draw(guildText);
        window.draw(backButton);
        window.draw(shopButton);
        window.draw(shopText);

        window.display();
    }
};

class TrainMenu {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture backTexture;
    sf::Sprite backButton;

    sf::Texture petTextures[4];
    sf::Sprite petSprites[4];
    sf::RectangleShape tileOutlines[4];
    bool isHovered[4] = { false };

public:
    GameState nextState = STATE_TRAIN;

    TrainMenu(sf::RenderWindow& win) : window(win) {
        // Load font
        if (!font.loadFromFile("font.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        // Load background
        if (!backgroundTexture.loadFromFile("backgrounds/pet_select_bg.png")) {
            std::cerr << "Failed to load pet selection background!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        // Scale background to fill screen
        float scaleX = 1280.0f / backgroundTexture.getSize().x;
        float scaleY = 720.0f / backgroundTexture.getSize().y;
        backgroundSprite.setScale(scaleX, scaleY);

        // Back button at top left corner
        if (!backTexture.loadFromFile("textures/back.png")) {
            std::cerr << "Failed to load back button texture!" << std::endl;
        }
        backButton.setTexture(backTexture);
        backButton.setPosition(20, 20);
        backButton.setScale(0.7f, 0.7f);

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
            petSprites[i].setTexture(petTextures[i]);
        }

        // Calculate grid positions - centered on screen
        const float tileSize = 250.0f;
        const float spacing = 60.0f;

        // Center the 2x2 grid in the screen
        const float gridWidth = 2 * tileSize + spacing;
        const float gridHeight = 2 * tileSize + spacing;
        const float startX = (1280 - gridWidth) / 2.0f;
        const float startY = (800 - gridHeight) / 2.0f;

        // Create 2x2 grid
        for (int i = 0; i < 4; i++) {
            // Position calculation
            int row = i / 2;
            int col = i % 2;
            float posX = startX + col * (tileSize + spacing);
            float posY = startY + row * (tileSize + spacing);

            // Configure sprites
            petSprites[i].setPosition(posX, posY);

            // Scale sprites to fit the tile size while maintaining aspect ratio
            float scaleX = tileSize / petSprites[i].getLocalBounds().width;
            float scaleY = tileSize / petSprites[i].getLocalBounds().height;
            float scale = std::min(scaleX, scaleY);
            petSprites[i].setScale(scale, scale);

            // Center the sprite within its tile
            sf::FloatRect spriteBounds = petSprites[i].getLocalBounds();
            float spriteWidth = spriteBounds.width * scale;
            float spriteHeight = spriteBounds.height * scale;
            float offsetX = (tileSize - spriteWidth) / 2.0f;
            float offsetY = (tileSize - spriteHeight) / 2.0f;
            petSprites[i].setPosition(posX + offsetX, posY + offsetY);

            // Configure hover outlines
            tileOutlines[i].setSize(sf::Vector2f(tileSize, tileSize));
            tileOutlines[i].setPosition(posX, posY);
            tileOutlines[i].setFillColor(sf::Color::Transparent);
            tileOutlines[i].setOutlineThickness(4.0f);
            tileOutlines[i].setOutlineColor(sf::Color::Transparent);
        }
    }

    void handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle hover effects
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);

            // Back button interaction
            if (event.type == sf::Event::MouseButtonReleased) {
                if (backButton.getGlobalBounds().contains(mousePosF)) {
                    nextState = STATE_MODE_SELECT;
                }
            }

            for (int i = 0; i < 4; i++) {
                // Check if mouse is over the tile outline area
                isHovered[i] = tileOutlines[i].getGlobalBounds().contains(mousePosF);

                // Update outline color for hover effect
                tileOutlines[i].setOutlineColor(
                    isHovered[i] ? sf::Color(255, 215, 0, 200) : sf::Color::Transparent
                );

                // Handle clicks
                if (event.type == sf::Event::MouseButtonPressed && isHovered[i]) {
                    selectedPetType = static_cast<PetType>(i); // Convert index to PetType
                    nextState = STATE_TRAINING; // Go to training screen\n
                    cout << "nigga pls work? \n";
                }
            }
        }
    }

    void draw() {
        window.clear();
        window.draw(backgroundSprite);

        // Draw pet tiles
        for (int i = 0; i < 4; i++) {
            window.draw(tileOutlines[i]);  // Draw outline first
            window.draw(petSprites[i]);
        }

        window.draw(backButton);
        window.display();
    }
};

class ArenaMenu {
private:
	sf::RenderWindow& window;
	sf::Font font;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Texture backTexture;
	sf::Sprite backButton;

	sf::RectangleShape buttons[3];
	sf::Text buttonTexts[3];

	bool isFirstRender = true; // Flag to track first render after state change

public:
	GameState nextState = STATE_ARENA;

	ArenaMenu(sf::RenderWindow& win) : window(win) {
		if (!font.loadFromFile("font.ttf")) {
			std::cerr << "Error loading font" << std::endl;
		}

		// Load background
		if (!backgroundTexture.loadFromFile("arena_bg.png")) {
			std::cerr << "Failed to load arena background!" << std::endl;
		}
		backgroundSprite.setTexture(backgroundTexture);

		// Scale background to fill screen
		float scaleX = 1280.0f / backgroundTexture.getSize().x;
		float scaleY = 720.0f / backgroundTexture.getSize().y;
		backgroundSprite.setScale(scaleX, scaleY);

		// Back button at top left corner
		if (!backTexture.loadFromFile("textures/back.png")) {
			std::cerr << "Failed to load back button texture!" << std::endl;
		}
		backButton.setTexture(backTexture);
		backButton.setPosition(20, 20);
		backButton.setScale(0.7f, 0.7f);

		// Buttons - centered on screen
		const std::string labels[] = { "1v1", "2v2", "Guild Wars" };
		const sf::Color buttonColors[] = {
			sf::Color(255, 87, 34),  // Deep Orange for 1v1
			sf::Color(233, 30, 99),  // Pink for 2v2
			sf::Color(103, 58, 183)  // Deep Purple for Guild Wars
		};

		const sf::Color outlineColors[] = {
			sf::Color(191, 54, 12),  // Darker Orange
			sf::Color(173, 20, 87),  // Darker Pink
			sf::Color(69, 39, 160)   // Darker Purple
		};

		const float buttonWidth = 300.0f;
		const float buttonHeight = 70.0f;
		const float buttonSpacing = 40.0f;
		const float startY = (720 - (3 * buttonHeight + 2 * buttonSpacing)) / 2.0f;

		for (int i = 0; i < 3; i++) {
			buttons[i].setSize(sf::Vector2f(buttonWidth, buttonHeight));
			buttons[i].setPosition((1280 - buttonWidth) / 2.0f, startY + i * (buttonHeight + buttonSpacing));
			buttons[i].setFillColor(buttonColors[i]);
			buttons[i].setOutlineThickness(3.0f);
			buttons[i].setOutlineColor(outlineColors[i]);

			buttonTexts[i].setFont(font);
			buttonTexts[i].setString(labels[i]);
			buttonTexts[i].setCharacterSize(36);
			centerTextOnBackground(buttonTexts[i], buttons[i]);
		}
	}

	// Method to reset the menu state
	void reset() {
		nextState = STATE_ARENA;
		isFirstRender = true;
		std::cout << "Arena menu reset" << std::endl;
	}

	void handleInput() {
		// Reset nextState at the beginning of handleInput
		// This is critical - it ensures we don't auto-transition
		nextState = STATE_ARENA;

		// Skip processing input on first render to prevent auto-selection
		if (isFirstRender) {
			isFirstRender = false;
			std::cout << "First arena menu render - skipping input processing" << std::endl;
			return;
		}

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonReleased) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);

				// Check back button
				if (backButton.getGlobalBounds().contains(mousePosF)) {
					nextState = STATE_MODE_SELECT;
					return;
				}

				// Check arena mode buttons
				if (buttons[0].getGlobalBounds().contains(mousePosF)) {
					std::cout << "1v1 button clicked!" << std::endl;
					nextState = STATE_ARENA_SELECT_1V1;
					std::cout << "Setting nextState to: " << nextState << std::endl;
					return;
				}
				else if (buttons[1].getGlobalBounds().contains(mousePosF)) {
					// Function call for 2v2 here
					// gamemanager.setup2v2Match(); // Uncomment when GameManager has this method
					std::cout << "Setting up 2v2 match" << std::endl;
					nextState = STATE_ARENA_SELECT_2V2;
					return;
				}
				else if (buttons[2].getGlobalBounds().contains(mousePosF)) {
					// Function call for Guild Wars here
					// gamemanager.setupGuildWar(); // Uncomment when GameManager has this method
					std::cout << "Setting up Guild War" << std::endl;
					nextState = STATE_ARENA_SELECT_4V4;
					return;
				}
			}
		}
	}

	void draw() {
		window.clear();
		window.draw(backgroundSprite);

		for (int i = 0; i < 3; i++) {
			window.draw(buttons[i]);
			window.draw(buttonTexts[i]);
		}

		window.draw(backButton);
		window.display();
	}
};

class GuildMenu {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture backTexture;
    sf::Sprite backButton;

    sf::RectangleShape buttons[2];  
    sf::Text buttonTexts[2];

public:
    GameState nextState = STATE_GUILD;

    GuildMenu(sf::RenderWindow& win) : window(win) {
        if (!font.loadFromFile("font.ttf")) {
            std::cerr << "Error loading font" << std::endl;
        }

        // Load background
        if (!backgroundTexture.loadFromFile("guild_bg.png")) {
            std::cerr << "Failed to load guild background!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        // Scale background to fill screen
        float scaleX = 1280.0f / backgroundTexture.getSize().x;
        float scaleY = 720.0f / backgroundTexture.getSize().y;
        backgroundSprite.setScale(scaleX, scaleY);

        // Back button at top left corner
        if (!backTexture.loadFromFile("textures/back.png")) {
            std::cerr << "Failed to load back button texture!" << std::endl;
        }
        backButton.setTexture(backTexture);
        backButton.setPosition(20, 20);
        backButton.setScale(0.7f, 0.7f);

        // Buttons - centered on screen
        const std::string labels[] = { "Create Guild", "Join Guild" };
        const sf::Color buttonColors[] = 
        {
            sf::Color(139, 195, 74),  // Light Green for Create Guild
            sf::Color(0, 150, 136)    // Teal for Join Guild
        };

        const sf::Color outlineColors[] = {
            sf::Color(104, 159, 56),  // Darker Green
            sf::Color(0, 121, 107)    // Darker Teal
        };

        const float buttonWidth = 300.0f;
        const float buttonHeight = 70.0f;
        const float buttonSpacing = 60.0f;
        const float startY = (720 - (2 * buttonHeight + buttonSpacing)) / 2.0f;

        for (int i = 0; i < 2; i++) {
            buttons[i].setSize(sf::Vector2f(buttonWidth, buttonHeight));
            buttons[i].setPosition((1280 - buttonWidth) / 2.0f, startY + i * (buttonHeight + buttonSpacing));
            buttons[i].setFillColor(buttonColors[i]);
            buttons[i].setOutlineThickness(3.0f);
            buttons[i].setOutlineColor(outlineColors[i]);

            buttonTexts[i].setFont(font);
            buttonTexts[i].setString(labels[i]);
            buttonTexts[i].setCharacterSize(36);
            centerTextOnBackground(buttonTexts[i], buttons[i]);
        }
    }

    void handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);

                // Check back button
                if (backButton.getGlobalBounds().contains(mousePosF)) {
                    nextState = STATE_MODE_SELECT;
                    return;
                }

                // Check guild option buttons
                for (int i = 0; i < 2; i++) {
                    if (buttons[i].getGlobalBounds().contains(mousePosF)) {
                        nextState = STATE_GAME;
                        return;
                    }
                }
            }
        }
    }

    void draw() {
        window.clear();
        window.draw(backgroundSprite);

        for (int i = 0; i < 2; i++) {
            window.draw(buttons[i]);
            window.draw(buttonTexts[i]);
        }

        window.draw(backButton);
        window.display();
    }

};

class ArenaPetSelect {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture backTexture;
    sf::Sprite backButton;

    sf::Texture petTextures[4];
    sf::Sprite petSprites[4];
    sf::RectangleShape tileOutlines[4];
    bool isHovered[4] = { false };
    bool isSelected[4] = { false };

    sf::RectangleShape confirmButton;
    sf::Text confirmText;

    int maxSelections;
    int currentSelections = 0;
    int selectedPets[4]; // Array to store indices of selected pets (max 4 for 4v4)

public:
    GameState nextState = STATE_ARENA;

    // Method to get the index of a selected pet (returns the pet type)
    int getSelectedPet(int index) {
        if (index >= 0 && index < currentSelections && index < 4) {
            return selectedPets[index];
        }
        return -1; // Invalid index
    }

    ArenaPetSelect(sf::RenderWindow& win, int maxPets = 1, GameState initialState = STATE_ARENA_SELECT_1V1)
        : window(win), maxSelections(maxPets), nextState(initialState)
    {
        // Initialize selectedPets array with -1 (no selection)
        for (int i = 0; i < 4; i++)
        {
            selectedPets[i] = -1;
        }
        // Load font
        if (!font.loadFromFile("font.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        // Load background
        if (!backgroundTexture.loadFromFile("backgrounds/pet_select_bg.png")) {
            std::cerr << "Failed to load pet selection background!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        // Scale background to fill screen
        float scaleX = 1280.0f / backgroundTexture.getSize().x;
        float scaleY = 720.0f / backgroundTexture.getSize().y;
        backgroundSprite.setScale(scaleX, scaleY);

        // Back button at top left corner
        if (!backTexture.loadFromFile("textures/back.png")) {
            std::cerr << "Failed to load back button texture!" << std::endl;
        }

        backButton.setTexture(backTexture);
        backButton.setPosition(20, 20);
        backButton.setScale(0.7f, 0.7f);

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
            petSprites[i].setTexture(petTextures[i]);
        }

        // Calculate grid positions - centered on screen
        const float tileSize = 250.0f;
        const float spacing = 60.0f;

        // Center the 2x2 grid in the screen
        const float gridWidth = 2 * tileSize + spacing;
        const float gridHeight = 2 * tileSize + spacing;
        const float startX = (1280 - gridWidth) / 2.0f;
        const float startY = (720 - gridHeight) / 2.0f - 50; // Shifted up to make room for confirm button

        // Create 2x2 grid
        for (int i = 0; i < 4; i++) {
            // Position calculation
            int row = i / 2;
            int col = i % 2;
            float posX = startX + col * (tileSize + spacing);
            float posY = startY + row * (tileSize + spacing);

            // Configure sprites
            petSprites[i].setPosition(posX, posY);

            // Scale sprites to fit the tile size while maintaining aspect ratio
            float scaleX = tileSize / petSprites[i].getLocalBounds().width;
            float scaleY = tileSize / petSprites[i].getLocalBounds().height;
            float scale = std::min(scaleX, scaleY);
            petSprites[i].setScale(scale, scale);

            // Center the sprite within its tile
            sf::FloatRect spriteBounds = petSprites[i].getLocalBounds();
            float spriteWidth = spriteBounds.width * scale;
            float spriteHeight = spriteBounds.height * scale;
            float offsetX = (tileSize - spriteWidth) / 2.0f;
            float offsetY = (tileSize - spriteHeight) / 2.0f;
            petSprites[i].setPosition(posX + offsetX, posY + offsetY);

            // Configure hover outlines
            tileOutlines[i].setSize(sf::Vector2f(tileSize, tileSize));
            tileOutlines[i].setPosition(posX, posY);
            tileOutlines[i].setFillColor(sf::Color::Transparent);
            tileOutlines[i].setOutlineThickness(4.0f);
            tileOutlines[i].setOutlineColor(sf::Color::Transparent);
        }

        // Confirm button
        confirmButton.setSize(sf::Vector2f(250, 60));
        confirmButton.setPosition((1280 - 250) / 2.0f, 580);
        confirmButton.setFillColor(sf::Color(76, 175, 80)); // Green
        confirmButton.setOutlineThickness(3);
        confirmButton.setOutlineColor(sf::Color(27, 94, 32)); // Dark green

        confirmText.setFont(font);
        confirmText.setString("Confirm");
        confirmText.setCharacterSize(36);
        centerTextOnBackground(confirmText, confirmButton);
    }

    void handleInput()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Handle hover effects
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);

            // Back button interaction
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (backButton.getGlobalBounds().contains(mousePosF))
                {
                    std::cout << "Back button pressed in pet select" << std::endl; // Debug print
                    nextState = STATE_ARENA;
                    return;
                }
                else if (confirmButton.getGlobalBounds().contains(mousePosF) && currentSelections > 0)
                {
                    // Function call to pass selected pets
                    // passSelectedPets(selectedPets);
                    nextState = STATE_GAME;
                    return;
                }
            }

            for (int i = 0; i < 4; i++)
            {
                // Check if mouse is over the tile outline area
                isHovered[i] = tileOutlines[i].getGlobalBounds().contains(mousePosF);

                // Update outline color for hover/selected effect
                if (isSelected[i]) {
                    tileOutlines[i].setOutlineColor(sf::Color(50, 205, 50, 200)); // Lime green for selected
                }
                else {
                    tileOutlines[i].setOutlineColor(
                        isHovered[i] ? sf::Color(255, 215, 0, 200) : sf::Color::Transparent
                    );
                }

                // Handle clicks
                if (event.type == sf::Event::MouseButtonPressed && isHovered[i])
                {
                    if (isSelected[i]) {
                        // Deselect
                        isSelected[i] = false;
                        currentSelections--;

                        for (int j = 0; j < 4; j++) {
                            if (selectedPets[j] == i) {
                                // Shift left from j onward
                                for (int k = j; k < 3; k++) {
                                    selectedPets[k] = selectedPets[k + 1];
                                }
                                selectedPets[3] = -1; // Clear the last slot
                                break;
                            }
                        }
                    }
                    else if (currentSelections < maxSelections) {
                        // Select if not at max
                        isSelected[i] = true;
                        currentSelections++;

                        // Add to first available slot in selectedPets
                        for (int j = 0; j < 4; j++) {
                            if (selectedPets[j] == -1) {
                                selectedPets[j] = i;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    void draw() {
        window.clear();
        window.draw(backgroundSprite);

        // Draw pet tiles
        for (int i = 0; i < 4; i++) {
            window.draw(tileOutlines[i]);  // Draw outline first
            window.draw(petSprites[i]);
        }

        window.draw(backButton);

        // Draw confirm button
        window.draw(confirmButton);
        window.draw(confirmText);

        window.display();
    }
};

class shopScreen {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture backTexture;
    sf::Sprite backButton;

    // Potion textures and sprites
    sf::Texture potionTextures[4];
    sf::Sprite potionSprites[4];
    sf::RectangleShape tileOutlines[4];
    sf::RectangleShape buyButtons[4];

    // Text for potion information
    sf::Text potionNames[4];
    sf::Text potionInfo[4];
    sf::Text buyText[4];

    // Potion quantities owned (will be set externally)
    int potionsOwned[4] = { 0, 0, 0 , 0};

    // Potion prices
    const int potionPrices[4] = { 500, 500, 500, 500 };

    // Potion names
    const std::string potionNameTexts[4] = { "HealingPotion", "Shield", "Buff", "Stamina"};

    bool isHovered[4] = { false };
    bool buttonHovered[4] = { false };

public:
    GameState nextState = STATE_SHOP;

    shopScreen(sf::RenderWindow& win) : window(win) {
        // Load font
        if (!font.loadFromFile("font.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        // Load background
        if (!backgroundTexture.loadFromFile("shop_bg.png")) {
            std::cerr << "Failed to load shop background!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        // Scale background to fill screen
        float scaleX = 1280.0f / backgroundTexture.getSize().x;
        float scaleY = 720.0f / backgroundTexture.getSize().y;
        backgroundSprite.setScale(scaleX, scaleY);

        // Back button at top left corner
        if (!backTexture.loadFromFile("textures/back.png")) {
            std::cerr << "Failed to load back button texture!" << std::endl;
        }
        backButton.setTexture(backTexture);
        backButton.setPosition(20, 20);
        backButton.setScale(0.7f, 0.7f);

        // Load potion textures
        std::string texturePaths[] = {
            "textures/healpot.png",
            "textures/shieldpot.png",
            "textures/buffpot.png",
            "textures/staminapot.png"
        };

        for (int i = 0; i < 4; i++) {
            if (!potionTextures[i].loadFromFile(texturePaths[i])) {
                std::cerr << "Failed to load texture: " << texturePaths[i] << std::endl;
            }
            potionSprites[i].setTexture(potionTextures[i]);
        }

        // Calculate tile positions - centered on screen
        const float tileSize = 200.0f;
        const float spacing = 100.0f;
        const float buttonHeight = 40.0f;
        const float buttonWidth = 150.0f;

        // Center the row of tiles in the screen
        const float totalWidth = 4 * tileSize + 2 * spacing;
        const float startX = (1280 - totalWidth) / 2.0f;
        const float tileY = 200.0f;
        const float nameY = tileY + tileSize + 20.0f;
        const float infoY = nameY + 30.0f;
        const float buttonY = infoY + 30.0f;

        // Create the potion tiles
        for (int i = 0; i < 4; i++) {
            float posX = startX + i * (tileSize + spacing);

            // Configure potion sprites
            potionSprites[i].setPosition(posX, tileY);

            // Scale sprites to fit the tile size while maintaining aspect ratio
            float scaleX = tileSize / potionSprites[i].getLocalBounds().width;
            float scaleY = tileSize / potionSprites[i].getLocalBounds().height;
            float scale = std::min(scaleX, scaleY);
            potionSprites[i].setScale(scale, scale);

            // Center the sprite within its tile
            sf::FloatRect spriteBounds = potionSprites[i].getLocalBounds();
            float spriteWidth = spriteBounds.width * scale;
            float spriteHeight = spriteBounds.height * scale;
            float offsetX = (tileSize - spriteWidth) / 2.0f;
            float offsetY = (tileSize - spriteHeight) / 2.0f;
            potionSprites[i].setPosition(posX + offsetX, tileY + offsetY);

            // Configure tile outlines
            tileOutlines[i].setSize(sf::Vector2f(tileSize, tileSize));
            tileOutlines[i].setPosition(posX, tileY);
            tileOutlines[i].setFillColor(sf::Color::Transparent);
            tileOutlines[i].setOutlineThickness(3.0f);
            tileOutlines[i].setOutlineColor(sf::Color::Transparent);

            // Set potion Counts

            potionsOwned[i] = gamemanager.player->getItemCount(potionNameTexts[i]);

            // Configure potion name text
            potionNames[i].setFont(font);
            potionNames[i].setString(potionNameTexts[i]);
            potionNames[i].setCharacterSize(24);
            potionNames[i].setFillColor(sf::Color::White);
            sf::FloatRect nameRect = potionNames[i].getLocalBounds();
            potionNames[i].setOrigin(nameRect.left + nameRect.width / 2.0f, nameRect.top + nameRect.height / 2.0f);
            potionNames[i].setPosition(posX + tileSize / 2.0f, nameY);

            // Configure potion info text (owned and price)
            potionInfo[i].setFont(font);
            potionInfo[i].setString("Owned: " + std::to_string(potionsOwned[i]) + " Price: " + std::to_string(potionPrices[i]));
            potionInfo[i].setCharacterSize(20);
            potionInfo[i].setFillColor(sf::Color::White);
            sf::FloatRect infoRect = potionInfo[i].getLocalBounds();
            potionInfo[i].setOrigin(infoRect.left + infoRect.width / 2.0f, infoRect.top + infoRect.height / 2.0f);
            potionInfo[i].setPosition(posX + tileSize / 2.0f, infoY);

            // Configure buy buttons
            buyButtons[i].setSize(sf::Vector2f(buttonWidth, buttonHeight));
            buyButtons[i].setPosition(posX + (tileSize - buttonWidth) / 2.0f, buttonY);
            buyButtons[i].setFillColor(sf::Color(76, 175, 80)); // Green
            buyButtons[i].setOutlineThickness(2.0f);
            buyButtons[i].setOutlineColor(sf::Color(27, 94, 32)); // Dark green

            buyText[i].setFont(font);
            buyText[i].setString("Buy");
            buyText[i].setCharacterSize(20);
            centerTextOnBackground(buyText[i], buyButtons[i]);
        }
    }

    // Update the potion quantities (should be called when quantities change)
    void updatePotionQuantities(int healPotions, int shieldPotions, int buffPotions) {
        potionsOwned[0] = healPotions;
        potionsOwned[1] = shieldPotions;
        potionsOwned[2] = buffPotions;

        // Update the display text
        for (int i = 0; i < 3; i++) {
            potionInfo[i].setString("Owned: " + std::to_string(potionsOwned[i]) + " Price: " + std::to_string(potionPrices[i]));
            sf::FloatRect infoRect = potionInfo[i].getLocalBounds();
            potionInfo[i].setOrigin(infoRect.left + infoRect.width / 2.0f, infoRect.top + infoRect.height / 2.0f);
            float posX = tileOutlines[i].getPosition().x;
            float tileSize = tileOutlines[i].getSize().x;
            potionInfo[i].setPosition(posX + tileSize / 2.0f, potionInfo[i].getPosition().y);
        }
    }

    void handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle hover effects
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);

            // Back button interaction
            if (event.type == sf::Event::MouseButtonPressed) {
                if (backButton.getGlobalBounds().contains(mousePosF)) {
                    nextState = STATE_MODE_SELECT;
                    return;
                }
            }

            // Handle potion tile and buy button interactions
            for (int i = 0; i < 4; i++) {
                // Check if mouse is over the tile outline area
                isHovered[i] = tileOutlines[i].getGlobalBounds().contains(mousePosF);
                buttonHovered[i] = buyButtons[i].getGlobalBounds().contains(mousePosF);

                // Update outline colors for hover effect
                tileOutlines[i].setOutlineColor(
                    isHovered[i] ? sf::Color(255, 215, 0, 200) : sf::Color::Transparent
                );

                buyButtons[i].setFillColor(
                    buttonHovered[i] ? sf::Color(129, 199, 132) : sf::Color(76, 175, 80)
                );

                // Handle clicks
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (isHovered[i]) {
                        // Potion tile clicked
                        if (i == 0) {
                            // First tile clicked (Heal Potion)
                            std::cout << "Heal Potion clicked" << std::endl;
                           
                        }
                        else if (i == 1) {
                            // Second tile clicked (Shield Potion)
                            std::cout << "Shield Potion clicked" << std::endl;
                        }
                        else if (i == 2) {
                            // Third tile clicked (Buff Potion)
                            std::cout << "Buff Potion clicked" << std::endl;
                        }
                        else if (i == 3) {
                            // Fourth tile clicked (Buff Potion)
                            std::cout << "Stamina Potion clicked" << std::endl;
                        }
                    }

                    if (buttonHovered[i]) {
                        // Buy button clicked
                        if (i == 0) {
                            // Buy Heal Potion
                            std::cout << "Buy Heal Potion clicked" << std::endl;
                            // Add your purchase logic here
                            gamemanager.player->buyItem("HealingPotion");
                        }
                        else if (i == 1) {
                            // Buy Shield Potion
                            std::cout << "Buy Shield Potion clicked" << std::endl;
                            // Add your purchase logic here
                            gamemanager.player->buyItem("Buff");
                        }
                        else if (i == 2) {
                            // Buy Buff Potion
                            std::cout << "Buy Buff Potion clicked" << std::endl;
                            // Add your purchase logic here
                            gamemanager.player->buyItem("Shield");
                        }
                        else if (i == 3) {
                            // Buy Buff Potion
                            std::cout << "Buy Buff Potion clicked" << std::endl;
                            // Add your purchase logic here
                            gamemanager.player->buyItem("Stamina");
                        }
                    }
                }
            }
        }
    }

    void draw() {
        window.clear();
        window.draw(backgroundSprite);

        // Draw potion tiles and information
        for (int i = 0; i < 4; i++) {
            window.draw(tileOutlines[i]);
            window.draw(potionSprites[i]);
            window.draw(potionNames[i]);
            window.draw(potionInfo[i]);
            window.draw(buyButtons[i]);
            window.draw(buyText[i]);
        }

        window.draw(backButton);
        window.display();
    }
};