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

Character::Character(const int& aID) :
mCharacterParameter(aID),
mTurn(false),
mDirection(KVector(0.0f, 0.0f, -1.0f)),
mBody(mPosition),
mWeapon(NULL),
mShield(NULL),
mHeadEquipment(NULL),
mBodyEquipment(NULL),
mFootEquipment(NULL) {
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
    mPrePosition = mPosition;
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
        KVector dirNorm((aPosition - mPosition).normalization());
        mPosition += dirNorm * mCharacterParameter.mAGI;
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
                + (mPosition - mPrePosition).extractParallel(wallN)
                );
        KVector hit(i->hitPoint(moveP));
        if (i->operator*(hit)) {
            // 壁へのめり込み距離
            float overlap = moveP.length() -(hit - mPrePosition).length() - mBody.mRadius;
            mPosition += wallN * overlap;
        }
    }
    // キャラクター同士のめり込み解消
    for (Character* i : aState.charList()) {
        if (mBody * i->body() && i != this) {
            KVector overlap(mPosition - i->position());
            mPosition = i->position() + overlap.normalization() * (mBody.mRadius + i->size());
        }
    }
}

Item* Character::checkItem(GameState& aState) const {
    float rad(mBody.mRadius + Item::ITEM_SCALE);
    for (Item* i : aState.itemList()) {
        if ((i->position() - mPosition).length() < rad) return i;
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
        Special::add(Special(aItem.mItemParameter.mSpecial, this));
        delete &aItem;
        turnEnd();
    }
}

void Character::equip(GameState& aState, Item& aItem) {
    // 装備箇所の確定
    bool notEquip(false); // 装備箇所がない
    Item ** target(NULL); // 装備箇所
    switch (aItem.mItemParameter.mItemType) {
        case EQUIPMENT_WEAPON: target = &mWeapon;
            break;
        case EQUIPMENT_SHIELD: target = &mShield;
            break;
        case EQUIPMENT_HEAD: target = &mHeadEquipment;
            break;
        case EQUIPMENT_BODY: target = &mBodyEquipment;
            break;
        case EQUIPMENT_FOOT: target = &mFootEquipment;
            break;
        default: notEquip = true;
    }
    // 装備不可(メッセージだけで何も起こらない)
    if (notEquip) {
        aState.mBulletin.write(aItem.mItemParameter.mName + "をそうびできるかしょがない!");
    } else if (!aItem.mItemParameter.mEquippable) {
        aState.mBulletin.write(aItem.mItemParameter.mName + "はそうびできない!");
    } else if (aItem.mItemParameter.mEquipped) {
        aState.mBulletin.write(aItem.mItemParameter.mName + "はすでにそうびしている!");
    } else
        // 装備可能(元装備の解除と装備、ターンの終了)
        if (mTurn) {
        bool equippable(true);
        if (*target) { // 元装備が存在する
            equippable = takeOff(aState, **target, false);
        }

        if (equippable) {
            *target = &aItem; // 装備
            aItem.mItemParameter.mEquipped = true;

            aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.mItemParameter.mName + "をそうびした。");
            turnEnd();
        }
    }
}

bool Character::takeOff(GameState& aState, Item& aItem, const bool& aMessage) {
    if (mTurn) {
        // 装備箇所の確認
        Item ** target(NULL);
        if (mWeapon == &aItem) {
            target = &mWeapon;
        } else if (mShield == &aItem) {
            target = &mShield;
        } else if (mHeadEquipment == &aItem) {
            target = &mHeadEquipment;
        } else if (mBodyEquipment == &aItem) {
            target = &mBodyEquipment;
        } else if (mFootEquipment == &aItem) {
            target = &mFootEquipment;
        } else {
            aState.mBulletin.write(aItem.mItemParameter.mName + "はそうびされていない!");
            return false;
        }

        // 呪われた装備(メッセージのみで何も起きない)
        if (!(*target)->mItemParameter.mTakeoffable) {
            aState.mBulletin.write(aItem.mItemParameter.mName + "はそうびからはずせない!");
            return false;
        }

        // 装備を外す
        (*target)->mItemParameter.mEquipped = false;
        *target = NULL;
        if (aMessage) aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.mItemParameter.mName + "をはずした。");
        turnEnd();
        return true;
    }
    return false;
}

void Character::throwing(GameState& aState, Item& aItem) {
    if (!aItem.mItemParameter.mThrowable) {
        aState.mBulletin.write(aItem.mItemParameter.mName + "はなげられない!");
        return;
    }
    if (mTurn) {
        // 装備してたら装備を外したうえで投げる
        bool throwable(true);
        if (aItem.mItemParameter.mEquipped) {
            throwable = takeOff(aState, aItem, false);
        }
        if (throwable) {
            aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.mItemParameter.mName + "をなげた。");
            aState.addItem(aItem);
            aItem.throwing(*this);
            turnEnd();
        }
    }
}

void Character::setPosition(const GameState& aState, const KVector& aPosition) {
    mPosition = aPosition;
    mPrePosition = aPosition;
    resolveOverlap(aState);
    mPrePosition = mPosition;
    syncPosition();
}

const KSphere& Character::body() const {
    return mBody;
}

KVector Character::position() const {
    return mPosition;
}

KVector Character::direction() const {
    return mDirection;
}

float Character::size() const {
    return mBody.mRadius;
}

