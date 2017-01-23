/**
 * @file   Character.cpp
 * @brief  Character
 * @author Maeda Takumi
 */
#include "Character.h"

#include "Action.h"
#include "GameState.h"
#include "Item.h"
#include "Special.h"
#include "Tile.h"
#include "Weapon.h"

Character::Character() :
mTurn(false),
mDirection(KVector(0.0f, 0.0f, -1.0f)),
mWeapon(NULL),
mShield(NULL),
mEquip1(NULL),
mEquip2(NULL) {
}

Character::Character(const int& aID) :
mCharacterParameter(aID),
mDirection(KVector(0.0f, 0.0f, -1.0f)),
mWeapon(NULL),
mShield(NULL),
mEquip1(NULL),
mEquip2(NULL) {
}

void Character::update(GameState& aState) {
    if (mTurn) {
        Action act = mCharacterParameter.mAI.nextAction(aState, *this);
        switch (act.type()) {
            case WAIT: wait();
            case MOVE: move(aState, act.position());
            case ATTACK: attack(aState);
        }
    }
    mPrePosition = mBody.mPosition;
}

void Character::turnStart() {
    mTurn = true;
}

void Character::turnEnd() {
    mTurn = false;
}

bool Character::turn() const {
    return mTurn;
}

void Character::wait() {
    turnEnd();
}

void Character::move(GameState& aState, const KVector& aPosition) {
    if (mTurn) {
        // 移動方向の単位ベクトル
        KVector dirNorm((aPosition - mBody.mPosition).normalization());
        mBody.mPosition += dirNorm * mCharacterParameter.mAGI;
        resolveOverlap(aState);
        syncPosition();
        turnEnd();
    }
}

void Character::resolveOverlap(const GameState& aState) {
    // 壁へのめり込み解消
    for (KPolygon* i : Tile::polyList()) {
        KVector wallN(i->mNormal); // 壁の法線
        KSegment moveP(// 壁に垂直な移動線分
                mPrePosition + (wallN * mBody.mRadius),
                mPrePosition - (wallN * mBody.mRadius)
                + (mBody.mPosition - mPrePosition).extractParallel(wallN)
                );
        KVector hit(i->hitPoint(moveP));
        if (i->operator*(hit)) {
            // 壁へのめり込み距離
            float overlap = moveP.length() -(hit - mPrePosition).length() - mBody.mRadius;
            mBody.mPosition += wallN * overlap;
        }
    }
    // キャラクター同士のめり込み解消
    for (Character* i : aState.charList()) {
        if (mBody * i->body() && i != this) {
            KVector overlap(mBody.mPosition - i->position());
            mBody.mPosition = i->position() + overlap.normalization() * (mBody.mRadius + i->size());
        }
    }
}

Item* Character::checkItem(GameState& aState) const {
    float rad(mBody.mRadius + Item::ITEM_SCALE);
    for (Item* i : aState.itemList()) {
        if ((i->position() - mBody.mPosition).length() < rad) return i;
    }
    return NULL;
}

void Character::use(GameState& aState, Item& aItem) {
    if (!aItem.mItemParameter.mUsable) {
        aState.mBulletin.write(aItem.mItemParameter.mName + "はしようできない!");
        return;
    }
    if (mTurn) {
        aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.mItemParameter.mName + "をつかった。");
        aItem.use(*this);
        turnEnd();
    }
}

void Character::equip(GameState& aState, Item& aItem) {
    if (!aItem.mItemParameter.mEquippable) {
        aState.mBulletin.write(aItem.mItemParameter.mName + "はそうびできない!");
        return;
    }
    if (mTurn) {
        aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.mItemParameter.mName + "をそうびした。");
        aItem.equip(*this);
        turnEnd();
    }
}

void Character::throwing(GameState& aState, Item& aItem) {
    if (!aItem.mItemParameter.mThrowable) {
        aState.mBulletin.write(aItem.mItemParameter.mName + "はなげられない!");
        return;
    }
    if (mTurn) {
        aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.mItemParameter.mName + "をなげた。");
        aState.addItem(aItem);
        aItem.throwing(*this);
        turnEnd();
    }
}

void Character::equipWeapon(Weapon& aWeapon) {
    mWeapon = &aWeapon;
}

void Character::setPosition(const GameState& aState, const KVector& aPosition) {
    mBody.mPosition = aPosition;
    mPrePosition = aPosition;
    resolveOverlap(aState);
    mPrePosition = mBody.mPosition;
    syncPosition();
}

const KSphere& Character::body() const {
    return mBody;
}

KVector Character::position() const {
    return mBody.mPosition;
}

KVector Character::direction() const {
    return mDirection;
}

float Character::size() const {
    return mBody.mRadius;
}

