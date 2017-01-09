/**
 * @file   Character.cpp
 * @brief  Character
 * @author Maeda Takumi
 */
#include "Character.h"

#include "AI.h"
#include "Action.h"
#include "Device.h"
#include "GameState.h"
#include "Item.h"
#include "Mapping.h"
#include "Stage.h"
#include "Tile.h"
#include "Weapon.h"
#include "Special.h"

List<Character*> Character::sCharacters;

Character::Character() :
mTurn(false),
mAIType(AIType::Sloth),
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

void Character::update(const GameState& aState) {
    if (mTurn) {
        Action act = AI(mAIType).nextAction(aState);
        switch (act.type()) {
            case WAIT: turnEnd();
            case MOVE: move(act.position());
            case ATACK:;
        }
    }

    if (mParameter.mDead) delete this;
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

void Character::move(const KVector& aPosition) {
    if (mTurn) {
        // 移動方向の単位ベクトル
        KVector dirNorm((aPosition - mBody.mPosition).normalization());
        KVector prePos;
        float remainingSpeed = mParameter.mSpeed;
        while (remainingSpeed) { // 移動量が尽きるまで移動(微妙処理)
            float currentSpeed = Math::min(remainingSpeed, mBody.mRadius);
            mBody.mPosition += dirNorm * currentSpeed;
            remainingSpeed -= currentSpeed;
            prePos = mBody.mPosition;
            resolveOverlap();

            if (mBody.mPosition != prePos) break;
        }
        syncPosition();
        turnEnd();
    }
}

void Character::resolveOverlap() {
    // 壁へのめり込み解消
    List<KPolygon*> walls = Tile::polyList();
    for (KPolygon* i : walls) {
        KVector hit = i->hitPoint(KSegment(
                mBody.mPosition + i->mNormal * mBody.mRadius,
                mBody.mPosition - i->mNormal * mBody.mRadius
                ));
        if (i->operator*(hit)) {
            float overlap = mBody.mRadius - (mBody.mPosition - hit).length();
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

void Character::die() {
    Device::sBulletin.write(mParameter.mName + "はたおれた。");
    mParameter.mDead = true;
}

void Character::use(Item& aItem) {
    if (!aItem.usable()) {
        Device::sBulletin.write(aItem.name() + "はしようできない!");
        return;
    }
    if (mTurn) {
        Device::sBulletin.write(mParameter.mName + "は" + aItem.name() + "をつかった。");
        aItem.use(*this);
        turnEnd();
    }
}

void Character::equip(Item& aItem) {
    if (!aItem.equippable()) {
        Device::sBulletin.write(aItem.name() + "はそうびできない!");
        return;
    }
    if (mTurn) {
        Device::sBulletin.write(mParameter.mName + "は" + aItem.name() + "をそうびした。");
        aItem.equip(*this);
        turnEnd();
    }
}

void Character::equipWeapon(Weapon& aWeapon) {
    mWeapon = &aWeapon;
}

void Character::setPosition(const KVector& aPosition) {
    mBody.mPosition = aPosition;
    resolveOverlap();
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

