/**
 * @file   Parameter.cpp
 * @brief  Prameter
 * @author Maeda Takumi
 */
#include "Parameter.h"

int Parameter::sIDDistributor = 0;

Parameter::Parameter() :
mID(++sIDDistributor),
mName(""),
mDead(false),
mLevel(1),
mExperience(0),
mRequireExperience(1),
mMaxHP(1),
mHP(1),
mSpeed(0.0f),
mAttackRange(0.0f),
mStrength(0) {
}

