/**
 * @file   Item.cpp
 * @brief  Item
 * @author Maeda Takumi
 */
#include "Item.h"

#include "GameState.h"
#include "Special.h"

const float Item::ITEM_SCALE = 1.0f;

Item::Item(const int& aID) :
Item(aID, KVector()) {
    hide();
}

Item::Item(const int& aID, const KVector& aPosition) :
mItemParameter(aID),
mEntity(mItemParameter.size(), mItemParameter.weight(), aPosition),
mOwener(NULL) {
    mEntity.mReflect = mItemParameter.reflec();
    mEntity.Object::remove();
}

void Item::update(GameState& aState) {
    if (mEntity.isMove()) {
        const Vector<Character*>& hitChar(mEntity.hitCharacter());
        if (mOwener && !hitChar.empty()) {
            for (Character* i : hitChar) {
                if (i != mOwener) {
                    if (mItemParameter.special().type() == DAMAGE) {
                        Special::add(Special(DAMAGE, mItemParameter.special().value() * mEntity.impulse(), mOwener, i));
                    } else Special::add(Special(mItemParameter.special(), mOwener, i));
                    aState.removeItem(*this);
                    delete this;
                    return;
                }
            }
        }
    } else {
        mOwener = NULL;
    }
    if (!mItemParameter.reflec() && mEntity.isHitWall()) {
        aState.removeItem(*this);
        delete this;
    }
}

void Item::embody() {
    mEntity.KDrawer::add();
    mItemParameter.mPickable = true;
}

void Item::hide() {
    mEntity.KDrawer::remove();
    mItemParameter.mPickable = false;
}

void Item::throwing(Character & aChar) {
    embody();
    mEntity.setPosition(aChar.position() + aChar.direction() * (aChar.size() + mEntity.radius()));
    mEntity.applyForce(aChar.direction() * aChar.mCharacterParameter.throwPower());
    mOwener = &aChar;
}

void Item::putting(Character & aChar) {
    embody();
    KVector putPosition(aChar.position() + aChar.direction() * (aChar.size() + mEntity.radius()));
    mEntity.setPosition(KVector(putPosition.x, 0, putPosition.z));
}

void Item::reload(Item& aItem) {
    if (mMagazine.size() < mItemParameter.stack()) {
        if (mItemParameter.magazineID() == aItem.mItemParameter.id()) {
            mMagazine.push_back(&aItem);
        }
    }
}

void Item::trigger(GameState& aState, Character& aChar) {
    if (!mMagazine.empty()) {
        Item * bullet(mMagazine.back());
        mMagazine.pop_back();

        bullet->embody();
        bullet->mEntity.setPosition(aChar.position() + aChar.direction() * (aChar.size() + bullet->mEntity.radius()));

        KVector force(aChar.direction() * (mItemParameter.attackPower() + (mItemParameter.type() == EQUIPMENT_BOW ? aChar.mCharacterParameter.mSTR : 0)));
        bullet->mEntity.applyForce(force);
        bullet->mOwener = &aChar;
    } else aState.mBulletin.write("たまがそうてんされていない!");
}

const bool Item::pickable() const {
    return mItemParameter.mPickable && !mEntity.isMove();
}

const KVector & Item::position() const {
    return mEntity.position();
}

int Item::loadNumber() const {
    return mMagazine.size();
}

