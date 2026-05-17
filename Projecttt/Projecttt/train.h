#pragma once
#include <SFML/Graphics.hpp>
#include "menus.h"

const int MAX_TARGETS = 4;
extern GameManager gamemanager;

bool back = false;
class TrainingScreen {
private:
    sf::RenderWindow& window;
    PetType currentPet;
    sf::Texture bgTexture;
    sf::Sprite background;

    sf::Texture targetTexture;
    sf::Sprite targets[MAX_TARGETS];
    int activeTargets = 0;

    sf::Clock animationClock;
    sf::Clock colorResetClocks[MAX_TARGETS]; 
    bool targetColored[MAX_TARGETS] = { false };

    sf::Texture buttonTex;
    sf::Sprite backButton;

public:
    GameState nextState = STATE_TRAINING;

    TrainingScreen(sf::RenderWindow& win, PetType pet)
        : window(win), currentPet(pet) 
    {
     

        // Load common background
        if (!bgTexture.loadFromFile("backgrounds/train_bg.png"))
        {
            std::cout << "Failed to load background texture!" << std::endl;
        }
        background.setTexture(bgTexture);
        background.setScale(
            1280.0f / background.getLocalBounds().width,
            720.0f / background.getLocalBounds().height
        );

        // Load back button
        if (!buttonTex.loadFromFile("textures/back.png"))
        {
            std::cout << "Failed to load back button texture!" << std::endl;
        }
        backButton.setTexture(buttonTex);
        backButton.setPosition(20, 20);
        backButton.setScale(0.7f, 0.7f);


        // Setup targets
        if (currentPet == PHOENIX) 
        {
            if (!targetTexture.loadFromFile("textures/healing_crystal.png"))
            {
                std::cout << "Failed to load healing crystal texture!" << std::endl;
            }
            activeTargets = 4;
            // Position healing crystals horizontally
            for (int i = 0; i < activeTargets; i++)
            {
                targets[i].setTexture(targetTexture);
                targets[i].setPosition(
                    rand() % (1280 - 100) + 50,
                    rand() % (500 - 250) + 100
                );
                targets[i].setScale(0.6f, 0.6f);
            }
        }
        else {
            if (!targetTexture.loadFromFile("textures/target.png"))
            {
                std::cout << "Failed to load target texture!" << std::endl;
            }
            std::cout << "Loading target texture\n";
            activeTargets = 3;
            // Random positions for moving targets
            for (int i = 0; i < activeTargets; i++)
            {
                targets[i].setTexture(targetTexture);
                targets[i].setPosition(
                    rand() % (1280 - 100) + 50,
                    rand() % (500 - 100) + 100
                );
                targets[i].setScale(0.6f, 0.6f);
            }
        }
    }


    void handleInput() 
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords
                (
                    sf::Mouse::getPosition(window)
                );

                // Check back button
                if (backButton.getGlobalBounds().contains(mousePos)) 
                {
                    back = true;
                    std::cout << "backhit\n";
                    nextState = STATE_MODE_SELECT;
                    return;
                }

                // Check targets
                for (int i = 0; i < activeTargets; i++)
                {
                    if (targets[i].getGlobalBounds().contains(mousePos))
                    {
                        // Modify target handling
                        if (currentPet == PHOENIX)
                        {
                            gamemanager.phoenix->trainHealth();
                            gamemanager.phoenix->trainAttack();
                            gamemanager.phoenix->trainSpeed();
                            gamemanager.phoenix->trainDefense();

                            // Add visual feedback
                            targets[i].setColor(sf::Color::Green);
                        }
                        else {
                            if (currentPet == DRAGON)
                            {
                                gamemanager.dragon->trainHealth();
                                gamemanager.dragon->trainAttack();
                                gamemanager.dragon->trainSpeed();
                                gamemanager.dragon->trainDefense();
                            } if (currentPet == GRIFFIN)
                            {
                                gamemanager.griffin->trainHealth();
                                gamemanager.griffin->trainAttack();
                                gamemanager.griffin->trainSpeed();
                                gamemanager.griffin->trainDefense();
                            } if (currentPet == UNICORN)
                            {
                                gamemanager.unicorn->trainHealth();
                                gamemanager.unicorn->trainAttack();
                                gamemanager.unicorn->trainSpeed();
                                gamemanager.unicorn->trainDefense();
                            }
                            // Add visual feedback
                            targets[i].setColor(sf::Color::Red);
                        }
                        colorResetClocks[i].restart();
                        targetColored[i] = true;
                    }
                }
            }
        }
    }


    void update() 
    {
        // Animate targets for non-phoenix
        if (currentPet != PHOENIX && animationClock.getElapsedTime().asSeconds() > 0.5f)
        {
            for (int i = 0; i < activeTargets; i++)
            {
                // Calculate new position with random movement
                float newX = targets[i].getPosition().x + (rand() % 100 - 50);
                float newY = targets[i].getPosition().y + (rand() % 100 - 50);

                // Get screen height
                float screenHeight = 720.0f; // Based on your window size

                // Limit Y position to middle 50% of screen (between 25% and 75% of screen height)
                float minY = screenHeight * 0.25f; // Top of 2nd quarter
                float maxY = screenHeight * 0.75f; // Bottom of 3rd quarter

                // Apply limits
                newY = std::max(minY, std::min(newY, maxY));

                // Also limit X to stay on screen
                float screenWidth = 1280.0f; // Based on your window size
                float targetWidth = targets[i].getGlobalBounds().width;
                newX = std::max(0.0f, std::min(newX, screenWidth - targetWidth));

                // Set new position
                targets[i].setPosition(newX, newY);
            }
            animationClock.restart();
        }

        // Check for targets to reset color
        for (int i = 0; i < activeTargets; i++) 
        {
            if (targetColored[i] && colorResetClocks[i].getElapsedTime().asSeconds() > 0.2f)
            {
                targets[i].setColor(sf::Color::White); // Reset to default color
                targetColored[i] = false;
            }
        }
    }


    void draw() 
    {
        window.clear();
        window.draw(background);
        window.draw(backButton);

        for (int i = 0; i < activeTargets; i++) 
        {
            window.draw(targets[i]);
        }

        window.display();
    }
};