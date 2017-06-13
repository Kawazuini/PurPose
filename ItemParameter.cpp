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
mValue(toInt(mParameterTable[ITEM_INDEX_VALUE])),
mBrief(split(mParameterTable[ITEM_INDEX_BRIEF], "/")),
mSize(toFloat(mParameterTable[ITEM_INDEX_SIZE])),
mWeight(toFloat(mParameterTable[ITEM_INDEX_WEIGHT])),
mUsable(toInt(mParameterTable[ITEM_INDEX_USABLE])),
mEquippable(toInt(mParameterTable[ITEM_INDEX_EQUIPPABLE])),
mReflectable(toInt(mParameterTable[ITEM_INDEX_REFLECT])),
mSpecials(Special::Specials(split(loadString(ID_INDEX_SPECIAL + toInt(mParameterTable[ITEM_INDEX_SPECIALS])), ","))),
mCost(toInt(mParameterTable[ITEM_INDEX_COST])),
mPower(toInt(mParameterTable[ITEM_INDEX_POWER])),
mEffectiveRange(toFloat(mParameterTable[ITEM_INDEX_ERANGE])),
mEffectiveAngle(toFloat(mParameterTable[ITEM_INDEX_EANGLE])),
mBurst(toInt(mParameterTable[ITEM_INDEX_BURST])),
mStack(toInt(mParameterTable[ITEM_INDEX_STACK])),
mMagazineID(ID_INDEX_ITEM + toInt(mParameterTable[ITEM_INDEX_MAGAZINE_ID])) {
}

