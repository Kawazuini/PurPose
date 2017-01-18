/**
 * @file   Character.cpp
 * @brief  Character
 * @author Maeda Takumi
 */
#include "Character.h"

#include "AI.h"
#include "Action.h"
#include "GameState.h"
#include "Item.h"
#include "Special.h"
#include "Tile.h"
#include "Weapon.h"

List<Character*> Character::sCharacters;

Character::Character() :
mTurn(false),
mAI(AIType::Sloth, *this),
mDirection(KVector(0.0f, 0.0f, -1.0f)),
mWeapon(NULL),
mShield(NULL),
mEquip1(NULL),
mEquip2(NULL) {
    add();
}

Character::~Character() {
    remove();
}

void Character::add() {
    sCharacters.push_back(this);
}

void Character::remove() {
    for (auto i = sCharacters.begin(), i_e = sCharacters.end(); i != i_e; ++i) {
        if (*i == this) {
            sCharacters.erase(i);
            return;
        }
    }
}

void Character::update(GameState& aState) {
    if (mParameter.mDead) {
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
        resolveOverlap();
        syncPosition();
        turnEnd();
    }
}

void Character::resolveOverlap() {
    // 壁へのめり込み解消
    List<KPolygon*> walls = Tile::polyList();
    KVector diff(mBody.mPosition - mPrePosition);
    for (KPolygon* i : walls) {
        KVector veloP((mBody.mPosition - mPrePosition).extractParallel(i->mNormal));
        KVector hit(i->hitPoint(KSegment(
                mPrePosition + (i->mNormal * mBody.mRadius),
                mPrePosition - (i->mNormal * mBody.mRadius) + veloP
                )));
        if (i->operator*(hit)) {
            // 壁へのめり込み距離
            float dist = (hit - mPrePosition).length() - (mBody.mPosition - mPrePosition).length();
            float overlap = mBody.mRadius - dist;
            mBody.mPosition += i->mNormal * overlap;
        }
    }
    // キャラクター同士のめり込み解消
    for (Character* i : sCharacters) {
        if (mBody * i->body() && i != this) {
            KVector overlap = mBody.mPosition - i->position();
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

void Character::die(GameState& aState) {
    aState.mBulletin.write(mParameter.mName + "はたおれた。");
    mParameter.mDead = true;
}

void Character::use(GameState& aState, Item& aItem) {
    if (!aItem.usable()) {
        aState.mBulletin.write(aItem.name() + "はしようできない!");
        return;
    }
    if (mTurn) {
        aState.mBulletin.write(mParameter.mName + "は" + aItem.name() + "をつかった。");
        aItem.use(*this);
        turnEnd();
    }
}

void Character::equip(GameState& aState, Item& aItem) {
    if (!aItem.equippable()) {
        aState.mBulletin.write(aItem.name() + "はそうびできない!");
        return;
    }
    if (mTurn) {
        aState.mBulletin.write(mParameter.mName + "は" + aItem.name() + "をそうびした。");
        aItem.equip(*this);
        turnEnd();
    }
}

void Character::throwing(GameState& aState, Item& aItem) {
    if (!aItem.throwable()) {
        aState.mBulletin.write(aItem.name() + "はなげられない!");
        return;
    }
    if (mTurn) {
        aState.mBulletin.write(mParameter.mName + "は" + aItem.name() + "をなげた。");
        aItem.throwing(*this);
        turnEnd();
    }
}

void Character::equipWeapon(Weapon& aWeapon) {
    mWeapon = &aWeapon;
}

void Character::setPosition(const KVector& aPosition) {
    mBody.mPosition = aPosition;
    mPrePosition = aPosition;
    resolveOverlap();
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

