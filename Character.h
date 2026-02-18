#pragma once
#include <string>
#include <iostream>

struct Character {
    Character(const std::string& name, int lvl, int hp, int ap, int dex);
    const std::string& getName() const;
    int getLevel() const;
    int getHealthPoints() const;
    int getAttackPower() const;
    int getDexterity() const;
    void attack(Character& target, int turn);
    void takeDamage(int d);
    bool isAlive() const;

    friend std::ostream& operator<<(std::ostream& os, const Character& c);

    private:
        std::string name;
        int level;
        int health_points;
        int attack_power;
        int dexterity;
};

struct Player : Character {
    Player(const std::string& name);
    Player(const std::string& name, int lvl, int hp, int ap, int dex);
};

struct Enemy : Character {
    Enemy(const std::string& name);
    Enemy(const std::string& name, int lvl, int hp, int ap, int dex);
};