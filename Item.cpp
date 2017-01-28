/**
 * @file   Item.cpp
 * @brief  Item
 * @author Maeda Takumi
 */
#include "Item.h"

#include "Special.h"
#include "GameState.h"

const float Item::ITEM_SCALE = 1.0f;

Item::Item(const int& aID) :
Item(aID, KVector()) {
    mEntity.Object::remove();
    hide();
}

Item::Item(const int& aID, const KVector& aPosition) :
mEntity(ITEM_SCALE, aPosition),
mOwener(NULL),
mItemParameter(aID) {
}

void Item::update(GameState& aState) {
    if (mEntity.isMove()) {
        const Vector<Character*>& hitChar(mEntity.hitCharacter());
        if (mOwener && !hitChar.empty()) {
            Special::add(Special(mItemParameter.mSpecial, mOwener, (hitChar[0])));
            aState.removeItem(*this);
            delete this;
        }
    } else {
        mOwener = NULL;
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
    mEntity.setPosition(aChar.position() + aChar.direction() * (aChar.size() + mEntity.radius() + 0.1f));
    mEntity.applyForce(aChar.direction() * aChar.mCharacterParameter.throwPower());
    mOwener = &aChar;
}

const bool Item::pickable() const {
    return mItemParameter.mPickable && !mEntity.isMove();
}

const KVector & Item::position() const {
    return mEntity.position();
}

