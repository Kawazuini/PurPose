/**
 * @file   Special.cpp
 * @brief  Special
 * @author Maeda Takumi
 */
#include "Special.h"

#include "Bulletin.h"
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

void Special::special(const GameState& aState) {
    Parameter* S = mSubject ? &(mSubject->mParameter) : NULL;
    Parameter* O = mObject ? &(mObject->mParameter) : NULL;

    switch (mType) {
        case DAMAGE:
        {
            O->mHP = Math::max(0, O->mHP - mValueI1);
            if (mValueI1) {
                aState.mBulletin.write(S->mName + "は" + O->mName + "に" + toString(mValueI1) + "ダメージをあたえた。");
            } else {
                aState.mBulletin.write(O->mName + "にダメージはない。");
            }

            if (!(O->mHP)) {
                aState.mBulletin.write(O->mName + "はたおれた。");
                O->mDead = true;
                Grow(mSubject, O->mExperience);
            }
            break;
        }
        case GROW:
        {
            S->mExperience += mValueI1;
            aState.mBulletin.write(S->mName + "は" + toString(mValueI1) + "けいけんちをえた。");

            // Lv. UP
            for (; S->mRequireExperience <= S->mExperience; S->mRequireExperience *= 2) {
                LevelUp(mSubject, 1);
            }
            break;
        }
        case HEAL:
        {
            O->mHP = Math::min(O->mHP + mValueI1, O->mMaxHP);
            aState.mBulletin.write(O->mName + "のHPは" + toString(mValueI1) + "かいふくした。");
            break;
        }
        case LEVELUP:
        {
            S->mLevel += mValueI1;
            aState.mBulletin.write(S->mName + "はレベルが" + toString(S->mLevel) + "にあがった。");
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

void Special::invocation(const GameState& aState) {
    while (!sSpecials.empty()) {
        Special* sp = sSpecials.front();
        sSpecials.pop_front();
        sp->special(aState);
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

