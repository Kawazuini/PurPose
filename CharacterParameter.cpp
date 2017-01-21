/**
 * @file   CharacterParameter.cpp
 * @brief  CharacterParameter
 * @author Maeda Takumi
 */
#include "CharacterParameter.h"

const int CharacterParameter::PARAMETER_INDEX_NAME(0);
const int CharacterParameter::PARAMETER_INDEX_SIZE(1);
const int CharacterParameter::PARAMETER_INDEX_AI(2);
const int CharacterParameter::PARAMETER_INDEX_LEVEL(3);
const int CharacterParameter::PARAMETER_INDEX_EXP(4);
const int CharacterParameter::PARAMETER_INDEX_REQUIREDEXP(5);
const int CharacterParameter::PARAMETER_INDEX_MHP(6);
const int CharacterParameter::PARAMETER_INDEX_AGI(7);
const int CharacterParameter::PARAMETER_INDEX_ATTACKREACH(8);
const int CharacterParameter::PARAMETER_INDEX_STR(9);

CharacterParameter::CharacterParameter() :
mDead(false) {
}

CharacterParameter::CharacterParameter(const int& aID) :
CharacterParameter(aID, split(loadString(aID), _T(","))) {
}

CharacterParameter::CharacterParameter(const int& aID, const Vector<String>& aParameter) :
mParameterTable(aParameter),
mDead(false),
mID(aID),
mName(aParameter[PARAMETER_INDEX_NAME]),
mSize(toFloat(aParameter[PARAMETER_INDEX_SIZE])),
mAI(aParameter[PARAMETER_INDEX_AI]),
mLevel(toInt(aParameter[PARAMETER_INDEX_LEVEL])),
mExperience(toInt(aParameter[PARAMETER_INDEX_EXP])),
mRequireExperience(toInt(aParameter[PARAMETER_INDEX_REQUIREDEXP])),
mMHP(toInt(aParameter[PARAMETER_INDEX_MHP])), mHP(mMHP),
mAGI(toFloat(aParameter[PARAMETER_INDEX_AGI])),
mAttackRange(toFloat(aParameter[PARAMETER_INDEX_ATTACKREACH])),
mSTR(toInt(aParameter[PARAMETER_INDEX_STR])) {
}

float CharacterParameter::throwPower() const {
    static const float COEFFICIENT = 4.0f / 100.0f;
    return mSTR * COEFFICIENT + 1;
}

