/**
 * @file   Hero.cpp
 * @brief  Hero
 * @author Maeda Takumi
 */
#include "Hero.h"

#include "Device.h"
#include "Stage.h"

#include "HPotion.h"
#include "TelePotion.h"
#include "Sword.h"

Hero::Hero() {
    KDrawer::erase(); // 独自描画

    mName = "aaa";

    mBody.mRadius = 1;
    mDevice = new Device(mEyeCamera, *this);

    mLevel = 1;
    mRequireExperience = 1;

    mHP = mMaxHP = 10;

    mPunchReach = 5;
    mPunchAngle = 30.0f / 180 * Math::PI;

    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new TelePotion());
    mBackPack.add(new TelePotion());
    mBackPack.add(new Sword());
    
    resolveOverlap();
    setPosition(mBody.mPosition);
}

Hero::~Hero() {
    delete mDevice;
}

void Hero::draw() const {
    mDevice->draw();
}

void Hero::update() {
    light.mPosition = mEyeCamera.mPosition;
    light.mDirection = mEyeCamera.mDirection;
    light.at();
}

void Hero::move(const KVector& aMovement) {
    if (mTurn) {
        mBody.mPosition += mEyeCamera.convertDirection(aMovement).normalization();
        resolveOverlap();
        mEyeCamera.mPosition = mBody.mPosition;
        mEyeCamera.set();
        turnEnd();
    }
}

void Hero::attack() {
    if (mTurn) {
        Device::sBulletin.write(mName + "のこうげき!");
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
                    Device::sBulletin.write(mName + "は" + i->name() + "をなぐりつけた!");
                    i->damage(*this, 10);
                    hit = true;
                }
            }
        }
    }
    if (!hit) Device::sBulletin.write(mName + "はからぶりしてしまった。");
}

void Hero::die() {
    Device::sBulletin.write(mName + "はちからつきた。");
    mDead = true;
}

void Hero::swivel(const float& aAngleV, const float& aAngleH) {
    mEyeCamera.rotate(aAngleV, aAngleH);
    mDirection = mEyeCamera.mDirection;
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

void Hero::setPosition(const KVector& aPosition) {
    Character::setPosition(aPosition);
    mEyeCamera.mPosition = mBody.mPosition;
    mEyeCamera.set();
}

