/**
 * @file Character.cpp
 * @brief Character
 */
#include "Character.h"

#include "Map.h"

Map* Character::sMap = NULL;

Character::Character() {
    KVector pawn = sMap->respawn();
    mPosition = KVector(pawn.x, 0, pawn.y);
}

Character::~Character() {
}

void Character::setMap(Map * const aMap) {
    sMap = aMap;
}

void Character::update() {
    if (mTurn && mActionPoint <= 0) turnEnd();
}

void Character::turnStart() {
    mTurn = true;
    mActionPoint = mAgility;
}

void Character::turnEnd() {
    mTurn = false;
}

bool Character::turn() const {
    return mTurn;
}

bool Character::move(const KVector& aMovement) {
    if (mTurn) {
        if (mActionPoint >= mMoveCost) {
            mActionPoint -= mMoveCost;
            mPosition += aMovement.normalization() * mSpeed;
            return true;
        }
    }
    return false;
}

bool Character::atack() {
    if (mTurn) {
        if (mActionPoint >= mAtackCost) {
            mActionPoint -= mAtackCost;
            return true;
        }
    }
    return false;
}

void Character::setPosition(const KVector& aPosition) {
    mPosition = aPosition;
}

KVector Character::position() const {
    return mPosition;
}

KVector Character::direction() const {
    return mDirection;
}
