/**
 * @file   LevelUp.cpp
 * @brief  LevelUp
 * @author Maeda Takumi
 */
#include "LevelUp.h"

#include "Device.h"
#include "Object.h"

LevelUp::LevelUp(const int& aLevel, Object * const aSubject)
: Special(aSubject) {
    mLevel = aLevel;
}

LevelUp& LevelUp::operator+=(const LevelUp& aLevelUp) {
    mLevel += aLevelUp.mLevel;
    return *this;
}

LevelUp LevelUp::operator+(const LevelUp& aLevelUp) const {
    return LevelUp(mLevel, mSubject) += aLevelUp;
}

void LevelUp::special() {
    int* level = &(mSubject->mParameter.mLevel);

    *level += mLevel;
    Device::sBulletin.write(mSubject->mParameter.mName + "はレベルが" + toString(*level) + "にあがった。");
}

