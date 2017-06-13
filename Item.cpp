/**
 * @file   Item.cpp
 * @brief  Item
 * @author Maeda Takumi
 */
#include "Item.h"

#include "GameState.h"

const float Item::PICKABLE_RANGE(1.0f);
const int Item::TEX_SIZE(16);

Item::Item(const int& aID) :
Item(aID, KVector()) {
    hide();
}

Item::Item(const int& aID, const KVector& aPosition) :
mItemParameter(aID),
mTexture(TEX_SIZE, false),
mOffset(0, PICKABLE_RANGE / 2.0f + mItemParameter.mSize),
mHaribote(aPosition, PICKABLE_RANGE, mTexture),
mEntity(mItemParameter.mSize, mItemParameter.mWeight, aPosition),
mOwener(NULL),
mPickable(true),
mEquipped(false),
mTakeoffable(true) {
    mEntity.mReflect = mItemParameter.mReflectable;
    mEntity.Object::remove();

    // 描画領域の確定・描画
    KVector src(KVector(mItemParameter.mItemType % 4, mItemParameter.mItemType / 4) * TEX_SIZE);
    mTexture.drawImage(IMG_ITEM, KRect(src, src + KVector(TEX_SIZE, TEX_SIZE)), KVector());
    mTexture.reflect();
}

Item::~Item() {
    // マガジンを空にする
    while (!mMagazine.empty()) {
        delete mMagazine.back();
        mMagazine.pop_back();
    }
}

void Item::update(GameState& aState) {
    static const KVector AXIS(0, 1, 0);

    // ハリボテの位置調整
    if (mPickable) mHaribote.translate(mEntity.position() + mOffset);

    if (mEntity.isMove()) {
        aState.mPhysical = true;
        const Vector<Character*>& hitChar(mEntity.hitCharacter());
        if (mOwener && !hitChar.empty()) {
            for (Character* i : hitChar) {
                if (i != mOwener) {
                    if (mItemParameter.mSpecials.front().type() == SPECIAL_DAMAGE) { // 力積でダメージボーナス
                        Special::add(Special(SPECIAL_DAMAGE, mItemParameter.mSpecials.front().value() * mEntity.impulse(), mOwener, i));
                    } else special(mOwener, i);
                    aState.removeItem(*this);
                    delete this;
                    return;
                }
            }
        }
    } else mOwener = NULL;

    if (!mItemParameter.mReflectable && mEntity.isHitWall()) {
        if (mItemParameter.mSpecials.front().type() == SPECIAL_EXPLOSION) { // 爆発!!
            Special::add(Special(mItemParameter.mSpecials.front(), mOwener, this));
            Special::invocation(aState);
        }
        aState.removeItem(*this);
        delete this;
    }
}

void Item::special(Character* aSCharacter, Character* aOCharacter) {
    for (Special i : mItemParameter.mSpecials) {
        Special::add(Special(i, aSCharacter, aOCharacter));
    }
}

void Item::embody() {
    mEntity.KDrawer::add();
    mHaribote.add();
    mPickable = true;
}

void Item::hide() {
    mEntity.KDrawer::remove();
    mHaribote.remove();
    mPickable = false;
}

const bool Item::pickable() const {
    return mPickable && !mEntity.isMove();
}

const ItemParameter& Item::param() const {
    return mItemParameter;
}

