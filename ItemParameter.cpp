/**
 * @file   ItemParameter.cpp
 * @brief  ItemParameter
 * @author Maeda Takumi
 */
#include "ItemParameter.h"

ItemParameter::ItemParameter(const int& aID) :
mParameterTable(split(loadString(aID), _T(","))),
mID(aID),
mItemType(toItemType(mParameterTable[ITEM_INDEX_TYPE])),
mName(mParameterTable[ITEM_INDEX_NAME]),
mSize(toFloat(mParameterTable[ITEM_INDEX_SIZE])),
mWeight(toFloat(mParameterTable[ITEM_INDEX_WEIGHT])),
mUsable(toInt(mParameterTable[ITEM_INDEX_USABLE])),
mEquippable(toInt(mParameterTable[ITEM_INDEX_EQUIPPABLE])),
mReflectable(toInt(mParameterTable[ITEM_INDEX_REFLECT])),
mSpecial(
toSpecialType(mParameterTable[ITEM_INDEX_SPECIAL]),
toFloat(mParameterTable[ITEM_INDEX_SPPOINT])
),
mCost(toInt(mParameterTable[ITEM_INDEX_COST])),
mAttackPower(toFloat(mParameterTable[ITEM_INDEX_ATTACK])),
mDefencePower(toFloat(mParameterTable[ITEM_INDEX_DEFENSE])),
mEffectiveRange(toFloat(mParameterTable[ITEM_INDEX_ERANGE])),
mEffectiveAngle(toFloat(mParameterTable[ITEM_INDEX_EANGLE])),
mPickable(true),
mEquipped(false),
mTakeoffable(true),
mStack(toInt(mParameterTable[ITEM_INDEX_STACK])),
mMagazineID(toInt(mParameterTable[ITEM_INDEX_MAGAZINE_ID])) {
}

const int& ItemParameter::id() const {
    return mID;
}

const ItemType& ItemParameter::type() const {
    return mItemType;
}

const String& ItemParameter::name() const {
    return mName;
}

const float& ItemParameter::size() const {
    return mSize;
}

const float& ItemParameter::weight() const {
    return mWeight;
}

const bool& ItemParameter::usable() const {
    return mUsable;
}

const bool& ItemParameter::equippable() const {
    return mEquippable;
}

const bool& ItemParameter::reflec() const {
    return mReflectable;
}

const Special& ItemParameter::special() const {
    return mSpecial;
}

const int& ItemParameter::cost() const {
    return mCost;
}

const float& ItemParameter::attackPower() const {
    return mAttackPower;
}

const float& ItemParameter::defencePower() const {
    return mDefencePower;
}

const float& ItemParameter::effectRange() const {
    return mEffectiveRange;
}

const float& ItemParameter::effectAngle() const {
    return mEffectiveAngle;
}

const int& ItemParameter::stack() {
    return mStack;
}

const int& ItemParameter::magazineID() {
    return mMagazineID;
}

