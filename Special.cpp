/**
 * @file   Special.cpp
 * @brief  Special
 * @author Maeda Takumi
 */
#include "Special.h"

#include "Device.h"
#include "Object.h"

List<Special*> Special::sSpecials;
int Special::sIDDistributor = 0;

Special::Special(
        const SpecialType aType,
        Object * const aSubject,
        Object * const aObject,
        const int& aValue
        ) : mID(++sIDDistributor) {
    mType = aType;
    mSubject = aSubject;
    mObject = aObject;
    mValueI1 = aValue;
}

Special::Special(
        const SpecialType aType,
        Object * const aSubject,
        const int& aValue
        )
: Special(aType, aSubject, NULL, aValue) {
}

Special::Special(
        const SpecialType aType,
        Object * const aSubject,
        const double& aValue
        ) : mID(++sIDDistributor) {
    mType = aType;
    mSubject = aSubject;
    mObject = NULL;
    mValueD1 = aValue;
}

void Special::special() {
    switch (mType) {
        case DAMAGE:
        {
            int* HP = &(mObject->mParameter.mHP);
            *HP = Math::max(0, *HP - mValueI1);
            if (mValueI1) {
                Device::sBulletin.write(mSubject->mParameter.mName + "は" + mObject->mParameter.mName + "に" + toString(mValueI1) + "ダメージをあたえた。");
            } else {
                Device::sBulletin.write(mObject->mParameter.mName + "にダメージはない。");
            }

            if (!*HP) {
                Device::sBulletin.write(mObject->mParameter.mName + "はたおれた。");
                mObject->mParameter.mDead = true;
                Grow(mSubject, mObject->mParameter.mExperience);
            }
            break;
        }
        case GROW:
        {
            int* EXP = &(mSubject->mParameter.mExperience);

            *EXP += mValueI1;
            Device::sBulletin.write(mSubject->mParameter.mName + "は" + toString(mValueI1) + "けいけんちをえた。");

            // Lv. UP
            for (; mSubject->mParameter.mRequireExperience <= *EXP; mSubject->mParameter.mRequireExperience *= 2) {
                LevelUp(mSubject, 1);
            }
            break;
        }
        case HEAL:
            break;
        case LEVELUP:
        {
            int* level = &(mSubject->mParameter.mLevel);

            *level += mValueI1;
            Device::sBulletin.write(mSubject->mParameter.mName + "はレベルが" + toString(*level) + "にあがった。");
            break;
        }
    }
}

void Special::add(Special * const aSpecial) {
    sSpecials.push_back(aSpecial);
}

void Special::cutin(Special * const aSpecial) {
    sSpecials.push_front(aSpecial);
}

void Special::invocation() {
    while (!sSpecials.empty()) {
        Special* sp = sSpecials.front();
        sSpecials.pop_front();
        sp->special();
        delete sp;
    }
}

void Special::Damage(Object * const aSubject, Object * const aObject, const int& aDamage) {
    add(new Special(DAMAGE, aSubject, aObject, aDamage));
}

void Special::Grow(Object * const aSubject, const int& aExp) {
    if (!sSpecials.empty() && sSpecials.back()->mType == GROW) sSpecials.back()->mValueI1 += aExp;
    else add(new Special(GROW, aSubject, aExp));
}

void Special::Heal(Object * const aSubject, Object * const aObject, const int& aHeal) {
    add(new Special(HEAL, aSubject, aObject, aHeal));
}

void Special::LevelUp(Object * const aSubject, const int& aLevel) {
    if (!sSpecials.empty() && sSpecials.back()->mType == LEVELUP) sSpecials.back()->mValueI1 += aLevel;
    else add(new Special(LEVELUP, aSubject, aLevel));
}

