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
#include "Stair.h"

Hero::Hero() {
    KDrawer::remove(); // 独自描画

    mParameter.mName = "ぼく";

    mParameter.mSpeed = 1.0f;

    mBody.mRadius = 0.9;
    mDevice = new Device(*this);

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

void Hero::newFloar() {
    mClear = false;
    setPosition(sStage->respawn());

    resolveOverlap();
    syncPosition();
}

void Hero::move(const KVector& aDirection) {
    static const float SCALE_SQUARE = MAP_SCALE * MAP_SCALE;

    Character::move(mEyeCamera.convertDirection(aDirection));
    // 階段に到達
    if ((sStage->stair().position() - mBody.mPosition).lengthSquared() < SCALE_SQUARE) {
        mClear = true;
    }

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
                    i->damage(*this, 10);
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

void Hero::setPosition(const KVector& aPosition) {
    Character::setPosition(aPosition);
    mEyeCamera.mPosition = mBody.mPosition;
    mEyeCamera.set();
}

bool Hero::isClear() const {
    return mClear;
}

