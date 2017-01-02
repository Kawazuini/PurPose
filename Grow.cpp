/**
 * @file   Grow.cpp
 * @brief  Grow
 * @author Maeda Takumi
 */
#include "Grow.h"

#include "Device.h"
#include "LevelUp.h"
#include "Object.h"
#include "SpecialManager.h"

Grow::Grow(const int& aEXP, Object * const aSubject)
: Special(aSubject) {
    mEXP = aEXP;
}

Grow& Grow::operator+=(const Grow& aGrow) {
    mEXP += aGrow.mEXP;
    return *this;
}

Grow Grow::operator+(const Grow& aGrow) const {
    return Grow(*this) += aGrow;
}

void Grow::special() {
    int* EXP = &(mSubject->mParameter.mExperience);

    *EXP += mEXP;
    Device::sBulletin.write(mSubject->mParameter.mName + "は" + toString(mEXP) + "けいけんちをえた。");

    // Lv. UP
    for (; mSubject->mParameter.mRequireExperience <= *EXP; mSubject->mParameter.mRequireExperience *= 2) {
        SpecialManager::add(new LevelUp(1, mSubject));
    }
}

