/**
 * @file   Hero.cpp
 * @brief  Hero
 * @author Maeda Takumi
 */
#include "Hero.h"

#include "GameState.h"
#include "HPotion.h"
#include "Special.h"
#include "Sword.h"
#include "TelePotion.h"

Hero::Hero(List<Character*>& aList) :
Character(aList) {
    reset();
}

Hero::~Hero() {
}

void Hero::update(GameState& aState) {
    light.mPosition = mEyeCamera.mPosition;
    light.mDirection = mEyeCamera.mDirection;
    light.at();

    mPrePosition = mBody.mPosition;
}

void Hero::reset() {
    mCharacterParameter.mDead = false;
    mCharacterParameter.mName = "ぼく";
    mCharacterParameter.mAGI = 1.0f;
    mCharacterParameter.mAttackRange = 5;
    mCharacterParameter.mLevel = 1;
    mCharacterParameter.mRequireExperience = 1;
    mCharacterParameter.mHP = mCharacterParameter.mMHP = 10;
    mCharacterParameter.mSTR = 100;

    mBody.mRadius = 1.5;

    mPunchAngle = 30.0f / 180 * Math::PI;

    mClear = false;

    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new TelePotion());
    mBackPack.add(new TelePotion());
    mBackPack.add(new Sword());
}

void Hero::newFloar(GameState& aState) {
    mClear = false;
    setPosition(aState, aState.respawn());
}

void Hero::move(GameState& aState, const KVector& aDirection) {
    Character::move(aState, mEyeCamera.convertDirection(aDirection) + position());

    // アイテムを拾う
    Item* tmp = checkItem();
    if (tmp) {
        if (tmp->pickable()) {
            pickUp(aState, tmp);
            tmp->hide();
        }
    }
}

void Hero::syncPosition() {
    mEyeCamera.mPosition = mBody.mPosition;
    mEyeCamera.set();
}

void Hero::attack(GameState& aState) {
    if (mTurn) {
        aState.mBulletin.write(mCharacterParameter.mName + "のこうげき!");
        punch(aState);
        turnEnd();
    }
}

void Hero::punch(GameState& aState) {
    bool hit = false;
    KSphere reach(mBody.mPosition, mBody.mRadius + mCharacterParameter.mAttackRange);

    for (Character* i : aState.mCharacters) {
        if (i != this) { // 自分は殴らない。
            if (reach * i->body()) {
                if ((i->position() - mBody.mPosition).angle(mDirection) < mPunchAngle) {
                    Special::Damage(*this, *i, 10);
                    hit = true;
                }
            }
        }
    }
    if (!hit) aState.mBulletin.write(mCharacterParameter.mName + "はからぶりしてしまった。");
}

void Hero::swivel(const float& aAngleV, const float& aAngleH) {
    mEyeCamera.rotate(aAngleV, aAngleH);
    mDirection = mEyeCamera.mDirection;
}

void Hero::pickUp(GameState& aState, Item * const aItem) {
    mBackPack.add(aItem);
    aState.mBulletin.write(aItem->mItemParameter.mName + "をひろった。");
}

void Hero::fumble(const int& aAmount) {
    mBackPack.selectChange(aAmount);
}

void Hero::useItem(GameState& aState) {
    Item* item = mBackPack.lookAt();
    if (item) {
        if (item->usable()) item = mBackPack.takeOut();
        use(aState, *item);
    }
}

void Hero::equipItem(GameState& aState) {
    Item* item = mBackPack.lookAt();
    if (item) equip(aState, *item);
}

void Hero::throwItem(GameState& aState) {
    Item* item = mBackPack.lookAt();
    if (item) {
        if (item->throwable()) item = mBackPack.takeOut();
        throwing(aState, *item);
    }
}

bool Hero::isClear() const {
    return mClear;
}

const BackPack& Hero::backPack() const {
    return mBackPack;
}

