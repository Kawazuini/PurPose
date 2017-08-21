/**
 * @file   Hero.cpp
 * @brief  Hero
 * @author Maeda Takumi
 */
#include "Hero.h"

#include "GameState.h"
#include "Item.h"
#include "Special.h"

const int Hero::MAX_WEIGHT(50.0f);

Hero::Hero(const KCamera& aCamera) :
Character(ID_INDEX_HERO),
mTurnCount(0),
mBackPack(aCamera),
mMuscle(MAX_WEIGHT),
mWeightArerm(false),
mPunchAngle(20.0f / 180 * Math::PI),
mHold(false) {
    mSize = mCharacterParameter.mSize;
    reset();
}

void Hero::draw() const {
    Character::draw();
    if (mHold) {
        KShading::ColorShading->ON();
        glColor(0x99ffffff);

        glBegin(GL_LINES);
        glVertex(mPosition + KVector(0, -0.001, 0));
        glVertex(mPosition + mDirection * 1000);
        glEnd();
        KShading::PhongShading->ON();
    }
}

void Hero::update(GameState& aState) {
    Character::update(aState);
    bool weightOver(mBackPack.weight() > mMuscle);
    if (!mWeightArerm && weightOver) {
        aState.mBulletin.write(Message("アイテムが重すぎる!!", 0xffff0000));
        aState.mBulletin.write(Message("1ターンごとにダメージをうけてしまう!!", 0xffff0000));
        mWeightArerm = true;
    }
    if (mWeightArerm && !weightOver) {
        mWeightArerm = false;
    }
}

void Hero::turnStart() {
    Character::turnStart();

    ++mTurnCount;
    if (mBackPack.weight() > mMuscle) { // 重量オーバーでダメージ
        Special::add(Special(SPECIAL_DAMAGE_IGNORE, 1, this, this));
    }
    if (!(mTurnCount % 10) && mCharacterParameter.mStamina) { // スタミナがあるときはHPが自然回復
        Special::add(Special(SPECIAL_HEAL, 1, this, this));
    }
    if (mTurnCount >= 50) { // 一定ターンでスタミナ減少
        mTurnCount = 0;
        Special::add(Special(SPECIAL_DAMAGE_STAMINA, 1, this, this));
    }
}

void Hero::reset() {
    mCharacterParameter = CharacterParameter(ID_INDEX_HERO);
    mCharacterParameter.mName = PlayerName;

    for (int i = 0; i < 3; ++i) mWeapon[i] = nullptr;
    mShield = nullptr;
    mHeadEquipment = nullptr;
    mBodyEquipment = nullptr;
    mFootEquipment = nullptr;

    mBackPack.clear();

    mClear = false;
}

void Hero::newFloor(GameState& aState) {
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
    if (mTurn) {
        Character::attack(aState);
        if (!mWeapon[mWeaponIndex]) punch(aState);
        turnEnd();
    }
}

void Hero::punch(GameState& aState) {
    bool hit(false);
    KSphere reach(mPosition, mSize + mCharacterParameter.mAttackRange);

    for (Character* i : aState.charList()) {
        if (i != this) { // 自分は殴らない。
            if (reach * KSphere(i->position(), i->size())) {
                if ((i->position() - mPosition).angle(mDirection) < mPunchAngle) {
                    Special::add(Special(SPECIAL_DAMAGE, mCharacterParameter.mSTR, this, i));
                    hit = true;
                }
            }
        }
    }
    if (!hit) aState.mBulletin.write(mCharacterParameter.mName + "は空振りしてしまった。");
}

void Hero::reload(GameState& aState) {
    if (!mWeapon[mWeaponIndex]) {
        aState.mBulletin.write("なにも装備されていない!");
        return;
    }
    ItemType type(mWeapon[mWeaponIndex]->param().mItemType);
    if (type != WEAPON_GUN && type != WEAPON_BOW) {
        aState.mBulletin.write("装填の必要がない武器だ!");
    } else {
        bool reload(false);
        int reloadCount(mWeapon[mWeaponIndex]->param().mStack - mWeapon[mWeaponIndex]->mMagazine.size());
        for (int i = 0; i < reloadCount; ++i) {
            Item * bullet(mBackPack.takeOut(1, mWeapon[mWeaponIndex]->param().mMagazineID));
            if (bullet) {
                mWeapon[mWeaponIndex]->mMagazine.push_back(bullet);
                reload = true;

                mWaitTurn = mWeapon[mWeaponIndex]->param().mCost; // 装填には銃のコストを使用
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

void Hero::weaponFumble(const int& aAmount) {
    mWeaponIndex += aAmount;
    if (mWeaponIndex < 0) mWeaponIndex = 2;
    if (2 < mWeaponIndex) mWeaponIndex = 0;
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

void Hero::putItem(GameState& aState, const int& aCount) {
    Item * item(mBackPack.lookAt());
    if (item) {
        putting(aState, *(mBackPack.takeOut(aCount)));
    }
}

void Hero::sortItem() {
    mBackPack.sort();
}

const Character* Hero::whoIamSeeing(const GameState& aState) const {
    // 視線線分
    KSegment eye(mPosition, mPosition + mDirection * mCharacterParameter.mPER * 10);

    Vector<HitCharacter> checkList;
    const List<Character*>& characters(aState.charList());
    const List<KPolygon*>& walls(aState.wallList());
    for (Character* i : characters) {
        // 視線の先に自分以外のキャラクターがいる
        if (i != this && KSphere(i->position(), i->size()) * eye) {
            KSegment seg(mPosition, i->position());
            bool sepWall(false); // 壁で隔てられている
            for (KPolygon* j : walls) {
                if (j->operator*(seg)) {
                    sepWall = true;
                    break;
                }
            }
            if (!sepWall) checkList.push_back(HitCharacter{i, (i->position() - eye.mVec1).lengthSquared()});
        }
    }

    if (!checkList.empty()) {
        // 近い順に並べる
        std::sort(checkList.begin(), checkList.end(),
                [](const HitCharacter& x, const HitCharacter & y) -> bool {
                    return x.mDistance < y.mDistance;
                }
        );
        return checkList[0].mCharacter;
    }
    return nullptr;
}

const bool& Hero::isClear() const {
    return mClear;
}

const BackPack& Hero::backPack() const {
    return mBackPack;
}

