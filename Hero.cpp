/**
 * @file   Hero.cpp
 * @brief  Hero
 * @author Maeda Takumi
 */
#include "Hero.h"

#include "GameState.h"
#include "Item.h"
#include "Special.h"

Hero::Hero() :
Character(ID_HERO),
mHold(false) {
    mBody.mRadius = 1.5;

    mPunchAngle = 20.0f / 180 * Math::PI;

    reset();

    KDrawer::remove();
}

void Hero::draw() const {
    if (mHold) {
        glDisable(GL_LIGHTING);
        glBegin(GL_LINES);
        glColor4f(1, 0, 0, 0.5);

        glVertex3f(DEPLOYMENT(mPosition + KVector(0, -0.001, 0)));
        glVertex3f(DEPLOYMENT(mPosition + mDirection * 1000));

        glColor4f(1, 1, 1, 1);
        glEnd();
        glEnable(GL_LIGHTING);
    }
}

void Hero::reset() {
    mCharacterParameter = CharacterParameter(ID_HERO);

    mClear = false;

    mBackPack.add(new Item(801));
    mBackPack.add(new Item(802));
    mBackPack.add(new Item(803));
    mBackPack.add(new Item(804));
    mBackPack.add(new Item(805));
    mBackPack.add(new Item(806));
    mBackPack.add(new Item(807));
    mBackPack.add(new Item(808));
    mBackPack.add(new Item(809));
}

void Hero::newFloar(GameState& aState) {
    mClear = false;
    setPosition(aState, aState.respawn());
}

void Hero::move(GameState& aState, const KVector& aDirection) {
    Character::move(aState, aDirection + position());

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

void Hero::arm() {
    if (!mHold) mHold = true;
}

void Hero::disarm() {
    if (mHold) mHold = false;
}

void Hero::attack(GameState& aState) {
    Character::attack(aState);
    if (mTurn) {
        aState.mBulletin.write(mCharacterParameter.mName + "の攻撃!");
        if (mWeapon) weaponAttack(aState);
        else punch(aState);
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
    if (!hit) aState.mBulletin.write(mCharacterParameter.mName + "は空振りしてしまった。");
}

void Hero::weaponAttack(GameState& aState) {
    bool hit(false);
    switch (mWeapon->mItemParameter.type()) {
        case EQUIPMENT_SWORD:
        {
            KSphere reach(mPosition, mBody.mRadius + mCharacterParameter.mAttackRange + mWeapon->mItemParameter.effectRange());
            for (Character* i : aState.charList()) {
                if (i != this) { // 自分は殴らない。
                    if (reach * i->body()) {
                        if ((i->position() - mPosition).angle(mDirection) < mWeapon->mItemParameter.effectAngle() / 180 * Math::PI) {
                            Special::add(Special(DAMAGE, mCharacterParameter.mSTR + mWeapon->mItemParameter.attackPower(), this, i));
                            hit = true;
                        }
                    }
                }
            }
            if (!hit) aState.mBulletin.write(mCharacterParameter.mName + "は空振りしてしまった。");
            break;
        }
        case EQUIPMENT_GUN:
        case EQUIPMENT_BOW:
            mWeapon->trigger(aState, *this);
            break;
    }
}

void Hero::reload(GameState& aState) {
    if (!mWeapon) {
        aState.mBulletin.write("なにも装備されていない!");
        return;
    }
    ItemType type(mWeapon->mItemParameter.type());
    if (type != EQUIPMENT_GUN && type != EQUIPMENT_BOW) {
        aState.mBulletin.write("装填の必要がない武器だ!");
    } else {
        bool reload(false);
        int reloadCount(mWeapon->mItemParameter.stack() - mWeapon->loadNumber());
        for (int i = 0; i < reloadCount; ++i) {
            Item * bullet(mBackPack.lookFor(mWeapon->mItemParameter.magazineID()));
            if (bullet) {
                mWeapon->reload(*bullet);
                reload = true;
            } else break;
        }
        if (!reloadCount) aState.mBulletin.write("既に最大まで装填済み!");
        else if (!reload) aState.mBulletin.write("装填するアイテムがもうない!");
        else turnEnd();
    }
}

void Hero::pickUp(GameState& aState, Item * const aItem) {
    mBackPack.add(aItem);
    aState.mBulletin.write(aItem->mItemParameter.name() + "を拾った。");
}

void Hero::fumble(const int& aAmount) {
    mBackPack.selectChange(aAmount);
}

void Hero::useItem(GameState& aState) {
    Item * item(mBackPack.lookAt());
    if (item) {
        use(aState, *(mBackPack.takeOut()));
    }
}

void Hero::equipItem(GameState& aState) {
    Item * item(mBackPack.lookAt());
    if (item) equip(aState, *item);
}

void Hero::takeoffItem(GameState& aState) {
    Item * item(mBackPack.lookAt());
    if (item) takeOff(aState, *item);
}

void Hero::throwItem(GameState& aState) {
    Item * item(mBackPack.lookAt());
    if (item) {
        throwing(aState, *(mBackPack.takeOut()));
    }
}

void Hero::putItem(GameState& aState) {
    Item * item(mBackPack.lookAt());
    if (item) {
        putting(aState, *(mBackPack.takeOut()));
    }
}

const bool& Hero::isClear() const {
    return mClear;
}

const BackPack& Hero::backPack() const {
    return mBackPack;
}

