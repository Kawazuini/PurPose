/**
 * @file   Character.cpp
 * @brief  Character
 * @author Maeda Takumi
 */
#include "Character.h"

#include "Device.h"
#include "Item.h"
#include "Stage.h"
#include "Mapping.h"
#include "Wall.h"
#include "Weapon.h"

List<Character*> Character::sCharacters;
Stage* Character::sStage = NULL;
Mapping* Character::sMapDrawer = NULL;

Character::Character() {
    sCharacters.push_back(this);

    KVector pawn = sStage->respawn();
    mBody = KSphere(KVector(pawn.x, 0.0f, pawn.y), 0.0f);
    mDirection = KVector(0.0f, 0.0f, -1.0f);

    mName = "";

    mWeapon = NULL;
    mShield = NULL;
    mEquip1 = NULL;
    mEquip2 = NULL;

    mLevel = mExperience = mRequireExperience = 0;
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

void Character::gainExp(const int& aExp) {
    mExperience += aExp;
    Device::sBulletin.write(mName + "は" + toString(aExp) + "けいけんちをえた。");
    levelUp();
}

void Character::levelUp() {
    for (; mRequireExperience <= mExperience; ++mLevel, mRequireExperience *= 2) {
        Device::sBulletin.write(mName + "はレベルが" + toString(mLevel + 1) + "にあがった。");
    }
}

void Character::damage(Character& aChar, const int& aDamage) {
    mHP = Math::max(0, mHP - aDamage);
    if (aDamage)
        Device::sBulletin.write(mName + "は" + toString(aDamage) + "ダメージをうけた。");
    else Device::sBulletin.write(mName + "にダメージはない。");
    if (!mHP) {
        aChar.gainExp(mExperience);
        die();
    }
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

void Character::setStage(Stage * const aStage) {
    sStage = aStage;
}

void Character::setMap(Mapping * const aMap) {
    sMapDrawer = aMap;
}

void Character::resolveOverlap() {
    // 壁へのめり込みと解消
    List<Wall*> walls = Wall::wallList();
    for (Wall* i : walls) {
        const KPolygon* wall = &(i->polygon());
        KSegment cha(mBody.mPosition + wall->mNormal * mBody.mRadius, mBody.mPosition - wall->mNormal * mBody.mRadius);
        KVector hit = wall->hitPoint(cha);
        if (wall->operator*(hit)) {
            float overlap = mBody.mRadius - (mBody.mPosition - hit).length();
            mBody.mPosition += wall->mNormal * overlap;
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

