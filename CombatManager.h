#pragma once
#include "Character.h"
#include <vector>

class CombatManager {
    public:
        static void runCombatEncounter(Character& c1, Character& c2);
    private:
        static std::vector<Character*> determineCombatPriority(Character& c1, Character& c2);
};