#include "Character.h"
#include "CombatManager.h"
#include <iostream>

int main() {
    Player p1("hero");
    Enemy e1("trollboy", 1, 1, 1, 1);
    Enemy e2("trollman", 2, 2, 2, 1);
    Enemy e3("trollboss", 5, 10, 3, 1);
    Enemy e4("trollgirl", 1, 1, 1, 1);
    
    // Combat test 1
    CombatManager::runCombatEncounter(p1, e1);
    std::cout << "-------------------------------\n";
    // Combat test 2
    CombatManager::runCombatEncounter(p1, e2);
    std::cout << "-------------------------------\n";
    // Combat test 3
    CombatManager::runCombatEncounter(p1, e3);
    std::cout << "-------------------------------\n";
    // Combat test 4
    CombatManager::runCombatEncounter(p1, e4);
    std::cout << "-------------------------------\n";

    return 0;
}