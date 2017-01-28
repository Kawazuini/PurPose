/**
 * @file   ItemParameter.cpp
 * @brief  ItemParameter
 * @author Maeda Takumi
 */
#include "ItemParameter.h"

const int ItemParameter::ITEM_INDEX_TYPE(0);
const int ItemParameter::ITEM_INDEX_NAME(1);
const int ItemParameter::ITEM_INDEX_USABLE(2);
const int ItemParameter::ITEM_INDEX_EQUIPPABLE(3);
const int ItemParameter::ITEM_INDEX_THROWABLE(4);
const int ItemParameter::ITEM_INDEX_PICKABLE(5);
const int ItemParameter::ITEM_INDEX_WEIGHT(6);
const int ItemParameter::ITEM_INDEX_SPECIAL(7);
const int ItemParameter::ITEM_INDEX_SPPOINT(8);
const int ItemParameter::ITEM_INDEX_ATTACK(9);
const int ItemParameter::ITEM_INDEX_DEFENSE(10);
const int ItemParameter::ITEM_INDEX_ERANGE(11);
const int ItemParameter::ITEM_INDEX_EANGLE(12);

ItemParameter::ItemParameter(const int& aID) :
mParameterTable(split(loadString(aID), _T(","))),
mID(aID),
mName(mParameterTable[ITEM_INDEX_NAME]),
mItemType(toItemType(mParameterTable[ITEM_INDEX_TYPE])),
mUsable(toInt(mParameterTable[ITEM_INDEX_USABLE])),
mEquippable(toInt(mParameterTable[ITEM_INDEX_EQUIPPABLE])),
mEquipped(false),
mTakeoffable(true),
mThrowable(toInt(mParameterTable[ITEM_INDEX_THROWABLE])),
mPickable(toInt(mParameterTable[ITEM_INDEX_PICKABLE])),
mWeight(toFloat(mParameterTable[ITEM_INDEX_WEIGHT])),
mSpecial(
toSpecialType(mParameterTable[ITEM_INDEX_SPECIAL]),
toFloat(mParameterTable[ITEM_INDEX_SPPOINT])
),
mAttackPower(toFloat(mParameterTable[ITEM_INDEX_ATTACK])),
mDefencePower(toFloat(mParameterTable[ITEM_INDEX_DEFENSE])),
mEffectiveRange(toFloat(mParameterTable[ITEM_INDEX_ERANGE])),
mEffectiveAngle(toFloat(mParameterTable[ITEM_INDEX_EANGLE])) {
}

