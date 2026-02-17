#pragma once
#include "Character.h"
#include <vector>

class CombatManager {
    public:
        static void runCombatEncounter(Character& c1, Character& c2);
    private:
        struct CombatAction;
        static void orderByCombatInitiative(std::vector<CombatAction>& actions);
};