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

Vector<Character*> Character::sDrawList;

Character::Character(const int& aID) :
mCharacterParameter(aID),
mTurn(false),
mWaitTurn(0),
mDirection(KVector(0.0f, 0.0f, -1.0f)),
mBody(mPosition, mCharacterParameter.mSize),
mWeapon(NULL),
mShield(NULL),
mHeadEquipment(NULL),
mBodyEquipment(NULL),
mFootEquipment(NULL) {
    sDrawList.push_back(this);
}

Character::~Character() {
    for (auto i = sDrawList.begin(), i_e = sDrawList.end(); i != i_e; ++i) {
        if (this == *i) {
            sDrawList.erase(i);
            break;
        }
    }
}

const void Character::CHARACTER_DRAW(const GameState& aState) {
    const KVector & cameraPosition(aState.mCamera.mPosition);
    // バブルソート(カメラから遠い順に並べる)
    for (int i = 0, i_e = sDrawList.size() - 1; i < i_e; ++i) {
        bool end(true);
        for (int j = i_e; j > i; --j) {
            if ((sDrawList[j - 1]->position() - cameraPosition).lengthSquared() < (sDrawList[j]->position() - cameraPosition).lengthSquared()) {
                Character * tmp(sDrawList[j]);
                sDrawList[j] = sDrawList[j - 1];
                sDrawList[j - 1] = tmp;
                end = false;
            }
        }
        if (end) break; // 一回も更新されなかったら終了
    }

    for (Character* i : sDrawList) {
        if (KCamera::isInCamera(i->direction())) {
            i->draw();
        }
    }
    if ((sDrawList.back()->position() - cameraPosition).isZero()) { // 主人公補正(距離がカメラと一致したときは描画)
        sDrawList.back()->draw();
    }
}

void Character::update(GameState& aState) {
    if (mTurn) {
        if (mWaitTurn > 0) {
            wait();
        } else {
            Action act(mCharacterParameter.mAI.nextAction(aState, *this));
            switch (act.type()) {
                case ACTION_WAIT: wait();
                case ACTION_MOVE: move(aState, act.position());
                case ACTION_ATTACK: attack(aState);
                case ACTION_NOTHING:;
            }
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
    --mWaitTurn;
    turnEnd();
}

void Character::move(GameState& aState, const KVector& aPosition) {
    static const KVector AXIS(0, 1, 0);
    if (mTurn) {
        // 移動方向の単位ベクトル
        KVector dirNorm((aPosition - mPosition).extractVertical(AXIS).normalization());
        mPosition += dirNorm * mCharacterParameter.mAGI + aState.mGravity;
        resolveOverlap(aState);
        syncPosition();
        turnEnd();
    }
}

void Character::resolveOverlap(const GameState& aState) {
    // 壁へのめり込み解消
    for (KPolygon* i : aState.wallList()) {
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
    float rad(mBody.mRadius + Item::PICKABLE_RANGE);
    for (Item* i : aState.itemList()) {
        if ((i->mEntity.position() - mPosition).length() < rad) return i;
    }
    return NULL;
}

void Character::attack(GameState& aState) {
    if (mTurn) {
        int cost(mCharacterParameter.mAttackCost);
        if (mWeapon) cost += mWeapon->param().mCost;
        mWaitTurn = cost;
    }
}

void Character::use(GameState& aState, Item& aItem) {
    if (!aItem.param().mUsable) {
        aState.mBulletin.write(aItem.param().mName + "は使用できない!");
        return;
    }
    if (mTurn) {
        aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.param().mName + "を使った。");
        Special::add(Special(aItem.param().mSpecial, this));
        mWaitTurn = aItem.param().mCost;
        delete &aItem;
        turnEnd();
    }
}

void Character::equip(GameState& aState, Item& aItem) {
    // 装備箇所の確定
    bool notEquip(false); // 装備箇所がない
    Item ** target(NULL); // 装備箇所
    switch (aItem.param().mItemType) {
        case WEAPON_SWORD:
        case WEAPON_BOW:
        case WEAPON_GUN:
            target = &mWeapon;
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
        aState.mBulletin.write(aItem.param().mName + "を装備できる箇所がない!");
    } else if (!aItem.param().mEquippable) {
        aState.mBulletin.write(aItem.param().mName + "は装備できない!");
    } else if (aItem.mEquipped) {
        aState.mBulletin.write(aItem.param().mName + "は既に装備している!");
    } else
        // 装備可能(元装備の解除と装備、ターンの終了)
        if (mTurn) {
        bool equippable(true);
        if (*target) { // 元装備が存在する
            equippable = takeOff(aState, **target, false);
        }

        if (equippable) {
            *target = &aItem; // 装備
            aItem.mEquipped = true;

            aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.param().mName + "を装備した。");
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
            aState.mBulletin.write(aItem.param().mName + "は装備されていない!");
            return false;
        }

        // 呪われた装備(メッセージのみで何も起きない)
        if (!(*target)->mTakeoffable) {
            aState.mBulletin.write(aItem.param().mName + "は装備から外せない!");
            return false;
        }

        // 装備を外す
        (*target)->mEquipped = false;
        *target = NULL;
        if (aMessage) aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.param().mName + "を外した。");
        turnEnd();
        return true;
    }
    return false;
}

void Character::throwing(GameState& aState, Item& aItem) {
    if (mTurn) {
        // 装備してたら装備を外したうえで投げる
        bool throwable(true);
        if (aItem.mEquipped) {
            throwable = takeOff(aState, aItem, false);
        }
        if (throwable) {
            aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.param().mName + "を投げた。");
            aState.addItem(aItem);
            {
                aItem.embody();
                aItem.mEntity.setPosition(mPosition + mDirection * (mCharacterParameter.mSize + aItem.mEntity.radius()));
                aItem.mEntity.applyForce(mDirection * mCharacterParameter.throwPower());
                aItem.mOwener = this;
            }
            turnEnd();
        }
    }
}

void Character::putting(GameState& aState, Item& aItem) {
    static const KVector AXIS(0, 1, 0);
    if (mTurn) {
        // 装備してたら装備を外したうえで投げる
        bool throwable(true);
        if (aItem.mEquipped) {
            throwable = takeOff(aState, aItem, false);
        }
        if (throwable) {
            aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.param().mName + "を置いた。");
            aState.addItem(aItem);
            {
                aItem.embody();
                KVector horizon(mDirection.extractVertical(AXIS).normalization());
                KVector putPosition(mPosition + horizon * (mCharacterParameter.mSize + aItem.mEntity.radius()));
                aItem.mEntity.setPosition(KVector(putPosition.x, 0, putPosition.z));
            }
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

const KVector& Character::position() const {
    return mPosition;
}

const KVector& Character::direction() const {
    return mDirection;
}

float Character::size() const {
    return mBody.mRadius;
}

const Item * Character::weapon() const {
    return mWeapon;
}

const Item * Character::shield() const {
    return mShield;
}

const Item * Character::headEquipment() const {
    return mHeadEquipment;
}

const Item * Character::bodyEquipment() const {
    return mBodyEquipment;
}

const Item * Character::footEquipment() const {
    return mFootEquipment;
}

