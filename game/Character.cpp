#include "Character.h"
#include "EventLogger.h"

Character::Character(const std::string& name, int lvl, int hp, int ap, int dex) 
    : name_(name),
    level_(lvl),
    maxHealthPoints_(hp),
    currentHealthPoints_(hp),
    attackPower_(ap),
    dexterity_(dex) {}

const std::string& Character::getName() const {
    return name_;
}

int Character::getHealthPoints() const {
    return currentHealthPoints_;
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
    return currentHealthPoints_ > 0;
}

void Character::takeDamage(int dmg) {
    currentHealthPoints_ -= dmg;
    if (currentHealthPoints_ < 0) currentHealthPoints_ = 0;
}

void Character::attack(Character& target, int turn) {
    if (!isAlive()) return;
    int damage = attackPower_;
    target.takeDamage(damage);
    EventLogger::logAttack(*this, turn, target, damage);
}

std::ostream& operator<<(std::ostream& os, const Character& c) {
    os << "Name: " << c.name_ << "\n"
       << "Level: " << c.level_ << "\n"
       << "HP: " << c.currentHealthPoints_ << "/" << c.maxHealthPoints_ << "\n"
       << "Attack: " << c.attackPower_ << "\n"
       << "Dexterity: " << c.dexterity_ << "\n";
    return os;
}

// Player
Player::Player(const std::string& name) : Character(name, 1, 5, 1, 1), experience_(0), experienceToNextLevel_(10) {}

void Player::gainExperience(int xp) {
    if (!isAlive()) return;
    EventLogger::logExperienceGain(*this, xp);
    experience_ += xp;
    while (experience_ >= experienceToNextLevel_) {
        levelUp();
    } 
}

void Player::levelUp() {
    if (!isAlive()) return;
    level_++;
    maxHealthPoints_ += 3;
    currentHealthPoints_ = maxHealthPoints_;
    attackPower_ += 1;
    dexterity_ += 1;
    experienceToNextLevel_ += 10;
    EventLogger::logLevelUp(*this);
}

// Enemy
Enemy::Enemy(const std::string& name) : Character(name, 1, 1, 1, 1), experienceGranted_(5) {}
Enemy::Enemy(const std::string& name, int lvl, int hp, int ap, int dex, int xp) : Character(name, lvl, hp, ap, dex), experienceGranted_(xp) {}

int Enemy::getExperienceGranted() const {
    return experienceGranted_;
}