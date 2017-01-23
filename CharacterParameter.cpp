/**
 * @file   CharacterParameter.cpp
 * @brief  CharacterParameter
 * @author Maeda Takumi
 */
#include "CharacterParameter.h"

const int CharacterParameter::CHARACTER_PARAMETER_INDEX_NAME(0);
const int CharacterParameter::CHARACTER_PARAMETER_INDEX_SIZE(1);
const int CharacterParameter::CHARACTER_PARAMETER_INDEX_AI(2);
const int CharacterParameter::CHARACTER_PARAMETER_INDEX_LEVEL(3);
const int CharacterParameter::CHARACTER_PARAMETER_INDEX_EXP(4);
const int CharacterParameter::CHARACTER_PARAMETER_INDEX_REQUIREDEXP(5);
const int CharacterParameter::CHARACTER_PARAMETER_INDEX_MHP(6);
const int CharacterParameter::CHARACTER_PARAMETER_INDEX_AGI(7);
const int CharacterParameter::CHARACTER_PARAMETER_INDEX_ATTACKREACH(8);
const int CharacterParameter::CHARACTER_PARAMETER_INDEX_STR(9);

CharacterParameter::CharacterParameter() :
mDead(false) {
}

CharacterParameter::CharacterParameter(const int& aID) :
mParameterTable(split(loadString(aID), _T(","))),
mDead(false),
mID(aID),
mName(mParameterTable[CHARACTER_PARAMETER_INDEX_NAME]),
mSize(toFloat(mParameterTable[CHARACTER_PARAMETER_INDEX_SIZE])),
mAI(mParameterTable[CHARACTER_PARAMETER_INDEX_AI]),
mLevel(toInt(mParameterTable[CHARACTER_PARAMETER_INDEX_LEVEL])),
mExperience(toInt(mParameterTable[CHARACTER_PARAMETER_INDEX_EXP])),
mRequireExperience(toInt(mParameterTable[CHARACTER_PARAMETER_INDEX_REQUIREDEXP])),
mMHP(toInt(mParameterTable[CHARACTER_PARAMETER_INDEX_MHP])), mHP(mMHP),
mAGI(toFloat(mParameterTable[CHARACTER_PARAMETER_INDEX_AGI])),
mAttackRange(toFloat(mParameterTable[CHARACTER_PARAMETER_INDEX_ATTACKREACH])),
mSTR(toInt(mParameterTable[CHARACTER_PARAMETER_INDEX_STR])) {
}

float CharacterParameter::throwPower() const {
    static const float COEFFICIENT = 4.0f / 100.0f;
    return mSTR * COEFFICIENT + 1;
}

