#include "CombatManager.h"
#include <iostream>
#include <algorithm>
#include <random>

struct CombatManager::CombatAction {
    Character* actor;
    Character* target;
    int initiative;
};

int roll(int rangeStart, int rangeEnd) {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(rangeStart,rangeEnd);
    return dist(rng);
}

void CombatManager::orderByCombatInitiative(std::vector<CombatManager::CombatAction>& actions) {
    std::sort(actions.begin(), actions.end(),
        [](const CombatAction& a, const CombatAction& b) {
            return a.initiative > b.initiative;
        });
}

void CombatManager::runCombatEncounter(Character& c1, Character& c2) {
    if (!c1.isAlive() || !c2.isAlive()) {
        // TODO: throw exception here instead
        std::cerr << "Invalid encounter: one or more characters is already dead.\n";
        return;
    }

    int turn = 0;
    while (c1.isAlive() && c2.isAlive()) {
        turn++;
        std::vector<CombatAction> actions = { 
            { &c1, &c2, c1.getDexterity() + roll(1, 6) },
            { &c2, &c1, c2.getDexterity() + roll(1, 6) }
        };
        orderByCombatInitiative(actions);
        for (const CombatAction& action : actions) {
            Character* actor = action.actor;
            Character* target = action.target;
            if (!actor->isAlive()) continue;
            if (target->isAlive()) {
                actor->attack(*target, turn);
            }
        }
    }
}