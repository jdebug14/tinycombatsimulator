#pragma once
#include "Character.h"
#include <vector>
#include <string>
#include <stdexcept>

class CombatManager {
    public:
        class InvalidCombatException : public std::runtime_error {
            public:
                InvalidCombatException(const std::string& msg) : std::runtime_error(msg) {}
        };
        static void runCombatEncounter(Character& c1, Character& c2);
    private:
        struct CombatAction;
        static void orderByCombatInitiative(std::vector<CombatAction>& actions);
};