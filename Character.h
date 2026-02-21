#pragma once
#include <string>
#include <iostream>

struct Character {
    Character(const std::string& name, int lvl, int hp, int ap, int dex);
    virtual ~Character() = default;

    const std::string& getName() const;
    int getLevel() const;
    int getHealthPoints() const;
    int getAttackPower() const;
    int getDexterity() const;
    void takeDamage(int dmg);
    bool isAlive() const;
    void attack(Character& target, int turn);

    protected:
        std::string name_;
        int level_;
        int healthPoints_;
        int attackPower_;
        int dexterity_;

    friend std::ostream& operator<<(std::ostream& os, const Character& c);
};

struct Player : Character {
    Player(const std::string& name);
    Player(const std::string& name, int lvl, int hp, int ap, int dex);

    int getExperience() const;
    int getExperienceToNextLevel() const;
    void gainExperience(int exp);
    void levelUp();

    private:
        int experience_;
        int experienceToNextLevel_;

};

struct Enemy : Character {
    Enemy(const std::string& name);
    Enemy(const std::string& name, int lvl, int hp, int ap, int dex);

    int getExperienceGranted() const;

    private:
        int experienceGranted_;
};