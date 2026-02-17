#include "CombatManager.h"
#include <iostream>
#include <algorithm>

std::vector<Character*> CombatManager::determineCombatPriority(Character& c1, Character& c2) {
    std::vector<Character*> combatPriority = { &c1, &c2 };
    std::sort(combatPriority.begin(), combatPriority.end(),
        [](Character* a, Character* b) {
            return a->getDexterity() > b->getDexterity();
        });
    return combatPriority;
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
        auto cp = determineCombatPriority(c1, c2);
        for (Character* character : cp) {
            if (!character->isAlive()) continue;
            Character* target = (character == &c1) ? &c2 : &c1;
            if (target->isAlive()) {
                character->attack(*target, turn);
            }
        }
    }
}