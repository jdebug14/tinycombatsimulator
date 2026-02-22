#include "Game.h"
#include "CombatManager.h"
#include <iostream>
#include <vector>

Player& Game::createPlayer() {
    std::string name;
    std::cout << "What is your character's name: ";
    std::getline(std::cin, name);
    player_.emplace(name);
    std::cout << "Welcome " << name << "!\n\n";
    return player_.value();
}

void Game::run() {
    Player& player = createPlayer();
    std::vector<Enemy> enemies { 
        Enemy("trollboy"),
        Enemy("trollgirl"),
        Enemy("trollman", 2, 2, 2, 1, 10),
        Enemy("trollboss", 5, 10, 3, 1, 30)
    };
    int enemiesDefeated = 0;
    while (player.isAlive() && enemiesDefeated < enemies.size()) {
        Enemy& enemy = enemies[enemiesDefeated];
        std::cout << "Combat has begun!\n";
        std::cout << "-----------------------------------------------\n";
        try {
            CombatManager::runCombatEncounter(player, enemy);
            if (!enemy.isAlive()) {
                enemiesDefeated++;
                if (player.isAlive()) {
                    player.gainExperience(enemy.getExperienceGranted());
                }
            }
        } catch(const CombatManager::InvalidCombatException& e) {
            std::cerr << e.what() << std::endl;
        }
        std::cout << "-----------------------------------------------\n\n";
    }

    if (player.isAlive()) std::cout << player.getName() << " defeated all enemies!\n";
    else std::cout << "Game Over.\n";
}