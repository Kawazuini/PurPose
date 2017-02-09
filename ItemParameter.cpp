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
mPower(toFloat(mParameterTable[ITEM_INDEX_POWER])),
mEffectiveRange(toFloat(mParameterTable[ITEM_INDEX_ERANGE])),
mEffectiveAngle(toFloat(mParameterTable[ITEM_INDEX_EANGLE])),
mStack(toInt(mParameterTable[ITEM_INDEX_STACK])),
mMagazineID(toInt(mParameterTable[ITEM_INDEX_MAGAZINE_ID])) {
}

