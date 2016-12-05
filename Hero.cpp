/**
 * @file   Hero.cpp
 * @brief  Hero
 * @author Maeda Takumi
 */
#include "Hero.h"

#include "Device.h"
#include "Map.h"

#include "HPotion.h"
#include "TelePotion.h"

Hero::Hero() {
    KDrawer::erase(); // 独自描画

    mName = "aaa";

    mSize = 1;
    mEyeCamera = new KFPSCamera();
    mDevice = new Device(*mEyeCamera, *this);

    mHP = mMaxHP = 10;

    mActionPoint = 0;

    mAgility = 12;

    mMoveCost = 1;
    mAttackCost = 5;

    setPosition(mPosition);

    mDead = false;

    mPunchReach = 5;
    mPunchAngle = 30.0f / 180 * Math::PI;

    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new TelePotion());
    mBackPack.add(new TelePotion());
}

Hero::~Hero() {
}

void Hero::draw() const {
    mDevice->draw();
}

void Hero::update() {
    Character::update();

    light.mPosition = mEyeCamera->mPosition;
    light.mDirection = mEyeCamera->mDirection;
    light.at();
}

void Hero::move(const KVector& aMovement) {
    if (isMovable()) {
        mPosition += mEyeCamera->convertDirection(aMovement).normalization();
        resolveOverlap();
        mEyeCamera->mPosition = mPosition;
        mEyeCamera->set();
    }
}

void Hero::attack() {
    if (isAttackable()) {
        Device::sBulletin.write(mName + "のこうげき!");
        punch();
    }
}

void Hero::punch() {
    bool hit = false;
    KSphere reach(mPosition, mSize + mPunchReach);

    List<Character*> list = Character::sCharacters;
    for (Character* i : list) {
        if (i != this) { // 自分は殴らない。
            KSphere enemy(i->position(), i->size());
            if (reach * enemy) {
                if ((i->position() - mPosition).angle(mDirection) < mPunchAngle) {
                    Device::sBulletin.write(mName + "は" + i->name() + "をなぐりつけた!");
                    i->damage(10);
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
    mEyeCamera->rotate(aAngleV, aAngleH);
    mDirection = mEyeCamera->mDirection;
}

void Hero::fumble(const int& aAmount) {
    mBackPack.selectChange(aAmount);
}

void Hero::useItem() {
    Item* usingItem = mBackPack.takeOut();
    if (usingItem) Character::use(*usingItem);
}

void Hero::setPosition(const KVector& aPosition) {
    Character::setPosition(aPosition);

    mEyeCamera->mPosition = mPosition;
}

bool Hero::dead() const {
    return mDead;
}

