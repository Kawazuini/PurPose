/**
 * @file   Item.cpp
 * @brief  Item
 * @author Maeda Takumi
 */
#include "Item.h"

#include "GameState.h"

const float Item::PICKABLE_RANGE(1.0f);

Item::Item(const int& aID) :
Item(aID, KVector()) {
    hide();
}

Item::Item(const int& aID, const KVector& aPosition) :
mItemParameter(aID),
mEntity(mItemParameter.mSize, mItemParameter.mWeight, aPosition),
mOwener(NULL),
mPickable(true),
mEquipped(false),
mTakeoffable(true) {
    mEntity.mReflect = mItemParameter.mReflectable;
    mEntity.Object::remove();
}

void Item::update(GameState& aState) {
    if (mEntity.isMove()) {
        const Vector<Character*>& hitChar(mEntity.hitCharacter());
        if (mOwener && !hitChar.empty()) {
            for (Character* i : hitChar) {
                if (i != mOwener) {
                    if (mItemParameter.mSpecial.type() == DAMAGE) {
                        Special::add(Special(DAMAGE, mItemParameter.mSpecial.value() * mEntity.impulse(), mOwener, i));
                    } else Special::add(Special(mItemParameter.mSpecial, mOwener, i));
                    aState.removeItem(*this);
                    delete this;
                    return;
                }
            }
        }
    } else {
        mOwener = NULL;
    }
    if (!mItemParameter.mReflectable && mEntity.isHitWall()) {
        aState.removeItem(*this);
        delete this;
    }
}

void Item::embody() {
    mEntity.KDrawer::add();
    mPickable = true;
}

void Item::hide() {
    mEntity.KDrawer::remove();
    mPickable = false;
}

const bool Item::pickable() const {
    return mPickable && !mEntity.isMove();
}

const ItemParameter& Item::param() const {
    return mItemParameter;
}

