#include "Character.h"
#include "CombatLogger.h"

Character::Character(const std::string& name, int lvl, int hp, int ap, int dex) 
    : name(name),
    level(lvl),
    health_points(hp),
    attack_power(ap),
    dexterity(dex) {}
Player::Player(const std::string& name) : Character(name, 1, 5, 1, 1) {}
Enemy::Enemy() : Character("Creep", 1, 1, 1, 1) {}
Enemy::Enemy(const std::string& name, int lvl, int hp, int ap, int dex) : Character(name, lvl, hp, ap, dex) {}

const std::string& Character::getName() const {
    return name;
}

int Character::getHealthPoints() const {
    return health_points;
}

int Character::getLevel() const {
    return level;
}

int Character::getAttackPower() const {
    return attack_power;
}

int Character::getDexterity() const {
    return dexterity;
}

bool Character::isAlive() const {
    return health_points > 0;
}

void Character::takeDamage(int d) {
    health_points -= d;
    if (health_points < 0) health_points = 0;
}

void Character::attack(Character& target, int turn) {
    if (!isAlive()) return;
    int damage = attack_power;
    target.takeDamage(damage);
    CombatLogger::logAttack(*this, turn, target, damage);
}