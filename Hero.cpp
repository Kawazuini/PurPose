/**
 * @file   Hero.cpp
 * @brief  Hero
 * @author Maeda Takumi
 */
#include "Hero.h"

#include "GameState.h"
#include "Item.h"
#include "Special.h"
#include "Effect.h"

Hero::Hero() :
Character(ID_HERO),
mPunchAngle(20.0f / 180 * Math::PI),
mHold(false),
mMAXStamina(100), mStamina(mMAXStamina) {
    reset();
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

void Hero::turnStart() {
    static int turnCount(0);
    Character::turnStart();

    ++turnCount;
    if (!(turnCount % 10) && mStamina) { // スタミナがあるときはHPが自然回復
        mCharacterParameter.mHP = Math::min(mCharacterParameter.mMHP, mCharacterParameter.mHP + 1);
    }
    if (turnCount >= 50) { // 一定ターンでスタミナ減少
        turnCount = 0;
        mStamina = Math::max(0, mStamina - 1);
    }
}

void Hero::reset() {
    mCharacterParameter = CharacterParameter(ID_HERO);

    mWeapon = NULL;
    mShield = NULL;
    mHeadEquipment = NULL;
    mBodyEquipment = NULL;
    mFootEquipment = NULL;

    mBackPack.clear();
    mBackPack.add(*(new Item(ID_WEAPON_GUN)));
    for (int i = 0, i_e(mBackPack.lookAt()->param().mStack * 2); i < i_e; ++i) mBackPack.add(*(new Item(ID_ITEM_BULLET)));
    for (int i = 0; i < 3; ++i) mBackPack.add(*(new Item(ID_ITEM_POTION + 1)));

    mClear = false;
}

void Hero::newFloor(GameState& aState) {
    mClear = false;
    setPosition(aState, aState.respawn());
}

void Hero::levelUp(GameState& aState, const int& aLevel) {
    int hpup(5 * aLevel), strup(5 * aLevel);
    mCharacterParameter.mLevel += aLevel;
    mCharacterParameter.mMHP += hpup;
    mCharacterParameter.mSTR += strup;

    aState.mBulletin.write(Message(mCharacterParameter.mName + "はレベルが" + toString(mCharacterParameter.mLevel) + "に上がった。", 0xffff0000));
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
                    Special::add(Special(SPECIAL_DAMAGE, mCharacterParameter.mSTR, this, i));
                    hit = true;
                }
            }
        }
    }
    if (!hit) aState.mBulletin.write(mCharacterParameter.mName + "は空振りしてしまった。");
}

void Hero::weaponAttack(GameState& aState) {
    bool hit(false);
    switch (mWeapon->param().mItemType) {
        case WEAPON_SWORD:
        {
            KSphere reach(mPosition, mBody.mRadius + mCharacterParameter.mAttackRange + mWeapon->param().mEffectiveRange);
            for (Character* i : aState.charList()) {
                if (i != this) { // 自分は殴らない。
                    if (reach * i->body()) {
                        if ((i->position() - mPosition).angle(mDirection) < mWeapon->param().mEffectiveAngle / 180 * Math::PI) {
                            Special::add(Special(SPECIAL_DAMAGE, mCharacterParameter.mSTR + mWeapon->param().mPower, this, i));
                            hit = true;
                        }
                    }
                }
            }
            if (!hit) aState.mBulletin.write(mCharacterParameter.mName + "は空振りしてしまった。");
            break;
        }
        case WEAPON_GUN:
        case WEAPON_BOW:
        {
            if (!mWeapon->mMagazine.empty()) {
                Item * bullet(mWeapon->mMagazine.back());
                mWeapon->mMagazine.pop_back();

                bullet->embody();
                bullet->mEntity.setPosition(mPosition + mDirection * (mCharacterParameter.mSize + bullet->mEntity.radius()));

                KVector force(mDirection * (mWeapon->param().mPower + (mWeapon->param().mItemType == WEAPON_BOW ? mCharacterParameter.mSTR : 0)));
                bullet->mEntity.applyForce(force);
                bullet->mOwener = this;

                if (mWeapon->param().mItemType == WEAPON_GUN) new Effect(Effect::EFFECT_GUNSHOT, 2000, mPosition);
            } else aState.mBulletin.write("弾が装填されていない!");
            break;
        }
    }
}

void Hero::reload(GameState& aState) {
    if (!mWeapon) {
        aState.mBulletin.write("なにも装備されていない!");
        return;
    }
    ItemType type(mWeapon->param().mItemType);
    if (type != WEAPON_GUN && type != WEAPON_BOW) {
        aState.mBulletin.write("装填の必要がない武器だ!");
    } else {
        bool reload(false);
        int reloadCount(mWeapon->param().mStack - mWeapon->mMagazine.size());
        for (int i = 0; i < reloadCount; ++i) {
            Item * bullet(mBackPack.takeOut(mWeapon->param().mMagazineID));
            if (bullet) {
                mWeapon->mMagazine.push_back(bullet);
                reload = true;
            } else break;
        }
        if (!reloadCount) aState.mBulletin.write("既に最大まで装填済み!");
        else if (!reload) aState.mBulletin.write("装填するアイテムがもうない!");
        else turnEnd();
    }
}

void Hero::pickUp(GameState& aState, Item * const aItem) {
    int stackCount(aItem->mMagazine.size());
    mBackPack.add(*aItem);
    if (stackCount && aItem->param().mItemType == aItem->mMagazine.back()->param().mItemType) { // 複数格納かつ同一タイプ
        aState.mBulletin.write(aItem->param().mName + "[" + toString(stackCount + 1) + "]" + "を拾った。");
        for (int i = 0; i < stackCount; ++i) {
            mBackPack.add(*(aItem->mMagazine.back()));
            aItem->mMagazine.pop_back();
        }
    } else aState.mBulletin.write(aItem->param().mName + "を拾った。");
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

