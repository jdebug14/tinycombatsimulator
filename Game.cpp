#include "Game.h"
#include "CombatManager.h"
#include <iostream>
#include <vector>

void Game::createPlayer() {
    std::string name;
    std::cout << "What is your character's name: ";
    std::getline(std::cin, name);
    player_.emplace(name);
    std::cout << "Welcome " << name << "!\n\n";
}

void Game::run() {
    createPlayer();
    std::vector<Enemy> enemies { 
        Enemy("trollboy"),
        Enemy("trollman", 2, 2, 2, 1),
        Enemy("trollboss", 5, 10, 3, 1),
        Enemy("trollgirl")
    };
    int enemiesFought = 0;
    while (player_.value().isAlive() && enemiesFought < enemies.size()) {
        Enemy& enemy = enemies[enemiesFought];
        std::cout << "Combat has begun!\n";
        std::cout << "-----------------------------------------------\n";
        std::cout << *player_ << "\n***** VS *****\n\n" << enemy << "\n\n";
        try {
            CombatManager::runCombatEncounter(*player_, enemy);
            enemiesFought++;
        } catch(const CombatManager::InvalidCombatException& e) {
            std::cerr << e.what() << std::endl;
        }
        std::cout << "-----------------------------------------------\n\n";
    }

    if (player_.value().isAlive()) std::cout << "You defeated all enemies!\n";
    else std::cout << "Game Over.\n";
}