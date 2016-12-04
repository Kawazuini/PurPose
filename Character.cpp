/**
 * @file   Character.cpp
 * @brief  Character
 * @author Maeda Takumi
 */
#include "Character.h"

#include "Device.h"
#include "Map.h"
#include "Wall.h"
#include "Item.h"

List<Character*> Character::sCharacters;
Map* Character::sMap = NULL;

Character::Character() {
    sCharacters.push_back(this);

    KVector pawn = sMap->respawn();
    mPosition = KVector(pawn.x, 0.0f, pawn.y);
    mDirection = KVector(0.0f, 0.0f, -1.0f);

    mName = "";
    mSize = 0.0f;

    mMaxHP = mHP = 0;

    mActionPoint = mAgility = 0;
    mMoveCost = mAttackCost = 0;
}

Character::~Character() {
    erase();
}

void Character::add() {
    sCharacters.push_back(this);
}

void Character::erase() {
    for (auto i = sCharacters.begin(), i_e = sCharacters.end(); i != i_e; ++i) {
        if (*i == this) {
            sCharacters.erase(i);
            return;
        }
    }
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

bool Character::isMovable() {
    if (mTurn) {
        if (mActionPoint >= mMoveCost) {
            mActionPoint -= mMoveCost;
            return true;
        }
    }
    return false;
}

bool Character::isAttackable() {
    if (mTurn) {
        if (mActionPoint >= mAttackCost) {
            mActionPoint -= mAttackCost;
            return true;
        }
    }
    return false;
}

void Character::damage(const int& aDamage) {
    mHP = Math::max(0, mHP - aDamage);
    if (aDamage)
        Device::sBulletin.write(mName + "は" + toString(aDamage) + "ダメージをうけた。");
    else Device::sBulletin.write(mName + "にダメージはない。");
    if (!mHP) {
        Device::sBulletin.write(mName + "はたおれた。");
        delete this;
    }
}

void Character::recover(const int& aRecover) {
    mHP = Math::min(mHP + aRecover, mMaxHP);
    Device::sBulletin.write(mName + "のHPは" + toString(aRecover) + "かいふくした。");
}

void Character::use(Item& aItem) {
    int usingCost = aItem.cost();
    if (mTurn) {
        if (mActionPoint >= usingCost) {
            mActionPoint -= usingCost;
            Device::sBulletin.write(mName + "は" + aItem.name() + "をつかった。");
            aItem.use(*this);
        }
    }
}

void Character::setMap(Map * const aMap) {
    sMap = aMap;
}

void Character::resolveOverlap() {
    Array<KPolygon*> walls = Wall::wallList();
    for (KPolygon* i : walls) {
        KSegment cha(mPosition + i->mNormal * mSize, mPosition - i->mNormal * mSize);
        KVector hit = i->hitPoint(cha);
        if (i->operator*(hit)) {
            float length = (mPosition - hit).length();
            float into = mSize - length;
            mPosition += i->mNormal * into;
        }
    }
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

String Character::name() const {
    return mName;
}

float Character::size() const {
    return mSize;
}

