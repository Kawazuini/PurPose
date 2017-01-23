/**
 * @file   ItemParameter.cpp
 * @brief  ItemParameter
 * @author Maeda Takumi
 */
#include "ItemParameter.h"

const int ItemParameter::ITEM_PARAMETER_INDEX_NAME(0);
const int ItemParameter::ITEM_PARAMETER_INDEX_USABLE(1);
const int ItemParameter::ITEM_PARAMETER_INDEX_EQUIPPABLE(2);
const int ItemParameter::ITEM_PARAMETER_INDEX_THROWABLE(3);
const int ItemParameter::ITEM_PARAMETER_INDEX_PICKABLE(4);
const int ItemParameter::ITEM_PARAMETER_INDEX_WEIGHT(5);
const int ItemParameter::ITEM_PARAMETER_INDEX_SPECIAL(6);
const int ItemParameter::ITEM_PARAMETER_INDEX_SPPOINT(7);

ItemParameter::ItemParameter(const int& aID) :
mParameterTable(split(loadString(aID), _T(","))),
mID(aID),
mName(mParameterTable[ITEM_PARAMETER_INDEX_NAME]),
mUsable(toInt(mParameterTable[ITEM_PARAMETER_INDEX_USABLE])),
mEquippable(toInt(mParameterTable[ITEM_PARAMETER_INDEX_EQUIPPABLE])),
mThrowable(toInt(mParameterTable[ITEM_PARAMETER_INDEX_THROWABLE])),
mPickable(toInt(mParameterTable[ITEM_PARAMETER_INDEX_PICKABLE])),
mWeight(toFloat(mParameterTable[ITEM_PARAMETER_INDEX_WEIGHT])),
mSpecial(
toSpecialType(mParameterTable[ITEM_PARAMETER_INDEX_SPECIAL]),
toFloat(mParameterTable[ITEM_PARAMETER_INDEX_SPPOINT])
) {
}

