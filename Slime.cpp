/**
 * @file Slime.cpp
 * @brief Slime
 */
#include "Slime.h"

Slime::Slime()
: Enemy("S", 0x7700ff00) {
    mSpeed = 0.2;
    mAgility = 12;
    mMoveCost = 1;
    mActionPoint = 0;
}

Slime::~Slime() {
    delete mTexture;
}

void Slime::update(const KVector& aPlayer) {
    Enemy::update(aPlayer);
    Enemy::move(mDirection * mSpeed);
}
