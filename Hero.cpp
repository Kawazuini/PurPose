/**
 * @file   Hero.cpp
 * @brief  Hero
 * @author Maeda Takumi
 */
#include "Hero.h"

#include "Device.h"
#include "HPotion.h"
#include "Special.h"
#include "Stage.h"
#include "Sword.h"
#include "TelePotion.h"

Hero::Hero() {
    KDrawer::remove(); // 独自描画

    mParameter.mName = "ぼく";

    mParameter.mSpeed = 1.0f;

    mBody.mRadius = 0.9;

    mParameter.mLevel = 1;
    mParameter.mRequireExperience = 1;

    mParameter.mHP = mParameter.mMaxHP = 10;

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
}

void Hero::newFloar(const GameState& aState) {
    mClear = false;
    setPosition(aState.respawn());
}

void Hero::move(const KVector& aDirection) {
    Character::move(mEyeCamera.convertDirection(aDirection) + position());

    // アイテムを拾う
    Item* tmp = checkItem();
    if (tmp) {
        pickUp(tmp);
        tmp->pickUp();
    }
}

void Hero::syncPosition() {
    mEyeCamera.mPosition = mBody.mPosition;
    mEyeCamera.set();
}

void Hero::attack() {
    if (mTurn) {
        Device::sBulletin.write(mParameter.mName + "のこうげき!");
        punch();
        turnEnd();
    }
}

void Hero::punch() {
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
    if (!hit) Device::sBulletin.write(mParameter.mName + "はからぶりしてしまった。");
}

void Hero::die() {
    Device::sBulletin.write(mParameter.mName + "はちからつきた。");
    mParameter.mDead = true;
}

void Hero::swivel(const float& aAngleV, const float& aAngleH) {
    mEyeCamera.rotate(aAngleV, aAngleH);
    mDirection = mEyeCamera.mDirection;
}

void Hero::pickUp(Item * const aItem) {
    mBackPack.add(aItem);
    Device::sBulletin.write(aItem->name() + "をひろった。");
}

void Hero::fumble(const int& aAmount) {
    mBackPack.selectChange(aAmount);
}

void Hero::useItem() {
    Item* usingItem = mBackPack.lookAt();
    if (usingItem) {
        if (usingItem->usable()) usingItem = mBackPack.takeOut();
        if (usingItem) use(*usingItem);
    }
}

void Hero::equipItem() {
    Item* equippingItem = mBackPack.lookAt();
    if (equippingItem) equip(*equippingItem);
}

bool Hero::isClear() const {
    return mClear;
}

const BackPack& Hero::backPack() const {
    return mBackPack;
}

