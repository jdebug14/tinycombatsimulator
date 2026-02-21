#include "Character.h"
#include "CombatLogger.h"

Character::Character(const std::string& name, int lvl, int hp, int ap, int dex) 
    : name_(name),
    level_(lvl),
    healthPoints_(hp),
    attackPower_(ap),
    dexterity_(dex) {}

const std::string& Character::getName() const {
    return name_;
}

int Character::getHealthPoints() const {
    return healthPoints_;
}

int Character::getLevel() const {
    return level_;
}

int Character::getAttackPower() const {
    return attackPower_;
}

int Character::getDexterity() const {
    return dexterity_;
}

bool Character::isAlive() const {
    return healthPoints_ > 0;
}

void Character::takeDamage(int d) {
    healthPoints_ -= d;
    if (healthPoints_ < 0) healthPoints_ = 0;
}

void Character::attack(Character& target, int turn) {
    if (!isAlive()) return;
    int damage = attackPower_;
    target.takeDamage(damage);
    CombatLogger::logAttack(*this, turn, target, damage);
}

std::ostream& operator<<(std::ostream& os, const Character& c) {
    os << "Name: " << c.name_ << "\n"
       << "Level: " << c.level_ << "\n"
       << "HP: " << c.healthPoints_ << "\n"
       << "Attack: " << c.attackPower_ << "\n"
       << "Dexterity: " << c.dexterity_ << "\n";
    return os;
}

// Player
Player::Player(const std::string& name) : Character(name, 1, 5, 1, 1) {}
Player::Player(const std::string& name, int lvl, int hp, int ap, int dex) : Character(name, lvl, hp, ap, dex) {}

void Player::levelUp() {
    if (!isAlive()) return;
    level_++;
    healthPoints_ += 3;
    attackPower_ += 1;
    dexterity_ += 1;
    experienceToNextLevel_ += 50;
    std::cout << name_ << " leveled up to " << level_ << "!\n";
}

void Player::gainExperience(int exp) {
    if (!isAlive()) return;
    experience_ += exp;
    while (experience_ + exp >= experienceToNextLevel_) {
        levelUp();
    } 
}

// Enemy
Enemy::Enemy(const std::string& name) : Character(name, 1, 1, 1, 1) {}
Enemy::Enemy(const std::string& name, int lvl, int hp, int ap, int dex) : Character(name, lvl, hp, ap, dex) {}

int Enemy::getExperienceGranted() const {
    return experienceGranted_;
}