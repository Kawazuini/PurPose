/**
 * @file   Item.h
 * @brief  Item
 * @author Maeda Takumi
 */
#include "Item.h"

#include "Character.h"
#include "Map.h"
#include "Special.h"
#include "GameState.h"

const float Item::ITEM_SCALE = 1.0f;

Item::Item() :
Item(KVector(MAP_SCALE, 0, MAP_SCALE)) {
    hide();
}

Item::Item(const KVector& aPosition) :
mEntity(ITEM_SCALE, aPosition),
mOwener(NULL) {
    mItemParameter.mUsable = false;
    mItemParameter.mEquippable = false;
    mItemParameter.mThrowable = true;
    mItemParameter.mPickable = true;
    mItemParameter.mWeight = 0.0f;
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

void Item::use(Character & aChar) {
    delete this;
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

