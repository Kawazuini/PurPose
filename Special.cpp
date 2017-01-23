/**
 * @file   Special.cpp
 * @brief  Special
 * @author Maeda Takumi
 */
#include "Special.h"

#include "GameState.h"

List<Special> Special::sSpecials;

Special::Special(
        const SpecialType& aType,
        const double aValue,
        Character * const aSubject,
        Character * const aObject
        ) :
mType(aType),
mValue(aValue),
mSubject(aSubject),
mObject(aObject) {
}

Special::Special(
        const Special& aSpecial,
        Character * const aSubject,
        Character * const aObject
        ) :
Special(aSpecial.mType, aSpecial.mValue, aSubject, aObject) {
}

void Special::special(GameState& aState) {
    CharacterParameter * S(mSubject ? &(mSubject->mCharacterParameter) : NULL);
    CharacterParameter * O(mObject ? &(mObject->mCharacterParameter) : NULL);

    switch (mType) {
        case MISS:
        {
            aState.mBulletin.write("なにもおこらない!");
            break;
        }
        case DAMAGE:
        {
            O->mHP = Math::max(0, (int) (O->mHP - mValue));
            if (mValue) {
                aState.mBulletin.write(S->mName + "は" + O->mName + "に" + toString((int) mValue) + "ダメージをあたえた。");
            } else {
                aState.mBulletin.write(O->mName + "にダメージはない。");
            }

            if (!O->mHP) {
                aState.mBulletin.write(O->mName + "はたおれた。");
                O->mDead = true;
                if (sSpecials.back().mType == GROW) {
                    sSpecials.back().mValue += O->mExperience;
                } else add(Special(GROW, O->mExperience, mSubject));
            }
            break;
        }
        case GROW:
        {
            S->mExperience += mValue;
            aState.mBulletin.write(S->mName + "は" + toString((int) mValue) + "けいけんちをえた。");

            // Lv. UP
            for (; S->mRequireExperience <= S->mExperience; S->mRequireExperience *= 2) {
                if (sSpecials.back().mType == LEVELUP) {
                    sSpecials.back().mValue += 1;
                } else add(Special(LEVELUP, 1, mSubject));
            }
            break;
        }
        case HEAL:
        {
            if (O) {
                O->mHP = Math::min((int) (O->mHP + mValue), O->mMHP);
                aState.mBulletin.write(S->mName + "は" + O->mName + "のHPを" + toString((int) mValue) + "かいふくさせた。");
                break;
            } else {
                S->mHP = Math::min((int) (S->mHP + mValue), S->mMHP);
                aState.mBulletin.write(S->mName + "のHPは" + toString((int) mValue) + "かいふくした。");
                break;
            }
        }
        case LEVELUP:
        {
            S->mLevel += mValue;
            aState.mBulletin.write(S->mName + "はレベルが" + toString(S->mLevel) + "にあがった。");
            break;
        }
    }
}

void Special::add(const Special& aSpecial) {
    sSpecials.push_back(aSpecial);
}

void Special::cutin(const Special& aSpecial) {
    sSpecials.push_front(aSpecial);
}

void Special::invocation(GameState& aState) {
    while (!sSpecials.empty()) {
        Special sp(sSpecials.front());
        sSpecials.pop_front();
        sp.special(aState);
    }
}

