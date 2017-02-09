/**
 * @file   CharacterParameter.cpp
 * @brief  CharacterParameter
 * @author Maeda Takumi
 */
#include "CharacterParameter.h"

CharacterParameter::CharacterParameter(const int& aID) :
mParameterTable(split(loadString(aID), _T(","))),
mDead(false),
mID(aID),
mName(mParameterTable[CHARACTER_INDEX_NAME]),
mSize(toFloat(mParameterTable[CHARACTER_INDEX_SIZE])),
mAI(mParameterTable[CHARACTER_INDEX_AI]),
mLevel(1),
mExperience(toInt(mParameterTable[CHARACTER_INDEX_EXP])),
mRequireExperience(20),
mMHP(toInt(mParameterTable[CHARACTER_INDEX_MHP])), mHP(mMHP),
mAGI(toFloat(mParameterTable[CHARACTER_INDEX_AGI])),
mAttackRange(toFloat(mParameterTable[CHARACTER_INDEX_ATTACKREACH])),
mSTR(toInt(mParameterTable[CHARACTER_INDEX_STR])),
mAttackCost(toInt(mParameterTable[CHARACTER_INDEX_ATTACK_COST])) {
}

float CharacterParameter::throwPower() const {
    static const float COEFFICIENT(4.0f / 100.0f);
    return mSTR * COEFFICIENT + 1;
}

