#pragma once
#include "Character.h"

class CombatLogger {
    public:
        static void logAttack(const Character& attacker, int turn, const Character& target, int damage);
};