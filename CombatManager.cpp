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
        throw InvalidCombatException("One or more characters are unable to fight.");
    }

    int turn = 0;
    while (c1.isAlive() && c2.isAlive()) {
        turn++;
        // TODO: ideally something more elegant than a d6 roll, but it's enough to introduce some variance for now
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