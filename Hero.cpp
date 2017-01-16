/**
 * @file   Hero.cpp
 * @brief  Hero
 * @author Maeda Takumi
 */
#include "Hero.h"

#include "Bulletin.h"
#include "HPotion.h"
#include "Special.h"
#include "Stage.h"
#include "Sword.h"
#include "TelePotion.h"

Hero::Hero() {
    KDrawer::remove(); // 独自描画

    mParameter.mName = "ぼく";

    mParameter.mSpeed = 1.0f;

    mBody.mRadius = 1.5;

    mParameter.mLevel = 1;
    mParameter.mRequireExperience = 1;

    mParameter.mHP = mParameter.mMaxHP = 10;

    mParameter.mStrength = 100;

    mPunchReach = 5;
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

Hero::~Hero() {
}

void Hero::draw() const {
}

void Hero::update(const GameState& aState) {
    light.mPosition = mEyeCamera.mPosition;
    light.mDirection = mEyeCamera.mDirection;
    light.at();

    mPrePosition = mBody.mPosition;
}

void Hero::newFloar(const GameState& aState) {
    mClear = false;
    setPosition(aState.respawn());
}

void Hero::move(const GameState& aState, const KVector& aDirection) {
    Character::move(aState, mEyeCamera.convertDirection(aDirection) + position());

    // アイテムを拾う
    Item* tmp = checkItem();
    if (tmp) {
        pickUp(aState, tmp);
        tmp->hide();
    }
}

void Hero::syncPosition() {
    mEyeCamera.mPosition = mBody.mPosition;
    mEyeCamera.set();
}

void Hero::attack(const GameState& aState) {
    if (mTurn) {
        aState.mBulletin.write(mParameter.mName + "のこうげき!");
        punch(aState);
        turnEnd();
    }
}

void Hero::punch(const GameState& aState) {
    bool hit = false;
    KSphere reach(mBody.mPosition, mBody.mRadius + mPunchReach);

    List<Character*> list = Character::sCharacters;
    for (Character* i : list) {
        if (i != this) { // 自分は殴らない。
            if (reach * i->body()) {
                if ((i->position() - mBody.mPosition).angle(mDirection) < mPunchAngle) {
                    Special::Damage(this, i, 10);
                    hit = true;
                }
            }
        }
    }
    if (!hit) aState.mBulletin.write(mParameter.mName + "はからぶりしてしまった。");
}

void Hero::die(const GameState& aState) {
    aState.mBulletin.write(mParameter.mName + "はちからつきた。");
    mParameter.mDead = true;
}

void Hero::swivel(const float& aAngleV, const float& aAngleH) {
    mEyeCamera.rotate(aAngleV, aAngleH);
    mDirection = mEyeCamera.mDirection;
}

void Hero::pickUp(const GameState& aState, Item * const aItem) {
    mBackPack.add(aItem);
    aState.mBulletin.write(aItem->name() + "をひろった。");
}

void Hero::fumble(const int& aAmount) {
    mBackPack.selectChange(aAmount);
}

void Hero::useItem(const GameState& aState) {
    Item* item = mBackPack.lookAt();
    if (item) {
        if (item->usable()) item = mBackPack.takeOut();
        use(aState, *item);
    }
}

void Hero::equipItem(const GameState& aState) {
    Item* item = mBackPack.lookAt();
    if (item) equip(aState, *item);
}

void Hero::throwItem(const GameState& aState) {
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

