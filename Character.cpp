#include "Character.h"
#include "CombatLogger.h"

Character::Character(const std::string& name, int hp, int ap, int dex) 
    : name(name),
    health_points(hp),
    attack_power(ap),
    dexterity(dex) {}
Player::Player(const std::string& name) : Character(name, 5, 1, 2) {}
Enemy::Enemy() : Character("Creep", 1, 1, 1) {}
Enemy::Enemy(const std::string& name, int hp, int ap, int dex) : Character(name, hp, ap, dex) {}

const std::string& Character::getName() const {
    return name;
}

int Character::getHealthPoints() const {
    return health_points;
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