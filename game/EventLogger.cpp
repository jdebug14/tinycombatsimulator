#include "EventLogger.h"
#include <iostream>

void EventLogger::logAttack(const Character& attacker, int turn, const Character& target, int damage) {
    // TODO: show Character stats if advanced debugging enabled
    std::cout << "Turn " << turn << ": " << attacker.getName() << " hits " << target.getName() << " for " << damage << " damage\n";
    if (!target.isAlive()) {
        std::cout << target.getName() << " was defeated!" << std::endl;
    }
}

void EventLogger::logExperienceGain(const Player& player, int xp) {
    std::cout << player.getName() 
              << " gained "
              << xp
              << " experience!\n";
}

void EventLogger::logLevelUp(const Player& player) {
    std::cout << player.getName()
              << " is now level "
              << player.getLevel()
              << "!\n"
              << player;
}