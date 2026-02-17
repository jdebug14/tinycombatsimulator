#pragma once
#include <string>

struct Character {
    Character(const std::string& name, int hp, int ap, int dex);
    const std::string& getName() const;
    int getHealthPoints() const;
    int getAttackPower() const;
    int getDexterity() const;
    void attack(Character& target, int turn);
    void takeDamage(int d);
    bool isAlive() const;

    private:
        std::string name;
        int health_points;
        int attack_power;
        int dexterity;
};

struct Player : Character {
    Player(const std::string& name);
};

struct Enemy : Character {
    Enemy();
    Enemy(const std::string& name, int hp, int ap, int dex);
};