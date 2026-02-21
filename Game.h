#pragma once
#include "Character.h"
#include <optional>

class Game {
    public:
        void run();
    private:
        std::optional<Player> player_;

        void createPlayer();
};