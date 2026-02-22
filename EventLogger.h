#pragma once
#include "Character.h"

class EventLogger {
    public:
        static void logAttack(const Character& attacker, int turn, const Character& target, int damage);
        static void logExperienceGain(const Player& player, int xp);
        static void logLevelUp(const Player& player);
};