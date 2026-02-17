#include "CombatLogger.h"
#include <iostream>

void CombatLogger::logAttack(const Character& attacker, int turn, const Character& target, int damage) {
    std::cout << "Turn " << turn << ": " << attacker.getName() << " hits " << target.getName() << " for " << damage << " damage\n";
    if (!target.isAlive()) {
        std::cout << target.getName() << " was defeated!" << std::endl;
    }
}