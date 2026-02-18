#include "Character.h"
#include "CombatManager.h"
#include <iostream>
#include <vector>

int main() {
    std::string playerName;
    std::cout << "What is your character's name: ";
    std::getline(std::cin, playerName);
    std::cout << "Welcome " << playerName << "! Get ready...\n\n\n";

    Player p1(playerName, 1, 10, 1, 1);
    std::vector<Enemy> enemies { 
        Enemy("trollboy"),
        Enemy("trollman", 2, 2, 2, 1),
        Enemy("trollboss", 5, 10, 3, 1),
        Enemy("trollgirl")
     };

    int enemiesFought = 0;
    while (p1.isAlive() && enemiesFought < enemies.size()) {
        Enemy& enemy = enemies[enemiesFought];
        std::cout << "Combat has begun!\n";
        std::cout << "-----------------------------------------------\n";
        std::cout << p1 << "\n***** VS *****\n\n" << enemy << "\n\n";
        try {
            CombatManager::runCombatEncounter(p1, enemy);
            enemiesFought++;
        } catch(const CombatManager::InvalidCombatException& e) {
            std::cerr << e.what() << std::endl;
        }
        std::cout << "-----------------------------------------------\n\n";
    }

    if (p1.isAlive()) std::cout << "You defeated all enemies!\n";
    else std::cout << "Game Over.\n";

    return 0;
}