/**
 * @brief  \~english  Damage.cpp
 * @brief  \~japanese Damage
 * @author Maeda Takumi
 */
#include "Damage.h"

#include "Device.h"
#include "Grow.h"
#include "Object.h"
#include "SpecialManager.h"

Damage::Damage(const int& aDamage, Object * const aSubject, Object * const aObject)
: Special(aSubject, aObject) {
    mDamage = aDamage;
}

void Damage::special() {
    int* HP = &(mObject->mParameter.mHP);
    *HP = Math::max(0, *HP - mDamage);
    if (mDamage) {
        Device::sBulletin.write(mSubject->mParameter.mName + "は" + mObject->mParameter.mName + "に" + toString(mDamage) + "ダメージをあたえた。");
    } else {
        Device::sBulletin.write(mObject->mParameter.mName + "にダメージはない。");
    }

    if (!*HP) {
        Device::sBulletin.write(mObject->mParameter.mName + "はたおれた。");
        mObject->mParameter.mDead = true;
        SpecialManager::add(new Grow(mObject->mParameter.mExperience, mSubject));
    }
}

