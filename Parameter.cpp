/**
 * @file   Parameter.cpp
 * @brief  Prameter
 * @author Maeda Takumi
 */
#include "Parameter.h"

int Parameter::sIDDistributor = 0;

Parameter::Parameter()
: mID(++sIDDistributor) {
    mName = "";
    mDead = false;

    mLevel = 1;
    mExperience = mRequireExperience = 0;
    mMaxHP = mHP = 1;
    mSpeed = 0.0f;
}

Parameter::Parameter(const Parameter& orig)
: mID(orig.mID) {
}

Parameter::~Parameter() {
}

