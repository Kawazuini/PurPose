/**
 * @file   CharacterParameter.cpp
 * @brief  CharacterParameter
 * @author Maeda Takumi
 */
#include <vector>

#include "CharacterParameter.h"

CharacterParameter::CharacterParameter(const int& aID) :
mParameterTable(split(loadString(aID) + ",", _T(","))),
mDead(false),
mID(aID),
mName(mParameterTable[CHARACTER_INDEX_NAME]),
mSize(toFloat(mParameterTable[CHARACTER_INDEX_SIZE])),
mAI(mParameterTable[CHARACTER_INDEX_AI]),
mLevel(1),
mExperience(toInt(mParameterTable[CHARACTER_INDEX_EXP])),
mMHP(toInt(mParameterTable[CHARACTER_INDEX_MHP])), mHP(mMHP),
mMaxStamina(100), mStamina(100),
mSTR(toInt(mParameterTable[CHARACTER_INDEX_STR])),
mPER(toInt(mParameterTable[CHARACTER_INDEX_PER])),
mAGI(toFloat(mParameterTable[CHARACTER_INDEX_AGI])),
mAttackRange(toFloat(mParameterTable[CHARACTER_INDEX_ATTACKREACH])),
mAttackCost(toInt(mParameterTable[CHARACTER_INDEX_ATTACK_COST])),
mIncreaseMHP(toInt(mParameterTable[CHARACTER_INDEX_INCREASE_MHP])),
mIncreaseSTR(toInt(mParameterTable[CHARACTER_INDEX_INCREASE_STR])),
mTextureNumber(toInt(mParameterTable[CHARACTER_INDEX_TEXTURE])) {
    Vector<String> table(split(loadString(ID_INDEX_EXP + toInt(mParameterTable[CHARACTER_INDEX_GROW])), ","));
    for (String i : table) {
        mRequireExperience.push_back(toInt(i));
    }
}

float CharacterParameter::throwPower() const {
    static const float COEFFICIENT(4.0f / 100.0f);
    return mSTR * COEFFICIENT + 1;
}

