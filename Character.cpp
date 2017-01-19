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

Character::Character(GameState& aState) :
Character(aState.mCharacters) {
}

Character::Character(List<Character*>& aList) :
mTurn(false),
mAI(AIType::Sloth, *this),
mDirection(KVector(0.0f, 0.0f, -1.0f)),
mWeapon(NULL),
mShield(NULL),
mEquip1(NULL),
mEquip2(NULL) {
    aList.push_back(this);
}

void Character::die(GameState& aState) {
    for (auto i = aState.mCharacters.begin(), i_e = aState.mCharacters.end(); i != i_e; ++i) {
        if (*i == this) {
            aState.mCharacters.erase(i);
            return;
        }
    }
}

void Character::update(GameState& aState) {
    if (mParameter.mDead) {
        die(aState);
        delete this;
        return;
    }
    if (mTurn) {
        Action act = mAI.nextAction(aState);
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
        mBody.mPosition += dirNorm * mParameter.mSpeed;
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
    for (Character* i : aState.mCharacters) {
        if (mBody * i->body() && i != this) {
            KVector overlap(mBody.mPosition - i->position());
            mBody.mPosition = i->position() + overlap.normalization() * (mBody.mRadius + i->size());
        }
    }
}

Item* Character::checkItem() const {
    List<Item*> list = Item::itemList();
    float rad = mBody.mRadius + Item::ITEM_SCALE;
    for (Item* i : list) {
        if ((i->position() - mBody.mPosition).length() < rad) return i;
    }
    return NULL;
}

void Character::use(GameState& aState, Item& aItem) {
    if (!aItem.usable()) {
        aState.mBulletin.write(aItem.mParameter.mName + "はしようできない!");
        return;
    }
    if (mTurn) {
        aState.mBulletin.write(mParameter.mName + "は" + aItem.mParameter.mName + "をつかった。");
        aItem.use(*this);
        turnEnd();
    }
}

void Character::equip(GameState& aState, Item& aItem) {
    if (!aItem.equippable()) {
        aState.mBulletin.write(aItem.mParameter.mName + "はそうびできない!");
        return;
    }
    if (mTurn) {
        aState.mBulletin.write(mParameter.mName + "は" + aItem.mParameter.mName + "をそうびした。");
        aItem.equip(*this);
        turnEnd();
    }
}

void Character::throwing(GameState& aState, Item& aItem) {
    if (!aItem.throwable()) {
        aState.mBulletin.write(aItem.mParameter.mName + "はなげられない!");
        return;
    }
    if (mTurn) {
        aState.mBulletin.write(mParameter.mName + "は" + aItem.mParameter.mName + "をなげた。");
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

bool Character::dead() const {
    return mParameter.mDead;
}

float Character::size() const {
    return mBody.mRadius;
}

