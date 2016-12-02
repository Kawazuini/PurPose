/**
 * @file   Hero.cpp
 * @brief  Hero
 * @author Maeda Takumi
 */
#include "Hero.h"

#include "PurPose.h"

#include "Map.h"

#include "HPotion.h"
#include "TelePotion.h"

Hero::Hero() {
    KDrawer::erase(); // 独自描画

    mName = "aaa";

    mSize = 1;
    mEyeCamera = new KFPSCamera();
    mDevice = new Device(*mEyeCamera, *this);

    mActionPoint = 0;

    mAgility = 12;

    mMoveCost = 1;
    mAttackCost = 5;

    setPosition(mPosition);

    mPunchReach = 1;

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

void Hero::drawHP() {
}

void Hero::drawActionPoint() {
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
    Character* target = NULL;
    List<Character*> list = Character::sCharacters;
    for (Character* i : list) {
        if ((i->position() - mPosition).length() < mPunchReach + mSize + i->size()) {
            if (i != this) target = i;
        }
    }
    if (target) {
        Device::sBulletin.write(mName + "は" + target->name() + "をなぐりつけた!");
        target->damage(10);
    } else Device::sBulletin.write(mName + "はからぶりしてしまった.");
}

void Hero::swivel(const float& aAngleV, const float& aAngleH) {
    mEyeCamera->rotate(aAngleV, aAngleH);
}

void Hero::fumble(const int& aMoment) {
    mBackPack.selectChange(aMoment);
}

void Hero::setPosition(const KVector& aPosition) {
    Character::setPosition(aPosition);

    mEyeCamera->mPosition = mPosition;
}

