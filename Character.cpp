/**
 * @file   Character.cpp
 * @brief  Character
 * @author Maeda Takumi
 */
#include "Character.h"

#include "Device.h"
#include "Item.h"
#include "Map.h"
#include "Wall.h"
#include "Weapon.h"

List<Character*> Character::sCharacters;
Map* Character::sMap = NULL;

Character::Character() {
    sCharacters.push_back(this);

    KVector pawn = sMap->respawn();
    mBody = KSphere(KVector(pawn.x, 0.0f, pawn.y), 0.0f);
    mDirection = KVector(0.0f, 0.0f, -1.0f);

    mName = "";

    mWeapon = NULL;
    mShield = NULL;
    mEquip1 = NULL;
    mEquip2 = NULL;

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
    if (!mHP) die();
}

void Character::recover(const int& aRecover) {
    mHP = Math::min(mHP + aRecover, mMaxHP);
    Device::sBulletin.write(mName + "のHPは" + toString(aRecover) + "かいふくした。");
}

void Character::die() {
    Device::sBulletin.write(mName + "はたおれた。");
    delete this;
}

void Character::use(Item& aItem) {
    if (!aItem.usable()) {
        Device::sBulletin.write(aItem.name() + "はしようできない!");
        return;
    }
    int usingCost = aItem.useCost();
    if (mTurn) {
        if (mActionPoint >= usingCost) {
            mActionPoint -= usingCost;
            Device::sBulletin.write(mName + "は" + aItem.name() + "をつかった。");
            aItem.use(*this);
        }
    }
}

void Character::equip(Item& aItem) {
    if (!aItem.equippable()) {
        Device::sBulletin.write(aItem.name() + "はそうびできない!");
        return;
    }
    int equippingCost = aItem.equipCost();
    if (mTurn) {
        if (mActionPoint >= equippingCost) {
            mActionPoint -= equippingCost;
            Device::sBulletin.write(mName + "は" + aItem.name() + "をそうびした。");
            aItem.equip(*this);
        }
    }
}

void Character::equipWeapon(Weapon& aWeapon) {
    mWeapon = &aWeapon;
}

void Character::setMap(Map * const aMap) {
    sMap = aMap;
}

void Character::resolveOverlap() {
    // 壁へのめり込みと解消
    Array<KPolygon*> walls = Wall::wallList();
    for (KPolygon* i : walls) {
        KSegment cha(mBody.mPosition + i->mNormal * mBody.mRadius, mBody.mPosition - i->mNormal * mBody.mRadius);
        KVector hit = i->hitPoint(cha);
        if (i->operator*(hit)) {
            float overlap = mBody.mRadius - (mBody.mPosition - hit).length();
            mBody.mPosition += i->mNormal * overlap;
        }
    }
    // キャラクター同士のめり込みと解消
    for (Character* i : sCharacters) {
        if (mBody * i->body() && i != this) {
            KVector overlap = mBody.mPosition - i->position();
            mBody.mPosition = i->position() + overlap.normalization() * (mBody.mRadius + i->size());
        }
    }
}

void Character::setPosition(const KVector& aPosition) {
    mBody.mPosition = aPosition;
}

KSphere Character::body() const {
    return mBody;
}

KVector Character::position() const {
    return mBody.mPosition;
}

KVector Character::direction() const {
    return mDirection;
}

String Character::name() const {
    return mName;
}

float Character::size() const {
    return mBody.mRadius;
}

