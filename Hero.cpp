/**
 * @file   Hero.cpp
 * @brief  Hero
 * @author Maeda Takumi
 */
#include "Hero.h"

#include "GameState.h"
#include "Item.h"
#include "Special.h"

const int Hero::TEX_SIZE(512);

Hero::Hero() :
Character(ID_HERO),
mAiming(TEX_SIZE),
mHold(false) {
    mBody.mRadius = 1.5;

    mPunchAngle = 20.0f / 180 * Math::PI;

    // 照準テクスチャの設定
    mAiming.drawRect(KRect(TEX_SIZE, TEX_SIZE), 0x77003333);
    mAiming.drawLine(KVector(0, 0), KVector(TEX_SIZE, TEX_SIZE), 0x77ff0000);
    mAiming.drawLine(KVector(TEX_SIZE, 0), KVector(0, TEX_SIZE), 0x77ff0000);
    mAiming.reflect();

    reset();

    KDrawer::remove();
}

void Hero::draw() const {
    if (mHold) {
        float reach(mCharacterParameter.mAttackRange);
        float angle(mPunchAngle);
        KVector direction(mDirection.normalization() * reach);
        if (!mWeapon) {

        }

        KVector cross(mDirection.rotate(KQuaternion(KVector(0, 1, 0), 1)));
        KVector radius(mDirection.cross(cross).normalization() * reach * sin(angle));

        glDisable(GL_LIGHTING);
        mAiming.bindON();
        glBegin(GL_POLYGON);

        KVector vert(mPosition + direction + radius.rotate(KQuaternion(mDirection, Math::PI / 4 * 0)));
        glTexCoord2f(0, 0);
        glVertex3f(DEPLOYMENT(vert));
        vert = KVector(mPosition + direction + radius.rotate(KQuaternion(mDirection, Math::PI / 4 * 1)));
        glTexCoord2f(0, 0.5);
        glVertex3f(DEPLOYMENT(vert));
        vert = KVector(mPosition + direction + radius.rotate(KQuaternion(mDirection, Math::PI / 4 * 2)));
        glTexCoord2f(0, 1);
        glVertex3f(DEPLOYMENT(vert));
        vert = KVector(mPosition + direction + radius.rotate(KQuaternion(mDirection, Math::PI / 4 * 3)));
        glTexCoord2f(0.5, 1);
        glVertex3f(DEPLOYMENT(vert));
        vert = KVector(mPosition + direction + radius.rotate(KQuaternion(mDirection, Math::PI / 4 * 4)));
        glTexCoord2f(1, 1);
        glVertex3f(DEPLOYMENT(vert));
        vert = KVector(mPosition + direction + radius.rotate(KQuaternion(mDirection, Math::PI / 4 * 5)));
        glTexCoord2f(1, 0.5);
        glVertex3f(DEPLOYMENT(vert));
        vert = KVector(mPosition + direction + radius.rotate(KQuaternion(mDirection, Math::PI / 4 * 6)));
        glTexCoord2f(1, 0);
        glVertex3f(DEPLOYMENT(vert));
        vert = KVector(mPosition + direction + radius.rotate(KQuaternion(mDirection, Math::PI / 4 * 7)));
        glTexCoord2f(0.5, 0);
        glVertex3f(DEPLOYMENT(vert));

        glEnd();
        mAiming.bindOFF();
        glEnable(GL_LIGHTING);
    }
}

void Hero::update(GameState& aState) {
    light.mPosition = mEyeCamera.mPosition;
    light.mDirection = mEyeCamera.mDirection;
    light.at();

    mPrePosition = mPosition;

    mHold = false;
}

void Hero::reset() {
    mCharacterParameter = CharacterParameter(ID_HERO);

    mClear = false;

    mBackPack.add(new Item(801));
    mBackPack.add(new Item(802));
    mBackPack.add(new Item(803));
    mBackPack.add(new Item(804));
    mBackPack.add(new Item(805));
}

void Hero::newFloar(GameState& aState) {
    mClear = false;
    setPosition(aState, aState.respawn());
}

void Hero::move(GameState& aState, const KVector& aDirection) {
    Character::move(aState, mEyeCamera.convertDirection(aDirection) + position());

    // アイテムを拾う
    Item* tmp = checkItem(aState);
    if (tmp) {
        if (tmp->pickable()) {
            pickUp(aState, tmp);
            aState.removeItem(*tmp);
            tmp->hide();
        }
    }
}

void Hero::syncPosition() {
    mEyeCamera.mPosition = mPosition;
    mEyeCamera.set();
}

void Hero::holdWeapon() {
    mHold = true;
}

void Hero::attack(GameState& aState) {
    if (mTurn) {
        aState.mBulletin.write(mCharacterParameter.mName + "のこうげき!");
        if (!mWeapon) punch(aState);
        else weaponAttack(aState);
        turnEnd();
    }
}

void Hero::punch(GameState& aState) {
    bool hit(false);
    KSphere reach(mPosition, mBody.mRadius + mCharacterParameter.mAttackRange);

    for (Character* i : aState.charList()) {
        if (i != this) { // 自分は殴らない。
            if (reach * i->body()) {
                if ((i->position() - mPosition).angle(mDirection) < mPunchAngle) {
                    Special::add(Special(DAMAGE, mCharacterParameter.mSTR, this, i));
                    hit = true;
                }
            }
        }
    }
    if (!hit) aState.mBulletin.write(mCharacterParameter.mName + "はからぶりしてしまった。");
}

void Hero::weaponAttack(GameState& aState) {
    bool hit(false);
    KSphere reach(
            mPosition,
            mBody.mRadius
            + mCharacterParameter.mAttackRange
            + mWeapon->mItemParameter.mEffectiveRange
            );

    for (Character* i : aState.charList()) {
        if (i != this) { // 自分は殴らない。
            if (reach * i->body()) {
                if ((i->position() - mPosition).angle(mDirection) < mWeapon->mItemParameter.mEffectiveAngle / 180 * Math::PI) {
                    Special::add(Special(DAMAGE, mCharacterParameter.mSTR + mWeapon->mItemParameter.mAttackPower, this, i));
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
        if (item->mItemParameter.mUsable) item = mBackPack.takeOut();
        use(aState, *item);
    }
}

void Hero::equipItem(GameState& aState) {
    Item* item = mBackPack.lookAt();
    if (item) equip(aState, *item);
}

void Hero::takeoffItem(GameState& aState) {
    Item* item = mBackPack.lookAt();
    if (item) takeOff(aState, *item);
}

void Hero::throwItem(GameState& aState) {
    Item* item = mBackPack.lookAt();
    if (item) {
        if (item->mItemParameter.mThrowable) item = mBackPack.takeOut();
        throwing(aState, *item);
    }
}

const bool& Hero::isClear() const {
    return mClear;
}

const BackPack& Hero::backPack() const {
    return mBackPack;
}

